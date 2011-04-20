// assert.c
// LMNO LALR(1) parser generator
//
// Copyright ©2010 Brigham Toskin
// (Based on LEMON v1 parser generator, public domain)
//////////////////////////////////////////////////////


#include "global.h"


/*
 ** A more efficient way of handling assertions.
 */
void myassert(file,line)
char *file;
int line;
{
	fprintf(stderr,"Assertion failed on line %d of file \"%s\"\n",line,file);
	exit(1);
}
