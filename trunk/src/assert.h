// assert.h
// LMNO LALR(1) parser generator
//
// Copyright ©2010 Brigham Toskin
// (Based on LEMON v1 parser generator, public domain)
//////////////////////////////////////////////////////


void myassert();
#ifndef NDEBUG
#  define assert(X) if(!(X))myassert(__FILE__,__LINE__)
#else
#  define assert(X)
#endif

