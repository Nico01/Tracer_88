#include <stdio.h>                      // for snprintf, sprintf, fprintf, etc
#include <stdlib.h>                     // for exit, EXIT_FAILURE
#include <string.h>                     // for strcmp, strcpy, strlen, etc
#include <time.h>                       // for time_t
#include <fcntl.h>                      // for creat, open
#include <sys/stat.h>                   // for stat, st_mtime
#include <unistd.h>                     // for fork, write, close, dup2, etc

#include "prototype.h"
#include "88.h"                         // for memory, traceflag, sp, ds, etc
#include "macro.h"                      // for PC, CS


#define CBUF 180
#define MAGIC 0x0201
#define MAXSHORT 0XFFFF
#define MAXSYMTAB 0XFFF

char fnameL[CBUF], fnameS[CBUF], fname88[CBUF], fnamei[CBUF], fnamet[CBUF];
char nulsymbol[] = "NULLSYMBOL";
time_t t1, t2;
struct stat astat[2], *bf;
FILE *bituit;

int pfildes[2], pnr, termbitsize;
char bmbuf[9000];
/*file descriptor and procedure number to create a pipe for the bitmap*/

char window[24][81], cmdchar, cmdline[30], outveld[4][59];
unchr prdepth, bprdepth; /*prdepth altijd bijhouden; bprdepth zetten bij +-= */
int stckprdepth[20], prstckpos[20], nsymtab, maxsp;
int puthp; /*horizontale en verticale putpositie*/

typedef struct {
    short pcp;
    unchr bprt;
} bprveld;
bprveld bparr[32]; /* break point fields */

typedef struct {
    char typ;
    char sct;
    short smb;
    int adrs;
} relocveld;

relocveld relocarr[1024]; /* relocation variables field */

short lndotarr[0X2000], lnsymarr[0X2000], dotlnarr[0X6000], bssreloc;
int lnfilarr[0X6000], maxln, symp; /*fileptr in source, max source, last symbol*/

int lfptr, cmdfl, inpfl, errflag; /*load file pointer, command or input from file*/
char *syssp; /*pointer in stack for conversion in system calls*/

typedef struct {
    int symvalue;
    char *symbol;
    int nextsym;
    int lnr;
    char symsect;
} tsymtab; /*symbol table stucture */

tsymtab symtab[MAXSYMTAB];

char tringfield[1600], stringfield[8000], errbuf[292], inbuf[2024], *inbpl, *inbpu;
char *datadm[7], datadarr[7][81], basename[CBUF];
int datadp, /*pointer in datadarr */ symhash[32]; /* pointer in symbol table*/

typedef struct {
    int startad;
    int lengte;
    int fstart;
    int flen;
    int align;
} segmenthead;

segmenthead segmhead[8];

typedef union {
    int ii;
    char *cp;
} paramfield;

typedef union {
    int ii;
    char cp[140];
} sscanfield;

FILE *prog, *L, *CMD, *INP, *LOG;



int getint(FILE *f) {
    int i, j;
    lfptr += 4;

    i = (getc(f) & 0xFF) | ((getc(f) & 0xFF) << 8);
    j = (getc(f) & 0xFF) | ((getc(f) & 0xFF) << 8);

    return i | (j << 16);
}


int getsh(FILE *f) {
    lfptr += 2;
    return (getc(f) & 0xFF) | ((getc(f) & 0xFF) << 8);
}


void relocate( int n ) {
    int tp, sc, st, sa, ss;
    int i, j, k;
    char *p, octs[4];

    tp = (relocarr[n].typ & 0X3F);
    sc = (relocarr[n].sct & 0XFFFF);
    st = (relocarr[n].smb & 0XFFFF);
    sa = (relocarr[n].adrs & 0XFFFF);

    sa += segmhead[sc - 2].startad;

    if (sc > 2)
        sa += ds << 4;

    p = memory + sa;
    ss = i = 0;

    for (k = 0; k < (tp & 3); k++) {
        j = ((*p++) & 0xFF);
        octs[k] = j;
        j <<= i;
        i += 8;
        ss += j;
    }

    ss += symtab[st].symvalue;
    p = memory + sa;

    for (k = 0; k < (tp & 3); k++) {
        *p++ = octs[k + 2] = ss & 0xFF;
        ss >>= 8;
    }
}


int lcs( char *p, int s ) {
    char c, *q;
    int j, k, add;
    while ((*p <= ' ') || (*p == ':'))
        if (*p == 0)
            return (-1);
        else
            p++;
    j = 0;
    q = p;
    while ((c = *p++)) {
        j++;
        if (c == '\n' || c == '!' || c < '\t' || c > 126)
            return (-1);
        if (c <= ' ')
            return (lcs(q + j, s));
        if (c == ':') {
            k = j;
            p -= 2;
            add = hashstring(q);
            k = symhash[add];
            if (k < 0)
                return (-1);
            while (k >= 0) {
                if (k == s)
                    break;
                if (symtab[k].nextsym < 0)
                    break;
                k = symtab[k].nextsym;
            }

            if ((k == s) && (!strncmp(q, symtab[k].symbol, j - 1)) &&
                (strlen(symtab[k].symbol) == j - 1))
                return (0);
            if (*q <= '\n')
                return (-1);
            return (lcs(q + j, s));
        }
    }
    return (-1);
}

void symlcorr( int i ) {
    /* corrigeert line number bug voor symbolen uit de text. Zonder correctie
     wordt niet het line number, maar de eerste code doorgegeven */
    int ln, cd, j; //, c;
    //char *p;
    ln = symtab[i].lnr;
    cd = symtab[i].symvalue;
    while (ln > 0 && lndotarr[ln] == cd) {
        fseek(L, (int)lnfilarr[ln], 0);
        j = fread(inbuf, 1, lnfilarr[ln + 1] - lnfilarr[ln], L);
        inbuf[j] = '\0';
        if (!lcs(inbuf, i)) {
            symtab[i].lnr = ln;
            return;
        }
        ln--;
    }
}

char *spadr() {
    int i = 0;
    i |= (*syssp++) & 0xFF;
    i |= ((*syssp++) << 8) & 0XFFFF;
    return (memory + i + (ds << 4));
}

int spint( void ) {
    int i = 0;
    i |= (*syssp++) & 0xFF;
    i |= (*syssp++) << 8;
    return (i & 0XFFFF);
}

void returnax( int retval ) {
    al = (char)(retval & 0xFF);
    ah = (char)((retval >> 8) & 0xFF);
}

