#ifndef _88_H
#define	_88_H

#include <stdint.h>                     // for uint8_t
#include <sys/types.h>                  // for int16_t

#define MEMORY_SIZE (1024*1024)    /* maximum addressable memory is 1MiB */

char memory[MEMORY_SIZE];

typedef int16_t word;           /* type word must be 16 bits */
typedef int16_t adr;            /* unsigned 16-bit quantity */
typedef uint8_t unchr;          /* unsigned 8-bit */

typedef struct {
    unchr lo;
    unchr hi;
} pair;

typedef union {
    pair b;
    word w;
} reg;

typedef union {
    unchr rc[16];
    word rw[8];
} REG;

REG r;

// 8-bit General purpose registers
#define AL 0
#define AH 1
#define BL 2
#define BH 3
#define CL 4
#define CH 5
#define DL 6
#define DH 7

// 16-bit register
#define AX 0
#define BX 1
#define CX 2
#define DX 3
#define SI 4 // index registers
#define DI 5
#define BP 6
#define SP 7

#define ax r.rw[AX]
#define bx r.rw[BX]
#define cx r.rw[CX]
#define dx r.rw[DX]
#define si r.rw[SI]
#define di r.rw[DI]
#define bp r.rw[BP]
#define sp r.rw[SP]

#define al r.rc[AL]
#define ah r.rc[AH]
#define bl r.rc[BL]
#define bh r.rc[BH]
#define cl r.rc[CL]
#define ch r.rc[CH]
#define dl r.rc[DL]
#define dh r.rc[DH]

#define W00 AX /* Wxx used for submultiplexing, e.g. op 81 */
#define W01 CX
#define W02 DX
#define W03 BX
#define W04 SP
#define W05 BP
#define W06 SI
#define W07 DI

#define B00 AL
#define B01 CL
#define B02 DL
#define B03 BL
#define B04 AH
#define B05 CH
#define B06 DH
#define B07 BH

#define ea EA.w
#define ealo EA.b.lo
#define eahi EA.b.hi

#define ra RA.w
#define ralo RA.b.lo
#define rahi RA.b.hi

#define eop EOP.w
#define eoplo EOP.b.lo
#define eophi EOP.b.hi

#define rop ROP.w
#define roplo ROP.b.lo
#define rophi ROP.b.hi

#define ADDW 0 /* codes used for lazy condition code eval */
#define ADDB 1
#define ADCW 2
#define ADCB 3
#define INCW 4
#define INCB 5
#define SUBW 6
#define SUBB 7
#define SBBW 8
#define SBBB 9
#define DECW 10
#define DECB 11
#define BOOLW 12
#define BOOLC 13

/* Here are the values used in 'nextint' to tell which kind of interrupt next.*/
#define SEGOVER 1
#define CLOCK 2
#define TTYIN 3
#define TTYOUT 4
#define DISK 5
#define KBD 6
#define NDEV 8 /* number of I/O devices */

#define DIVIDEVEC 0
#define CLOCKVEC 8
#define KBDVEC 9
#define XT_WINI 13
#define DISKVEC 14 /* floppy */
#define SYS_VEC 32
#define TTYINVEC 35
#define TTYOUTVEC 36

/* I/O ports and related constants. */
#define PIT_C 0x00D6   /* output port to enable clock */
#define SIO_C 0x00DA   /* tty control port */
#define SIO_D 0x00D8   /* tty data port */
#define TIMER_2 0x0042 /* timer port 2 */
#define TIMER_3 0x0043 /* timer port 3 */
#define SIO_M 0x0043   /* tty port for enabling/disabling interrupt */
#define KEYBD 0x0060   /* keyboard data port */
#define PORT_B 0x0061  /* keyboard strobe port */

#define TXRDY 01
#define RXRDY 02
#define DXRDY 01
#define FROM_DISK 0
#define TO_DISK 1

/* Variables used by I/O. */
int ttystat;
int clkinterval;

reg EA, RA, EOP, ROP;
int ovf, dirf, intf, signf, zerof, cf; /* flag bits */
char *pcx;                             /* pcx = &m[ (cs<<4) + pc] */
char *pcx_save; /* pcx saved here at instruction start */
char *xapc;
char *eapc, *rapc;
word *rapw; /* eapw is unusable since it might be odd */
word *stkp; /* scratch variable used by PUSH and POP */
int mask;

adr cs, ds, ss, es; /* contents of segment registers */
adr xs, dsx, ssx;
long cs16; /* cs16 = 16*cs  (= cs<<4) */

unsigned timer, ticks, nextint, ints_pending;
long realtime; /* measured in mach instr (5 microsec each) */

struct intstruct {
    long int_time;  /* time of next interrupt (in mach instrs) */
    int int_status; /* status information */
    int int_vector;
} intstruct[NDEV];

#define ENABLED 01

long l, l1, l2;        /* scratch variables used for setting carry */
short x, y, z;         /* used in lazy condition code evaluation */
unchr xc, yc, zc;      /* ditto */
int operand;
int ccvalid; /* ditto */
int anything;          /* nonzero if any dumping or tracing on */
int whendump;          /* controls dumping */
int whatdump;          /* controls dumping */
long xx;               /* scratch variable used for mem checking */
unchr stopvlag, dumpt; /* ew dumping vlag and saved t */


int traceflag, instrcount, codelength; // procdepth(), breakpt(),
extern char errbuf[];

void interp( void );

#endif /* _88_H */
