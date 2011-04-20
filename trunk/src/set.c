// set.c
// LMNO LALR(1) parser generator
//
// Copyright ©2010 Brigham Toskin
// (Based on LEMON v1 parser generator, public domain)
//////////////////////////////////////////////////////


#include "global.h"


/*
 ** Set manipulation routines for the LMNO parser generator.
 */

static int size = 0;

/* Set the set size */
void SetSize(int n)
{
	size = n+1;
}

/* Allocate a new set */
char *SetNew()
{
	char *s;
	int i;
	s = (char*)malloc( size );
	if( s==0 )
	{
		extern void memory_error();
		memory_error();
	}
	for(i=0; i<size; i++)
		s[i] = 0;
	return s;
}

/* Deallocate a set */
void SetFree(char *s)
{
	free(s);
}

/* Add a new element to the set.  Return TRUE if the element was added
 ** and FALSE if it was already there. */
int SetAdd(char *s, int e)
{
	int rv;
	rv = s[e];
	s[e] = 1;
	return !rv;
}

/* Add every element of s2 to s1.  Return TRUE if s1 changes. */
int SetUnion(char *s1, char *s2)
{
	int i, progress;
	progress = 0;
	for(i=0; i<size; i++)
	{
		if( s2[i]==0 )
			continue;
		if( s1[i]==0 )
		{
			progress = 1;
			s1[i] = 1;
		}
	}
	return progress;
}
