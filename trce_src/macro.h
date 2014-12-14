/* Macros for memory references. */
#ifndef _MACRO_H
#define _MACRO_H

#include "88.h"

#define M memory

//~ #define WSTORE(x) wstore(x)
//~ #define RAPWSTORE(x) rapwstore(x)
//~ #define XSTORE(x) xstore(x)

#define WSTORE(x) {                                                            \
    *eapc++ = x;                                                               \
    *eapc = x >> 8;                                                            \
}

#define RAPWSTORE(x) {                                                         \
	*rapw = w;                                                                 \
}

#define XSTORE(x) {                                                            \
    *eapc = *x;                                                                \
    *(eapc + 1) = *(x + 1);                                                    \
}


#define MEM(x, b, t) x = M + (b << 4) + (unsigned short)t

#define CSMEM(x, t) x = M + cs16 + (unsigned short)t

#define STACKPTR(t)                                                            \
    xx = ((long)ss << 4) + (unsigned short)sp;                                 \
    t = (word *)(M + xx);

#define BSTORE(x) *eapc = x


#define MOV16                                                                  \
    *eapc++ = *pcx++;                                                          \
    *eapc++ = *pcx++

#define PC (pcx - M) - cs16
#define CS(x)                                                                  \
    cs = x;                                                                    \
    cs16 = cs << 4;

#define WFETCH                                                                 \
    eoplo = *eapc++;                                                           \
    eophi = *eapc++

#define BFETCH eoplo = *eapc

/* Macros for handling operands. */
#define DISP8 eahi = ((char)(ealo = *pcx++) < 0) ? 0xFF : 0;
#define DISP16                                                                 \
    ealo = *pcx++;                                                             \
    eahi = *pcx++;
#define IMMED                                                                  \
    eoplo = *pcx++;                                                            \
    eophi = *pcx++
#define IMMED8 eoplo = *pcx++
#define IMMED8X eophi = ((char)(eoplo = *pcx++) < 0) ? 0xFF : 0
#define IMMED8Z                                                                \
    eoplo = *pcx++;                                                            \
    eophi = 0
#define RMCONST                                                                \
    roplo = *pcx++;                                                            \
    rophi = *pcx++
#define BRMCONST roplo = *pcx++;
#define XRMCONST rophi = ((char)(roplo = *pcx++) < 0) ? 0xFF : 0

/* Macros for setting condition codes. * /
#define SZONLY(a)          ccvalid= 0; x= a; operator= BOOLW
#define BSZONLY(a)         ccvalid= 0; xc= a; operator= BOOLC
#define LAZYCC(a,b,op)     ccvalid= 0; x= a; y= b; operator= op
#define BLAZYCC(a,b,op)    ccvalid= 0; xc= a; yc= b; operator= op
#define LAZYCC3(a,b,c,op)  ccvalid= 0; x= a; y= b; z= c; operator= op
#define BLAZYCC3(a,b,c,op) ccvalid= 0; xc= a; yc= b; zc= c; operand = op;*/
#define CC                                                                     \
    if (ccvalid == 0)                                                          \
    cc()
#define SZONLY(a)                                                              \
    x = a;                                                                     \
    operand = BOOLW;                                                           \
    cc()
#define BSZONLY(a)                                                             \
    xc = a;                                                                    \
    operand = BOOLC;                                                           \
    cc()
#define LAZYCC(a, b, op)                                                       \
    x = a;                                                                     \
    y = b;                                                                     \
    operand = op;                                                              \
    cc()
#define BLAZYCC(a, b, op)                                                      \
    xc = a;                                                                    \
    yc = b;                                                                    \
    operand = op;                                                              \
    cc()
#define LAZYCC3(a, b, c, op)                                                   \
    x = a;                                                                     \
    y = b;                                                                     \
    z = c;                                                                     \
    operand = op;                                                              \
    cc()
#define BLAZYCC3(a, b, c, op)                                                  \
    xc = a;                                                                    \
    yc = b;                                                                    \
    zc = c;                                                                    \
    operand = op;                                                              \
    cc()

/* Macros for stack operations. */
#define PUSH(x)                                                                \
    sp -= 2;                                                                   \
    STACKPTR(stkp);                                                            \
    *stkp = x
#define POP(x)                                                                 \
    STACKPTR(stkp);                                                            \
    x = *stkp;                                                                 \
    sp += 2

/* Macros for interrupt and PSW operations. */
#define FLAGWD(t)                                                              \
    CC;                                                                        \
    t = ((ovf << 11) + (dirf << 10) + (intf << 9) + (signf << 7) +             \
         (zerof << 6) + cf)

#define LOADFLAGS(t)                                                           \
    ovf = (t >> 11) & 1;                                                       \
    dirf = (t >> 10) & 1;                                                      \
    intf = (t >> 9) & 1;                                                       \
    signf = (t >> 7) & 1;                                                      \
    zerof = (t >> 6) & 1;                                                      \
    cf = t & 1;                                                                \
    ccvalid = 1

/* Macros for string operations. */
#define STRING                                                                 \
    MEM(xapc, ds, si);                                                         \
    MEM(eapc, es, di)
#define WDIRF(t) t += (dirf == 0) ? 2 : -2;
#define BDIRF(t) t += (dirf == 0) ? 1 : -1;
#define WSIDI                                                                  \
    if (dirf == 0) {                                                           \
        si += 2;                                                               \
        di += 2;                                                               \
    } else {                                                                   \
        si -= 2;                                                               \
        di -= 2;                                                               \
    }
#define BSIDI                                                                  \
    if (dirf == 0) {                                                           \
        si += 1;                                                               \
        di += 1;                                                               \
    } else {                                                                   \
        si -= 1;                                                               \
        di -= 1;                                                               \
    }

/* Miscellaneous macros. */
#define OVERRIDE(seg)                                                          \
    dsx = ds;                                                                  \
    ssx = ss;                                                                  \
    ds = seg;                                                                  \
    ss = seg;                                                                  \
    realtime += ticks - timer;                                                 \
    ticks = 2;                                                                 \
    timer = 2;                                                                 \
    nextint = SEGOVER

#define BITSEL(v1, n1, v2, n2)                                                 \
    v1 = (eop >> n1) & 1;                                                      \
    v2 = (eop >> n2) & 1
#define LOOP goto loop

#endif /* _MACRO_H */
