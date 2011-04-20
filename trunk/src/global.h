// global.h
// LMNO LALR(1) parser generator
//
// Copyright ©2010 Brigham Toskin
// (Based on LEMON v1 parser generator, public domain)
//////////////////////////////////////////////////////

#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef __WIN32__
#   if defined(_WIN32) || defined(WIN32)
#	define __WIN32__
#   endif
#endif

#define PRIVATE static
//#define PRIVATE

#ifdef TEST
#define MAXRHS 5	   /* Set low to exercise exception code */
#else
#define MAXRHS 1000
#endif

char *msort();
extern void *malloc();

#include "action.h"
#include "assert.h"
#include "build.h"
#include "configlist.h"
#include "error.h"
#include "option.h"
#include "parse.h"
#include "plink.h"
#include "report.h"
#include "set.h"
#include "struct.h"
#include "table.h"