void syscal( void ) {
    char calnr, *q, *p, c;
    int retval, i, j, ar[9], k, l, fwidth[9]; //kk, ll,

    paramfield pram[8];
    sscanfield s[9];
    /*adrfield adrf;*/
    syssp = (sp & 0xffff) + (ss << 4) + memory;
    calnr = *syssp;
    syssp += 2;
    /*snprintf(errbuf, sizeof (errbuf),"system call %3d, %x",calnr,calnr); meldroutine();
     * winupdate();*/
    switch (calnr) {
    case 0x01: /*exit*/
        if (traceflag) {
            winupdate();
            mvcur(24, 0);
            winupdate();
            mvcur(24, 0);
            fprintf(stderr, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        }
        exit(spint());
        break;
    case 0x02: /*fork*/
        retval = fork();
        returnax(retval);
        break;
    case 0x03: /*read*/
        pram[0].ii = spint();
        pram[1].cp = spadr();
        pram[2].ii = spint();
        if (traceflag && (pram[0].ii == 0)) {
            retval = 0;
            p = pram[1].cp;
            while ((j = getchbp()) > 0) {
                *p++ = j;
                retval++;
                if (!--(pram[2].ii))
                    break;
            }
            if (retval == 0)
                retval = j;
        } else
            retval = read(pram[0].ii, pram[1].cp, pram[2].ii);

        returnax(retval);
        break;
    case 0x04: /*write*/
        pram[0].ii = spint();
        pram[1].cp = spadr();
        pram[2].ii = spint();
        if (traceflag && (pram[0].ii == 1)) {
            retval = pram[2].ii;
            p = pram[1].cp;
            while (pram[2].ii) {
                nextput(*p++);
                (pram[2].ii)--;
            }
            /*winupdate();*/
        } else {
            if (traceflag && (pram[0].ii == 2)) {
                retval = pram[2].ii;
                p = pram[1].cp;
                snprintf(errbuf, sizeof (errbuf), "%.55s", p);
                erroutine();
                /*winupdate();*/
            } else
                retval = write(pram[0].ii, pram[1].cp, pram[2].ii);
        }

        returnax(retval);
        break;
    case 0x05: /*open*/
        pram[0].cp = spadr();
        pram[1].ii = spint();
        retval = open(pram[0].cp, pram[1].ii);
        returnax(retval);
        break;
    case 0x06: /*close*/
        pram[0].ii = spint();
        if (traceflag && (pram[0].ii) == 1) {
            snprintf(errbuf, sizeof (errbuf), "close call standard output cannot be traced");
            erroutine();
            retval = 1;
        } else
            retval = close(pram[0].ii);
        returnax(retval);
        break;
    case 0x08: /*creat*/
        pram[0].cp = spadr();
        pram[1].ii = spint();
        retval = creat(pram[0].cp, pram[1].ii);
        returnax(retval);
        break;
    case 0x09: /*link*/
        pram[0].cp = spadr();
        pram[1].cp = spadr();
        retval = link(pram[0].cp, pram[1].cp);
        returnax(retval);
        break;
    case 0x0b: /*exec*/
        pram[0].cp = spadr();
        if ((prog = fopen(pram[0].cp, "rb")) == NULL) {
            snprintf(errbuf, sizeof (errbuf), "Interpreter 8088 cannot open %s", pram[0].cp);
            erroutine();
            returnax(-1);
        } else {
            //~ if (load())
                //~ returnax(-1);
            fclose(prog);
        }
        break;
    case 0x13: /*lseek*/
        pram[0].ii = spint();
        pram[1].ii = 0;
        pram[1].ii |= spint();
        pram[1].ii |= (spint() << 16);
        pram[2].ii = spint();
        retval = lseek(pram[0].ii, pram[1].ii, pram[2].ii);
        dl = (char)((retval >> 16) & 0xff);
        dh = (char)((retval >> 24) & 0xff);
        returnax(retval);
        break;
    case 0x40:
        pram[0].ii = spint();
        pram[1].ii = spint();
        pram[2].ii = spint();
        bitmapopen(pram[0].ii, pram[1].ii, pram[2].ii);
        break;
    case 0x41:
        pram[0].ii = spint();
        pram[1].ii = spint();
        pram[2].cp = spadr();
        bitmapdump(pram[0].ii, pram[1].ii, pram[2].cp);
        break;
    case 0x75: /*getchar*/
        if (traceflag) {
            retval = getchbp();
        } else
            retval = getchar();
        returnax(retval);
        break;

    case 0x79: /*sprintf* / sprintf(buf,"%s\n",spadr());break; */
        pram[0].cp = spadr();
        p = pram[1].cp = spadr();
        j = 2;
        /*fprintf(stderr,"%x %d %d pram\n",pram[0].ii,pram[0].ii,0);*/
        /*fprintf(stderr,"%x %d %d pram\n",pram[1].ii,pram[1].ii,1);*/
        while ((c = *p++)) {
            /* fprintf(stderr,"`%c ",c);*/
            if (c == '%') {
                i = 1;
                while (i && (c = *p++)) {
                    switch (c) {
                    case ' ':
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                    case '.':
                    case '-':
                    case '+':
                    case '#':
                        break;
                    case '*':
                        pram[j++].ii = spint();
                        break;
                    case 'l':
                    case 'L':
                        i = 2;
                        break;
                    case 'D':
                    case 'O':
                    case 'X':
                    case 'U':
                        i = 2;
                    case 'd':
                    case 'o':
                    case 'x':
                    case 'u':
                    case 'c':
                    case 'i':
                        pram[j].ii = spint();
                        if (i == 2)
                            pram[j].ii |= (spint() << 16);
                        else if (((c == 'd') || (c == 'i')) &&
                                 (pram[j].ii & 0x8000))
                            pram[j].ii |= 0xffff0000;
                        j++;
                        i = 0;
                        break;
                    case 's':
                        pram[j].cp = spadr();
                        i = 0;
                        j++;
                        break;
                    case 'e':
                    case 'E':
                    case 'f':
                    case 'F':
                    case 'g':
                        snprintf(errbuf, sizeof (errbuf), "Floats not implemented");
                        erroutine();
                    default:
                        i = 0;
                        break;
                    }
                }
                /*fprintf(stderr,"%x %d %d pram\n",pram[j].ii,pram[j].ii,j);*/
            }
        }
        if (j > 8) {
            snprintf(errbuf, sizeof (errbuf), "not more than 6 conversions in printf");
            erroutine();
        }
        /*snprintf(errbuf, sizeof (errbuf),"pram %x in sprintf\n",pram[0].cp-m); erroutine();*/
        retval = (int)(sprintf(pram[0].cp, pram[1].cp, pram[2].ii, pram[3].ii,
                               pram[4].ii, pram[5].ii, pram[6].ii, pram[7].ii));
        returnax(retval);
        break;

    case 0x7a: /*putchar*/
        pram[0].ii = spint();
        if (traceflag) {
            nextput(pram[0].ii);
            retval = pram[0].ii;
                /*winupdate();*/}
        else {
            retval = putchar(pram[0].ii);
            fflush(stdout);
        }
        returnax(retval);
        break;

    case 0x7d: /*sscanf*/
        for (i = 0; i < 9; i++) {
            ar[i] = 0;
            fwidth[i] = 1;
        }
        for (i = 0; i < 9; i++)
            for (j = 0; j < 140; j++)
                s[i].cp[j] = '\0';
        pram[0].cp = spadr();
        p = pram[1].cp = spadr();
        j = 2;
        while ((c = *p++)) {
            if (c == '%') {
                i = 2;
                while (i && (c = *p++)) {
                    switch (c) {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        p--;
                        sscanf(p, "%d", &fwidth[j]);
                        while ((c >= '0') && (c <= '9'))
                            c = *p++;
                        p--;
                        continue;
                    case '.':
                    case '-':
                    case '+':
                    case '*':
                        break;
                    case 'l':
                    case 'L':
                        i = 4;
                        break;
                    case 'h':
                    case 'H':
                        i = 1;
                        break;
                    case 'D':
                    case 'O':
                    case 'X':
                    case 'U':
                    case 'd':
                    case 'o':
                    case 'x':
                    case 'u':
                        ar[j] = i;
                        i = 0;
                        pram[j].cp = spadr();
                        j++;
                        break;
                    case 'c':
                        ar[j] = 3;
                        pram[j].cp = spadr();
                        j++;
                        i = 0;
                        break;
                    case 's':
                        pram[j].cp = spadr();
                        j++;
                        i = 0;
                        break;
                    case '[':
                        pram[j].cp = spadr();
                        j++;
                        i = 0;
                        while ((c = *p++) != ']')
                            if (c < ' ')
                                break;
                        break;
                    case 'e':
                    case 'E':
                    case 'f':
                    case 'F':
                    case 'g':
                        snprintf(errbuf, sizeof (errbuf), "Floats not implemented");
                        erroutine();
                    default:
                        i = 0;
                        break;
                    }

                }
            }
        }
        if (j > 8) {
            snprintf(errbuf, sizeof (errbuf), "not more than 6 conversions in sscanf");
            erroutine();
        }

        retval = sscanf(pram[0].cp, pram[1].cp, &s[2], &s[3], &s[4], &s[5],
                        &s[6], &s[7]);

        for (i = 2; i < j; i++) {
            if (ar[i] == 0) {
                strcpy(pram[i].cp, s[i].cp);
                continue;
            }
            if (ar[i] == 1) {
                *pram[i].cp = *(s[i].cp);
                continue;
            }
            if (ar[i] == 2) {
                k = (s[i].ii & 255);
                *(pram[i].cp) = (char)k;
                l = (s[i].ii >> 8) & 255;
                *(pram[i].cp + 1) = (char)(l);
                continue;
            }
            if (ar[i] == 3) {
                q = pram[i].cp;
                for (k = 0; k < fwidth[i]; k++)
                    *q++ = s[i].cp[k];
                continue;
            }
            if (ar[i] == 4) {
                l = (s[i].ii >> 24) & 255;
                *(pram[i].cp + 3) = (char)l;
                l = (s[i].ii >> 16) & 255;
                *(pram[i].cp + 2) = (char)l;
                l = (s[i].ii >> 8) & 255;
                *(pram[i].cp + 1) = (char)l;
                l = s[i].ii & 255;
                *(pram[i].cp) = (char)l;
                continue;
            }
        }
        returnax(retval);
        break;

    case 0x7f: /*printf*/
        p = pram[0].cp = spadr();
        j = 1;
        while ((c = *p++)) {
            /* fprintf(stderr,"`%c ",c);*/
            if (c == '%') {
                i = 1;
                while (i && (c = *p++)) {
                    switch (c) {
                    case ' ':
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                    case '.':
                    case '-':
                    case '+':
                    case '#':
                        break;
                    case '*':
                        pram[j++].ii = spint();
                        break;
                    case 'l':
                    case 'L':
                        i = 2;
                        break;
                    case 'D':
                    case 'O':
                    case 'X':
                    case 'U':
                        i = 2;
                    case 'd':
                    case 'o':
                    case 'x':
                    case 'u':
                    case 'c':
                    case 'i':
                        pram[j].ii = spint();
                        if (i == 2)
                            pram[j].ii |= (spint() << 16);
                        else if (((c == 'd') || (c == 'i')) &&
                                 (pram[j].ii & 0x8000))
                            pram[j].ii |= 0xffff0000;
                        j++;
                        i = 0;
                        break;
                    case 's':
                        pram[j].cp = spadr();
                        i = 0;
                        j++;
                        break;
                    case 'e':
                    case 'E':
                    case 'f':
                    case 'F':
                    case 'g':
                        snprintf(errbuf, sizeof (errbuf), "Floats not implemented");
                        erroutine();
                    default:
                        i = 0;
                        break;
                    }
                }
            }
        }
        if (j > 8) {
            snprintf(errbuf, sizeof (errbuf), "not more than 7 conversions in printf");
            erroutine();
        }
        /*snprintf(errbuf, sizeof (errbuf),"pram %x in printf\n",pram[0].cp-m); erroutine();*/
        if (traceflag) {
            retval = j;
            sprintf(tringfield + 200, pram[0].cp, pram[1].ii, pram[2].ii,
                    pram[3].ii, pram[4].ii, pram[5].ii, pram[6].ii, pram[7].ii);
            p = tringfield + 200;
            while ((j = *p++))
                nextput(j); /*winupdate();*/
        } else {
            retval = printf(pram[0].cp, pram[1].ii, pram[2].ii, pram[3].ii,
                            pram[4].ii, pram[5].ii, pram[6].ii, pram[7].ii);
            fflush(stdout);
        }
        returnax(retval);
        break;
    default:
        snprintf(errbuf, sizeof (errbuf), "Unimplemented sys call %d", calnr);
        erroutine();
        exit(EXIT_FAILURE);
        break;
        //~ /* case 0x07: /*wait* / break;
        //~ case 0x0c: /*cdir* / break;
        //~ case 0x0d: /*time* / break;
        //~ case 0x0e: /*mknod* / break;
        //~ case 0x0f: /*chmod* / break;
        //~ case 0x10: /*chown* / break;
        //~ case 0x11: /*brk* / break;
        //~ case 0x12: /*stat* / break;
        //~ case 0x14: /*getpid* / break;
        //~ case 0x15: /*mount* / break;
        //~ case 0x16: /*umount* / break;
        //~ case 0x17: /*setuid* / break;
        //~ case 0x18: /*getuid* / break;
        //~ case 0x19: /*stime* / break;
        //~ case 0x1a: /*ptrace* / break;
        //~ case 0x1b: /*alarm* / break;
        //~ case 0x1c: /*fstat* / break;
        //~ case 0x1d: /*pause* / break;
        //~ case 0x1e: /*utime* / break;
        //~ case 0x1f: /*stty* / break;
        //~ case 0x20: /*gtty* / break;
        //~ case 0x21: /*access* / break;
        //~ case 0x22: /*nice* / break;
        //~ case 0x23: /*ftime* / break;
        //~ case 0x24: /*sync* / break;
        //~ case 0x25: /*kill* / break;
        //~ case 0x29: /*dup* / break;
        //~ case 0x2a: /*pipe* / break;
        //~ case 0x2b: /*times* / break;
        //~ case 0x2c: /*profil* / break;
        //~ case 0x2e: /*setgid* / break;
        //~ case 0x2f: /*getgid* / break;
        //~ case 0x30: /*signal* / break;
        //~ case 0x33: /*acct* / break;
        //~ case 0x35: /*lock* / break;
        //~ case 0x36: /*ioctl* / break;
        //~ case 0x3b: /*exece* / break;
        //~ case 0x3c: /*umask* / break;
        //~ case 0x3d: /*chroot* / break;
        //~ case 0x76: /*getc* / break;
        //~ case 0x77: /*gets* / break;
        //~ case 0x78: /*ungetc* / break;
        //~ case 0x7e: /*scanf* / break;
        //~ case 0x7b: /*putc* / break;
        //~ case 0x7c: /*puts* / break; */
    }
}

void dump( void ) {
    int i;
    char *p;

    cnulbp();
    pdmpadr();
    rdcmd();
    if (errflag) {
        sprintf(window[10] + 22, "E Last message: %-37.37s", errbuf);
        errflag = 0;
    } else if (window[10][22] == 'M') {
        sprintf(window[10] + 22, "  %-55.55s", window[10] + 37);
    }
    p = errbuf;
    for (i = 0; i < 56; i++)
        *p++ = ' ';
}

void procdepth( int s ) {
    if (s > 0) {
        prdepth++;
        stckprdepth[prdepth] = dotlnarr[(((int)(PC)) & 0xFFFF) - s];
        prstckpos[prdepth] = sp - 2;
    }
    if (s == -1) {
        checkret();
        prdepth--;
    }
    if (prdepth == bprdepth)
        stopvlag |= 1;
    else
        stopvlag &= 0xFE;
}

void checkret( void ) {
    if (sp != prstckpos[prdepth]) {
        snprintf(errbuf, sizeof (errbuf), "Return on suspicious stack pointer prdepth %d", prdepth);
        erroutine();
        if (traceflag)
            dump();
        exit(EXIT_FAILURE);
    }
}

void zetbp( short textdot ) {
    int i;
    for (i = 1; i < 32; i++)
        if (!bparr[i].pcp)
            break;
    if (i == 32) {
        snprintf(errbuf, sizeof (errbuf), "break point table full");
        erroutine();
    }
    bparr[i].pcp = textdot;
    bparr[i].bprt = memory[cs16 + textdot];
    memory[cs16 + textdot] = 0xF0;
}

void clearbp( short textdot ) {
    int i;
    for (i = 1; i < 32; i++)
        if (bparr[i].pcp == textdot)
            break;
    if (i == 32) {
        snprintf(errbuf, sizeof (errbuf), "Break point not found.");
        erroutine();
    }
    bparr[i].pcp = 0;
    memory[cs16 + textdot] = bparr[i].bprt;
    bparr[i].bprt = memory[0];
}

void cnulbp( void ) {
    char *p;
    if (bparr[0].pcp != -1) {
        p = memory + cs16 + bparr[0].pcp;
        if (*p == '\360')
            *p = bparr[0].bprt;
        bparr[0].pcp = 0xFFFF;
    }
}

void nulbp( int ln ) {
    char *p;
    int dott;
    p = memory + cs16 + bparr[0].pcp;
    if (*p == '\360')
        *p = bparr[0].bprt;
    dott = lndotarr[ln];
    p = memory + cs16 + dott;
    bparr[0].pcp = dott;
    bparr[0].bprt = *p;
    *p = 0XF0;
}

int hashstring( char *p ) {
    return (((*p) - 'A') & 0x1F);
}

void breakpt( void ) {
    int i, j;
    i = ((int)(PC)) & 0xFFFF;
    i--;
    for (j = 0; j < 32; j++)
        if (bparr[j].pcp == i)
            break;
    if (j == 32) {
        snprintf(errbuf, sizeof (errbuf), "Wrong breakpoint");
        erroutine();
        exit(EXIT_FAILURE);
    }
    dumpt = bparr[j].bprt;
    dump();
}

void dmpadr( int adre ) {
    datadm[datadp] = memory + (ds << 4) + adre;
    snprintf(datadarr[datadp], sizeof (datadarr[datadp]), "%.19s", tringfield + 90);
    datadarr[datadp][19] = ' ';
    datadarr[datadp][18] = ':';
    datadp++;
    datadp %= 7;
}

void pdmpadr( void ) {
    char *o, *p, *q, *r, c;
    unsigned long ii, i, j;
    for (i = 0; i < 7; i++) {
        o = q = p = datadm[i];
        if (p != NULL) {
            for (j = 0; j < 8; j++) {
                r = datadarr[i];
                r += 19 + 3 * j;
                snprintf(r,  sizeof (r) ,"%3x", *p++ & 0xFF);
            }
            datadarr[i][43] = ' ';
            for (j = 0; j < 12; j++) {
                c = *q++;
                if (c < 32 || c > 126)
                    c = '.';
                datadarr[i][44 + j] = c;
            }
            for (j = 0; j < 4; j++) {
                r = datadarr[i];
                r += 55 + 6 * j;
                ii = *o++ & 0xFF;
                if (*o & 128)
                    ii |= 0XFFFF0000;
                ii |= (*o++ & 0xFF) << 8;
                snprintf(r, sizeof (r), "%6lu", ii);
            }
        }
    }
}

void rdcmd( void ) {
    int c, d, adre;
    mvcur(15, 0);
    for (c = 0; c < 20; c++)
        putchar(' ');
    mvcur(15, 0);
    snprintf(window[15], sizeof (window[15]), "                 ");
    winupdate();
    symp = -1;
    c = getchcmd();
    if (c == '/') {
        c = getchcmd();
        d = 1;
    } else
        d = 0;
    stopvlag = 0;
    rdcline(c);
    if (d) {
        adre = rdstrg();
        if (adre == -1) {
            /*snprintf(errbuf, sizeof (errbuf),"No match"); erroutine();*/ rdcmd();
            return;
        }
        if (symp == -1) {
            /*snprintf(errbuf, sizeof (errbuf),"No match"); erroutine();*/ rdcmd();
            return;
        }
    } else if ((c >= '0') && (c <= '9')) {
        adre = rdadr();
        if (cmdchar == '!')
            cmdchar = (symtab[symp].symsect < 3) ? 'x' : 'd';
    } else {
        adre = dotlnarr[(PC) - 1];
        cmdchar = c;
        if (c == '\n')
            c = '?';
    }
    /* Note: (PC)-1. The next instruction initial byte is fetched before the
     * dump*/
    if (cmdchar == '\n')
        cmdchar = 'S';
    instrcount = 0X7fffffff;
    bprdepth = -1;
    if (cmdchar == '!')
        cmdchar = (symtab[symp].symsect < 3) ? 'x' : 'd';
    if ((cmdchar < 5) || (cmdchar > 126))
        cmdchar = 'q';
    switch (cmdchar) {
    case 'q':
        fprintf(stderr, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        exit(0);
        break;
    case 'r':
        instrcount = 0X7fffffff;
        break;
    case '-':
        bprdepth = prdepth - 1;
        break;
    case '+':
        bprdepth = prdepth + 1;
        break;
    case '=':
        bprdepth = prdepth;
        stopvlag = 1;
        break;
    case '!':
        nulbp(adre);
        break;
    case 'g': /*snprintf(errbuf, sizeof (errbuf),"g %d",adre); erroutine();*/
        nulbp(adre);
        break;
    case 0xc:
    case 'R':
        refresh();
        rdcmd();
        break;
    case 'd':
        if (symtab[symp].symsect > 2)
            dmpadr(adre);
        else {
            snprintf(errbuf, sizeof (errbuf), "Cannot dump this label");
            erroutine();
        }
        dump();
        break;
    case 'b':
        zetbp(lndotarr[adre]);
        rdcmd();
        break;
    case 'c':
        clearbp(lndotarr[adre]);
        rdcmd();
        break;
    case 'n':
        nulbp(dotlnarr[lndotarr[dotlnarr[(PC - 1)] + 1]]);
        break;
    case 'x':
    case 'X':
    case '*':
        instrcount = adre;
        break;
    default:
        stopvlag = 255;
    }
}

/* Read string ??*/
int rdstrg( void ) {
    int i, j, stradr, k, syk;
    char *p, *q, c, cc;
    i = 0;
    p = cmdline;
    q = tringfield + 90;
    while ((c = *p++))
        if (c == '!' || c == '/' || c == '+')
            break;
        else {
            i++;
            *q++ = c;
        }
    if ((c == '/') && (*p != '+'))
        *(--p) = '0';
    *q = '\0';

    stradr = hashstring(tringfield + 90);
    symp = symhash[stradr];
    if (i > 8)
        i = 8;
    syk = -1;
    while (symp != -1) {

        /*if(!strncmp(tringfield+90, symtab[symp].symbol,i)) { syk = symp;
        break;}
        else {symp = symtab[symp].nextsym;}*/
        if (!strncmp(tringfield + 90, symtab[symp].symbol, i)) {
            syk = symp;
            if (i == strlen(symtab[symp].symbol))
                break;
        }
        symp = symtab[symp].nextsym;
    }
    symp = syk; /*april*/
    if (symp < 0) {
        snprintf(errbuf, sizeof (errbuf), "No Match");
        erroutine();
        return (-1);
    }
    for (k = 0; k < 18; k++)
        tringfield[k + 90] = ' ';
    tringfield[98] = '+';
    for (k = 0; k < 8; k++)
        if ((cc = symtab[symp].symbol[k]) > 32)
            tringfield[k + 90] = cc;
        else
            break;

    if (symtab[symp].symsect > 2)
        stradr = symtab[symp].symvalue;
    else if (symtab[symp].symsect == 2)
        stradr = symtab[symp].lnr;
    j = -1;
    if (c == '\0' || c == '!') {
        cmdchar = '!';
        j = 0;
    }
    if (j) {
        while (*p == '+' || *p == '\t' || *p == ' ')
            p++;
        if (*p == '\0' || *p == '!') {
            cmdchar = '!';
            j = 0;
        }
    }
    if (j) {
        if (*p < '0' || *p > '9') {
            snprintf(errbuf, sizeof (errbuf), "cmd constant expected.");
            erroutine();
            sprintf("%-55.55s", "  ");
            return (-1);
        }
        sscanf(p, "%d%1s", &j, &cmdchar);
    }
    if (symtab[symp].symsect == 2) {
        if (cmdchar == '!')
            cmdchar = 'g';
        sprintf(tringfield + 99, "%2d", j);
    } else {
        if (cmdchar == '!')
            cmdchar = 'd';
        sprintf(tringfield + 99, "%-4d=%04x:", j, (stradr + j));
    }
    return (stradr + j);
}

/* Read address ?? */
int rdadr( void ) {
    int i;
    sscanf(cmdline, "%d%1s", &i, &cmdchar);
    if ((cmdchar == '!') && (symtab[symp].symsect == 2))
        cmdchar = 'g';
    return (i);
}

/* Read comandline ?? */
void rdcline( int c ) {
    char *p;
    p = cmdline;
    while (c != '\n') {
        if (c == EOF)
            break;
        *p++ = c;
        c = getchcmd();
    }
    *p++ = '\0';
    *p = '\0';
    sprintf(window[14], "%-18.18s", cmdline);
    p--;
    *p = '!';
}

void winupdate( void ) {
    int i, j, k, l;
    char *p, *q;
    sprintf(window[0] + 4, "%02x", cs & 0Xffff);
    sprintf(window[0] + 18, "%03x", ds & 0Xffff);
    sprintf(window[1] + 3, "%02x", ah);
    sprintf(window[1] + 9, "%02x", al);
    sprintf(window[1] + 15, "%6d", ax);
    sprintf(window[2] + 3, "%02x", bh);
    sprintf(window[2] + 9, "%02x", bl);
    sprintf(window[2] + 15, "%6d", bx);
    sprintf(window[3] + 3, "%02x", ch);
    sprintf(window[3] + 9, "%02x", cl);
    sprintf(window[3] + 15, "%6d", cx);
    sprintf(window[4] + 3, "%02x", dh);
    sprintf(window[4] + 9, "%02x", dl);
    sprintf(window[4] + 15, "%6d", dx);
    sprintf(window[5] + 4, "%04x", sp & 0Xffff);
    sprintf(window[6] + 4, "%04x", bp & 0Xffff);
    sprintf(window[7] + 4, "%04x", si & 0Xffff);
    sprintf(window[8] + 4, "%04x", di & 0Xffff);
    sprintf(window[7] + 13, "%04ld:PC", (PC) - 1);
    /* Note: (PC)-1. The next instruction initial byte is fetched before the
     * dump*/
    sprintf(window[8] + 10, "           ");

    i = dotlnarr[(PC) - 1];
    j = lnsymarr[i];
    if (j > nsymtab - 3) {
        fprintf(stderr, "\nNo BSS or no head label?\n");
        refresh(); /*exit(1);*/
    }
    sprintf(window[8] + 10, "%s+%1d", symtab[j].symbol, i - symtab[j].lnr);
    window[6][12] = (ovf) ? 'v' : '-';
    window[6][14] = (dirf) ? '<' : '>';
    window[6][16] = (signf) ? 'n' : 'p';
    window[6][18] = (zerof) ? 'z' : '-';
    window[6][20] = (cf) ? 'c' : '-';
    for (j = 0; j < 9; j++) {
        fseek(L, (int)lnfilarr[i + j - 6], 0);
        p = window[j] + 32;
        gtabstr(48, p, L);
    }
    for (i = 0; i < 4; i++)
        for (j = 0; j < 58; j++)
            window[15 - i][j + 22] = outveld[i][j];
    for (i = 0; i < 7; i++)
        sprintf(window[17 + i], "%s", datadarr[i]);
    l = prdepth;
    j = (maxsp - sp > 18) ? sp : maxsp - 18;
    j &= 0xffff;
    p = memory + j + (ss << 4);

    for (i = 0; i < 9; i++) {
        if (j < sp) {
            p += 2;
            sprintf(window[i] + 23, "      ");
        } else {
            k = *p++ & 255;
            k |= ((*p++ & 255) << 8);
            if (j == sp)
                sprintf(window[i] + 23, "=>%04x", k);
            else
                sprintf(window[i] + 23, "  %04x", k);
            if (j == prstckpos[l]) {
                window[i][23] = (char)(l + 48);
                l--;
            }
        }
        j += 2;
    }

    l = (prdepth > 2) ? prdepth - 2 : 1;
    for (i = 12; i > 9; i--) {
        if (l > (int)prdepth)
            sprintf(window[i], "                   ");
        else {
            j = stckprdepth[l];
            k = lnsymarr[j];
            sprintf(window[i], "%1d <= %-8s + %3d", l, symtab[k].symbol,
                    j - symtab[k].lnr);
        }
        l++;
    }
    p = inbuf;
    q = window[11] + 22;
    *q++ = 'I';
    *q++ = ' ';
    while (p < inbpu - 85)
        p += 55;
    while ((j = (int)(*p)) != '\n') {
        if (*p == '\0')
            break;
        if ((q >= window[11] + 75) && (q < window[12])) {
            *q++ = ' ';
            *q++ = ' ';
            *q++ = ' ';
            q = window[12] + 24;
            window[12][22] = 'I';
        }
        if (p == inbpu) {
            *q++ = '-';
            *q++ = '>';
        }
        if (j == 0 || q > window[12] + 75)
            break;
        if (j < ' ') {
            *q++ = '^';
            j += 64;
        }
        *q++ = j;
        p++;
    }
    if (p == inbpu && *p == '\n') {
        *q++ = '-';
        *q++ = '>';
    }
    if ((inbpu != inbpl) && (*p == '\n')) {
        *q++ = '\\';
        *q++ = 'n';
    }
    if (*(inbpu - 1) == '\n') {
        *q++ = '\\';
        *q++ = 'n';
        *q++ = '-';
        *q++ = '>';
    }
    while (q < window[12] - 1)
        *q++ = ' ';
    if (q > window[12])
        while (q < window[13] - 1)
            *q++ = ' ';
    p = window[0] - 1;
    for (i = 0; i < 1944; i++)
        if (!(*(++p)))
            *p = ' ';
    immain();
    mvcur(15, 0);
}

void gtabstr( int i, char *a, FILE *f ) {
    int j, c;
    j = 0;
    while (j < i) {
        c = getc(f);
        if (c == EOF || c == '\r' || c == '\n')
            break;
        if (c == '\t') {
            if (j % 8 != 7)
                ungetc(c, f);
            c = ' ';
        }
        j++;
        *a++ = c;
    }
    while (j++ < i)
        *a++ = ' ';
}

void newgpfield( void ) {
    int i, j;
    for (i = 3; i > 0; i--)
        for (j = 0; j < 58; j++)
            outveld[i][j] = outveld[i - 1][j];
    for (j = 0; j < 58; j++)
        outveld[0][j] = ' ';
}

void nextput( int c ) {
    if (c == '\n') {
        nextput('\\');
        nextput('n');
        puthp = -1;
        return;
    }
    if (puthp > 57)
        puthp = -1;
    if (puthp < 0) {
        newgpfield();
        puthp = 0;
        nextput('>');
        nextput(' ');
    }
    if (c < ' ') {
        outveld[0][puthp++] = '^';
        c += 64;
    }
    if (c != '\n')
        outveld[0][puthp++] = c;
}

int getchcmd( void ) {
    int i;
    if ((i = getc(CMD)) != EOF) {
        if (i != '\r')
            return (i);
        else
            return (getchcmd());
    }
    if (cmdfl) {
        fclose(CMD);
        CMD = stdin;
        cmdfl = 0;
        i = getchcmd();
    }
    if (i != '\r')
        return (i);
    else
        return (getchcmd());
}

int getchbp( void ) {
    int i;
    char *p;
    if (inbpl == inbpu) {
        mvcur(11, 24);
        inbpl = inbpu = inbuf;
        if (traceflag && !(inpfl)) {
            snprintf(errbuf, sizeof (errbuf), "Input expected");
            erroutine();
            p = inbuf;
            *p++ = '\n';
            *p++ = '\0';
            winupdate();
            mvcur(11, 24);
        }
        while ((i = getc(INP)) != EOF) {
            if (i == '\r')
                continue;
            *inbpl++ = i;
            if (i == '\n')
                break;
        }
        if (i == EOF) {
            if (inpfl > 0) {
                fclose(INP);
                inpfl = 0;
                INP = stdin;
                return (getchbp());
            } else if (inpfl) {
                snprintf(errbuf, sizeof (errbuf), "Second time end of input so exit");
                erroutine();
                exit(0);
            } else {
                fclose(stdin);
                if ( fopen("/dev/tty", "rb") == NULL) {
                    puts("Can't open /dev/tty");
                }
                else {
                    inpfl--;
                return (i);
                }
            }
        }
    }
    return ((int)*inbpu++);
}

void meldroutine( void ) {
    //~ char *p;
    //~ int i, aa;
    if (traceflag) {
        errbuf[11] = ' ';
        errbuf[12] = ' ';
        errbuf[13] = ' ';
        mvcur(10, 24);
        printf("%s", errbuf);
        mvcur(10, 78);
        printf("\n");
        fprintf(stderr, "\n");
        sprintf(window[10] + 22, "M %-55.55s", errbuf);
        winupdate();
    } else
        fprintf(stderr, "%s\n", errbuf);
}

void erroutine( void ) {
    char *p;
    int i, aa;
    if (traceflag) {
        p = errbuf;
        aa = 0;
        for (i = 0; i < 55; i++)
            if (*p++ <= '\n') {
                p--;
                *p++ = ' ';
            } else if (*p == '\0' || *p == '\n')
                aa++;
            else if (aa)
                *p++ = ' ';
        *p = '\0';

        mvcur(10, 24);
        //~ viscursor();
        printf("%s", errbuf);
        //~ inviscur();
        mvcur(10, 78);
        printf("\n");
        //~ fprintf(stderr, "");
        sprintf(window[10] + 22, "E %-55.55s", errbuf);
        winupdate();
        errflag = 1;
    } else
        fprintf(stderr, "%s\n", errbuf);
}

void spare( word t ) {
    snprintf(errbuf, sizeof (errbuf), "8086 undefined instruction %0X", t & 0xff);
    erroutine();
}
void notim( word t ) {
    snprintf(errbuf, sizeof (errbuf), "Instruction %0X not implemented", t & 0xff);
    erroutine();
}
void interrupt( int t ) {
    snprintf(errbuf, sizeof (errbuf), "Interrupt %0X. Bad division?", t & 0xff);
    erroutine();
}
void panic(char *s) {
    snprintf(errbuf, sizeof (errbuf), "%s", s);
    erroutine();
    exit(EXIT_FAILURE);
}

void bitmapdump( int b, int h, char *buff ) {
    if (termbitsize == 2) {
        if ((bituit = fopen("tERMbITMAP", "wb")) == NULL) {
            fprintf(stderr, "Kan tERMbITMAP niet openen\n");
            exit(EXIT_FAILURE);
        }
    } else {
        if ((bituit = fopen("tERMbITmAP", "wb")) == NULL) {
            fprintf(stderr, "Kan tERMbITmAP niet openen\n");
            exit(EXIT_FAILURE);
        }
    }
    schrijfmap(b, h, termbitsize, buff, bituit);
    fclose(bituit);
    if (termbitsize == 2)
        snprintf(bmbuf, sizeof (bmbuf), ".c configure -bitmap @lEEGbITMAP\n");
    else
        snprintf(bmbuf, sizeof (bmbuf), ".c configure -bitmap @lEEGbITmAP\n");
    schrijf();

    if (termbitsize == 2)
        snprintf(bmbuf, sizeof (bmbuf), ".c configure -bitmap @tERMbITMAP\n");
    else
        snprintf(bmbuf, sizeof (bmbuf), ".c configure -bitmap @tERMbITmAP\n");
    schrijf();
}

void bitmapopen( int b, int h, int s ) {
    /*FAKE SYSTEM CALL TO OPEN A BITMAP FOR OPGAVE 1 */
    //int i;
    if (pipe(pfildes) < 0) {
        fprintf(stderr, "Kan geen pipe creeren\n");
        exit(EXIT_FAILURE);
    }
    if ((pnr = fork()) < 0) {
        fprintf(stderr, "Kan niet vorken\n");
        exit(EXIT_FAILURE);
    }
    if (pnr == 0) {
        dup2(pfildes[0], 0);
        //system("exec /usr/local/bin/wish");
        exit(0);
    }
    termbitsize = 1;
    if (s == 2)
        termbitsize = 2;

    if (termbitsize == 2) {
        if ((bituit = fopen("lEEGbITMAP", "wb")) == NULL) {
            fprintf(stderr, "Kan lEEGbITMAP niet openen\n");
            exit(EXIT_FAILURE);
        }
    } else {
        if ((bituit = fopen("lEEGbITmAP", "wb")) == NULL) {
            fprintf(stderr, "Kan lEEGbITmAP niet openen\n");
            exit(EXIT_FAILURE);
        }
    }
    schrijfmap(b, h, termbitsize, bmbuf + 800, bituit);
    fclose(bituit);

    snprintf(bmbuf, sizeof (bmbuf), "#!/usr/local/bin/wish -f\n. configure -background gray\n");
    schrijf();
    if (termbitsize == 2) {
        snprintf(bmbuf, sizeof (bmbuf), ". configure -width 591\n. configure -height 509\n");
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), "button .b -text %cexit window %c", '"', '"');
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), "  -font *-helvetica-bold-r-normal--*-180-* ");
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), " -command %cdestroy .%c\n", '"', '"');
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), "place .b -x 4 -y 4 -relwidth 0.32 -height 1.1c\n");
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), "label .c -bitmap @lEEGbITMAP\nplace .c -x 4 -y 1.4c\n");
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), "button .d -text %cdisplay new%c ", '"', '"');
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), "-font *-helvetica-bold-r-normal--*-180-* -command");
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), " %c.c configure -bitmap @tERMbITMAP%c\n", '"', '"');
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), "place .d -x 200 -y 4 -relwidth 0.32 -height 1.1c\n");
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), "button .e -text %cclear window %c ", '"', '"');
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), "-font *-helvetica-bold-r-normal--*-180-* -command");
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), " %c.c configure -bitmap @lEEGbITMAP%c\n", '"', '"');
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), "place .e -x 396 -y 4 -relwidth 0.32 -height 1.1c\n");
        schrijf();
    } else {
        snprintf(bmbuf, sizeof (bmbuf), ". configure -width 302\n. configure -height 266\n");
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), "button .b -text %cexit window %c", '"', '"');
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), "  -font *-helvetica-bold-r-normal--*-120-* ");
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), " -command %cdestroy .%c\n", '"', '"');
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), "place .b -x 2 -y 3 -relwidth 0.32 -height 0.7c\n");
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), "label .c -bitmap @lEEGbITmAP\nplace .c -x 3 -y 0.9c\n");
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), "button .d -text %cdisplay new%c ", '"', '"');
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), "-font *-helvetica-bold-r-normal--*-120-* -command");
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), " %c.c configure -bitmap @tERMbITmAP%c\n", '"', '"');
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), "place .d -x 101 -y 3 -relwidth 0.32 -height 0.7c\n");
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), "button .e -text %cclear window %c ", '"', '"');
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), "-font *-helvetica-bold-r-normal--*-120-* -command");
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), " %c.c configure -bitmap @lEEGbITmAP%c\n", '"', '"');
        schrijf();
        snprintf(bmbuf, sizeof (bmbuf), "place .e -x 200 -y 3 -relwidth 0.32 -height 0.7c\n");
        schrijf();
    }
    snprintf(bmbuf, sizeof (bmbuf), ".c configure -background black -foreground white\n");
    schrijf();
    snprintf(bmbuf, sizeof (bmbuf), ".b configure -background black -foreground white\n");
    schrijf();
    snprintf(bmbuf, sizeof (bmbuf), ".d configure -background black -foreground white\n");
    schrijf();
    snprintf(bmbuf, sizeof (bmbuf), ".e configure -background black -foreground white\n");
    schrijf();
}

