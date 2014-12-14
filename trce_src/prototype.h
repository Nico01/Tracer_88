#include <stdio.h>
#include "88.h"

/* main.c prototype */
void dump( void );
void meldroutine( void );
void syscal( void );
void notim( word );
void spare( word );
void panic(char *s);
void interrupt( int );
void relocate( int );
int hashstring( char *p );
void symlcorr( int i );
void winupdate( void );
int getchbp( void );
int spint( void );
void returnax( int retval );
void nextput( int c );
void erroutine( void );

void bitmapdump( int b, int h, char *buff );
void bitmapopen( int b, int h, int s );

void cnulbp( void );
void dmpadr( int adre );
void pdmpadr( void );
void rdcmd( void );
void checkret( void );
void procdepth( int s );

void zetbp( short textdot );
void clearbp( short textdot );
void nulbp( int ln );
void breakpt( void );

int getchcmd( void );
void rdcline( int c );
int rdadr( void );
int rdstrg( void );
void gtabstr( int i, char *a, FILE *f );
void newgpfield( void );

void schrijfmap( int b, int h, int s, char *buf, FILE *uitf );
void schrijf( void );
int spiegel( int m, int n );

/*doscurs.h prototype*/
void winfirst( void );
int mvcur( int a, int b );
void immain( void );
void refresh( void );

int clearscreen( void );
void wingo( void );
