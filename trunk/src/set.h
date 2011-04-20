// set.h
// LMNO LALR(1) parser generator
//
// Copyright ©2010 Brigham Toskin
// (Based on LEMON v1 parser generator, public domain)
//////////////////////////////////////////////////////


void  SetSize(/* int N */);			 /* All sets will be of size N */
char *SetNew(/* void */);			   /* A new set for element 0..N */
void  SetFree(/* char* */);			 /* Deallocate a set */

int SetAdd(/* char*,int */);			/* Add element to a set */
int SetUnion(/* char *A,char *B */);	/* A <- A U B, thru element N */

#define SetFind(X,Y) (X[Y])	   /* True if Y is in set X */