/* Write ?? */
void schrijf( void ) {
    int j;
    char *p;
    p = bmbuf;
    j = 0;
    while (*p++ > '\0')
        j++;
    if (write(pfildes[1], bmbuf, j) == -1) {
        puts("Write fail");
    }
}

/*Mirror ??*/
int spiegel( int m, int n ) {
    int i, j, k, l;
    if (m == 0) {
        i = 1;
        j = 128;
        l = 0;
        for (k = 0; k < 8; k++) {
            if ((i & n) > 0)
                l |= j;
            i <<= 1;
            j >>= 1;
        }
    } else if (m == 1) {
        i = 16;
        j = 128;
        l = 0;
        for (k = 0; k < 4; k++) {
            if ((i & n) > 0)
                l |= j;
            j >>= 1;
            if ((i & n) > 0)
                l |= j;
            j >>= 1;
            i <<= 1;
        }
    } else {
        i = 1;
        j = 128;
        l = 0;
        for (k = 0; k < 4; k++) {
            if ((i & n) > 0)
                l |= j;
            j >>= 1;
            if ((i & n) > 0)
                l |= j;
            j >>= 1;
            i <<= 1;
        }
    }
    /* if(l>0) fprintf(stderr,"l %x n %x l %d n %d m %d\n",l,n,l,n,m);*/
    return (l);
}

