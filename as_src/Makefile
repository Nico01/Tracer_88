# $Header: proto.make,v 1.5 91/10/22 14:35:13 Jacobs Exp $
CC = gcc

SUF = o   # suffix of files produced with $(CC) -c

CFLAGS = -ggdb -std=c99 -Wall #-fsanitize=address -O1 -fno-omit-frame-pointer

CSRC = \
    comm3.c         \
    main.c          \
    comm5.c         \
    bigkeywh.c      \
    comm6.c         \
    comm7.c         \
    comm8.c         \
    wr.c

COBJ = \
    comm3.$(SUF)    \
    main.$(SUF)     \
    comm5.$(SUF)    \
    bigkeywh.$(SUF) \
    comm6.$(SUF)    \
    comm7.$(SUF)    \
    comm8.$(SUF)    \
    wr.$(SUF)

MACHSRC = \
    mach0.c         \
    mach1.c         \
    mach2.c         \
    mach3.c         \
    mach4.c         \
    mach5.c

COMM = \
    comm0.h         \
    comm1.h         \
    comm2.y         \
    $(CSRC)

all: as88

as88: $(COBJ) as.$(SUF)
	$(CC) $(COBJ) as.$(SUF) -o as88; \
	cp as88 ../bin/as88; cp as88 ../exercises/as88; cp as88 ../examples/as88

# as.c:	as.y
# 	yacc $(YFLAGS) as.y && mv y.tab.c as.c

$(COBJ): y.tab.h
$(COBJ): comm0.h mach0.c
$(COBJ): comm1.h mach1.c

as.$(SUF): as.c
	$(CC) -c $(CFLAGS) as.c
main.$(SUF): main.c
	$(CC) -c $(CFLAGS) main.c
comm3.$(SUF): comm3.c
	$(CC) -c $(CFLAGS) comm3.c
comm3.$(SUF): mach3.c
comm5.$(SUF): comm5.c
	$(CC) -c $(CFLAGS) comm5.c
comm6.$(SUF): comm6.c
	$(CC) -c $(CFLAGS) comm6.c
comm7.$(SUF): comm7.c
	$(CC) -c $(CFLAGS) comm7.c
comm8.$(SUF): comm8.c
	$(CC) -c $(CFLAGS) comm8.c
comm8.$(SUF): mach5.c
bigkeywh.$(SUF): bigkeywh.c
	$(CC) -c $(CFLAGS) bigkeywh.c

clean:
	rm -f *.$(SUF) as88 # as.[cy] y.tab.h