/* Writemap ??*/
void schrijfmap( int b, int h, int s, char *buf, FILE *uitf ) {
    int i, j, k, l, m, c;
    char *p, *q;
    if (b % 8 != 0) {
        fprintf(stderr, "Bitmap breedte hoort een heel aantal bytes te zijn\n");
        exit(EXIT_FAILURE);
    }
    fprintf(uitf, "#define noname_width %d\n", b * s);
    fprintf(uitf, "#define noname_height %d\n", h * s);
    fprintf(uitf, "static char noname_bits[] = {\n ");
    p = buf;
    b >>= 3;
    k = b * h * s * s - 1;
    m = 1;
    for (i = 0; i < h; i++) {
        q = bmbuf;
        for (j = 0; j < b; j++)
            if (termbitsize == 2) {
                c = *p++;
                *q++ = spiegel(1, c);
                *q++ = spiegel(2, c);
            } else {
                c = *p++;
                *q++ = (255 & spiegel(0, c));
            }
        for (l = 0; l < s; l++) {
            q = bmbuf;
            for (j = 0; j < b * s; j++) {
                fprintf(uitf, "0x%02x", (255 & *q++));
                if (k == 0)
                    fprintf(uitf, "};\n");
                else {
                    putc(',', uitf);
                    if ((m % 15) == 0)
                        fprintf(uitf, "\n ");
                    k--;
                    m++;
                }
            }
        }
    }
}

void prut(char u, char v) {
    fprintf(stderr, "ah en al  %d %d     %x %x    %o %o\n", (int)u, (int)v,
            (int)u, (int)v, (int)u, (int)v);
}


int loadBinary(char *binaryFile) {
    int i, ii, j, k, sections, outrelo, loadl, strl, *pi;
    char *p;

    p = binaryFile;

    for (i = 0; i < 100; i++)
        if ((j = *p++) == '.' || j == '\0')
            break;
    *(--p) = 0;

    strcpy(basename, binaryFile);
    snprintf(fnameS, sizeof (fnameS), "%s.s", basename);
    snprintf(fname88, sizeof (fname88), "%s.88", basename);
    snprintf(fnameL, sizeof (fnameL), "%s.#", basename);

    if ((prog = fopen(fname88, "rb")) == NULL) {
		fprintf(stderr, "\e[1;31mError: Interpreter 8088 could not find file %s\n\e[00m", fname88);
		exit(EXIT_FAILURE);
	}

    if ((stat(fnameS, astat)) == -1 ) {
		fprintf(stderr, "\e[1;31mWarning: Does %s exist?\n\e[00m", fnameL);
		exit(EXIT_FAILURE);
	}

    t1 = astat[0].st_mtime;

    if (stat(fname88, astat)) {
        fprintf(stderr, "\e[1;31mWarning: Does %s exist?\n\e[00m", fname88);
        exit(EXIT_FAILURE);
    } else
        t2 = astat[0].st_mtime;

    if (t2 < t1) {
        fprintf(stderr, "\e[1;31mWarning: %s is older than %s.\n\e[00m", fname88, fnameS);
    }

    if (traceflag) {
        snprintf(fnameS, sizeof (fnameS), "%s.$", basename);
        //~ snprintf(fnameL, sizeof (fnameL), "%s.#", basename);
        snprintf(fnamei, sizeof (fnamei), "%s.i", basename);
        snprintf(fnamet, sizeof (fnamet), "%s.t", basename);

        if ((L = fopen(fnameL, "r")) == NULL) {
            fprintf(stderr, "Cannot open %s\n", fnameL);
            exit(EXIT_FAILURE);
        }

        i = 0;
        j = 0;

        while (fscanf(L, "%d %d", &loadl, &strl) > 0) {
            while (i <= loadl)
                lndotarr[i++] = strl;
            while (j <= strl)
                dotlnarr[j++] = loadl;
        }

        if ((INP = fopen(fnamei, "r")) != NULL)
            inpfl = 1;
        else {
            inpfl = 0;
            INP = stdin;
        }

        if ((CMD = fopen(fnamet, "r")) != NULL)
            cmdfl = 1;
        else {
            cmdfl = 0;
            CMD = stdin;
        }

        fclose(L);

        if ((L = fopen(fnameS, "rb")) == NULL) {
            fprintf(stderr, "Cannot open %s\n", fnameS);
            exit(EXIT_FAILURE);
        }

        strl = 0;
        lnfilarr[1] = lnfilarr[0] = 0;
        stckprdepth[0] = 1;

        for (i = 2; i < 0XFF8; i++) {
            while ((j = getc(L)) != EOF) {
                strl++;
                if (j == '\n')
                    break;
            }
            if (j == EOF)
                break;
            lnfilarr[i] = strl;
        }

        maxln = i;
        rewind(L);

        for (i = 0; i < 7; i++)
            datadm[i] = NULL;

        puthp = 0;
    }

    pcx = p = memory;
    ss = ds = es = 0;

    CS(0);

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 80; j++)
            datadarr[i][j] = ' ';
        datadarr[i][80] = '\0';
    }

    datadp = 0;
    lfptr = 0;

    if ((i = getsh(prog)) != MAGIC) {
        fprintf(stderr, "wrong magic load file\n");
        return (1);
    }

    i = getsh(prog);        	/*stamps unimportant */
    i = getsh(prog);        	/*flags unimportant */
    sections = getsh(prog); 	/*number of load sections*/
    outrelo = getsh(prog);  	/*number of reloactable parts*/
    nsymtab = getsh(prog);  	/*number of entries in symbol table*/
    loadl = getint(prog);   	/*length of core image in load file*/
    strl = getint(prog);    	/*length of string section in load file*/

    j = 0;

    for (i = 0; i < sections; i++) {
        segmhead[i].startad = getint(prog);
        j += (segmhead[i].lengte = getint(prog));
        if (i == 0)
            codelength = segmhead[i].lengte;
        segmhead[i].fstart = getint(prog);
        segmhead[i].flen = getint(prog);
        segmhead[i].align = getint(prog);

        if (j > 99000) {
            fprintf(stderr, "Insufficient amount of memory %x\n", j);
            exit(EXIT_FAILURE);
        }
    }

    ss = ((j + 31) >> 4); /* stack segment behind loaded text, data, bss segments */

    for (i = 0; i < sections; i++) {
        if (lfptr > segmhead[i].fstart) {
            fprintf(stderr, "Misalignment in load file.\n");
            return (1);
        }
        if (i < 2)
            p = memory + segmhead[i].startad + (ds << 4);
        while ((p - memory) % segmhead[i].align)
            p++;
        if (i > 1)
            segmhead[i].startad = (p - (ds << 4)) - memory;
        for (j = 0; j < segmhead[i].flen; j++) {
            *p++ = getc(prog);
            lfptr++;
        }
        if (!i) {
            es = ds = (segmhead[i].lengte + 15) >> 4;
            bp = sp = maxsp = 0x7FF8;
        }

    }
    for (i = 0; i < outrelo; i++) { /* reads relocation information */
        relocarr[i].typ = getc(prog);
        relocarr[i].sct = getc(prog);
        relocarr[i].smb = getsh(prog);
        relocarr[i].adrs = getint(prog);
    }
    if (traceflag) {
        for (i = 0; i < 32; i++) {
            bparr[i].pcp = 0;
            bparr[i].bprt = *pcx;
        }
    }
    /*Break point fields initialised on zero field. Next initialise symbol table*/
    for (i = 0; i < MAXSYMTAB; i++) {
        symtab[i].symvalue = 0;
        symtab[i].symbol = nulsymbol;
        symtab[i].nextsym = -1;
        symtab[i].lnr = 0;
        symtab[i].symsect = 0;
    }
    for (i = 0; i < 32; i++)
        symhash[i] = -1;
    for (i = 0; i < nsymtab; i++) {
        symtab[i].nextsym = getint(prog);
        j = getint(prog);
        j &= 255;
        symtab[i].symsect = (char)(j);
        symtab[i].symvalue = getint(prog);
        if (j == 2)
            symtab[i].lnr = dotlnarr[symtab[i].symvalue];
        else if (j > 3)
            symtab[i].symvalue += segmhead[(j & 255) - 2].startad;

    }
    j = ftell(prog);
    for (i = 0; i < strl; i++) {
        k = getc(prog);
        stringfield[i] = (char)(k & 255);
    } /*augustus*/
    for (i = 0; i < nsymtab; i++) {
        symtab[i].nextsym -= j;
        symtab[i].symbol = stringfield + symtab[i].nextsym;
        symtab[i].nextsym = -1;
    }
    p = stringfield;
    i = 0;
    while ((i++ < 8190) && ((j = getc(prog)) != EOF))
        *p++ = j;
    for (i = 0; i < nsymtab; i++) {
        j = hashstring(symtab[i].symbol);
        pi = &symhash[j];
        while (*pi >= 0)
            pi = &(symtab[*pi].nextsym);
        *pi = i;
    }
    prdepth = 0;
    for (i = 0; i < 0X800; i++)
        lnsymarr[i] = nsymtab - 2;
    for (i = 0; i < nsymtab - 2; i++) {
        if (symtab[i].symsect == 2)
            symlcorr(i);
    }
    j = 0;
    for (i = 0; i <= maxln; i++) {
        while ((j < nsymtab)) {
            if ((symtab[j].symsect != 2) || (symtab[j].lnr < i) ||
                (symtab[j].symbol[0] == '.')) {
                j++;
                continue;
            }
            if (symtab[j].lnr == i)
                k = j;
            break;
        }
        lnsymarr[i] = k;
        if (k >= 0)
            for (ii = k + 1; ii <= nsymtab; ii++) {
                if ((symtab[ii].symsect == 2) && (symtab[ii].lnr == i))
                    lnsymarr[i] = ii;
            }
    }
    for (i = 0; i < outrelo; i++)
        relocate(i);
    if (traceflag) {
        p = window[0];
        for (i = 0; i < 1944; i++)
            *p++ = ' ';
        p = inbuf;
        for (i = 0; i < 1024; i++)
            *p++ = '\0';
        for (i = 1; i < 27; i++)
            fprintf(stderr, "\n");
        winfirst();
        inbpl = inbpu = inbuf;
        nextput('>');
        nextput(' ');
    } else
        INP = stdin;

    //~ argv++;
    //~ argc--;
    //~ if (argc) {
        //~ ii = argc + 4;
        //~ for (i = 0; i < argc; i++)
            //~ ii += strlen(argv[i]);
        //~ ii &= 0Xffe;
        //~ maxsp -= ii;
        //~ k = maxsp + 2;
        //~ p2 = memory + k + (ss << 4);
        //~ p1 = p2 - 4 - (argc << 1);
        //~ bp = sp = maxsp - 2 - (argc << 1);
        //~ *p1++ = argc & 255;
        //~ *p1++ = (argc >> 8) & 255;
        //~ for (i = 0; i < argc; i++) {
            //~ *p1++ = k & 255;
            //~ *p1++ = (k >> 8) & 255;
            //~ j = strlen(argv[i]) + 1;
            //~ strcpy(p2, argv[i]);
            //~ p2 += j;
            //~ k += j;
        //~ }
//~
    //~ }
    return (0);
}

void usage(char *progname)
{
    fprintf(stderr, "Usage: %s <option> <file>\n"
           "  -t    trace a file\n"
           "  -r,   interpret a file without displaying the tracer window\n",
	       progname);

    exit(EXIT_FAILURE);
}

int main( int argc, char *argv[] ) {
    sp = 0;
    ss = 0;
    cs = 0;
    pcx = memory;

    char *binaryFile;

    if (argc != 3)
	    usage(argv[0]);

    if (strcmp(argv[1], "-t") == 0)
        stopvlag = traceflag = 1;
	else if (strcmp(argv[1], "-r") == 0)
	    stopvlag = traceflag = 0;
	else
        usage(argv[0]);

    binaryFile = argv[2];

    loadBinary(binaryFile);
    fclose(prog);
    interp();

    return 0;
}
