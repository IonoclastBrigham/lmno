// option.h
// LMNO LALR(1) parser generator
//
// Copyright ©2010 Brigham Toskin
// (Based on LEMON v1 parser generator, public domain)
//////////////////////////////////////////////////////


struct s_options {
	enum { OPT_FLAG=1,  OPT_INT,  OPT_DBL,  OPT_STR,
		OPT_FFLAG, OPT_FINT, OPT_FDBL, OPT_FSTR} type;
	char *label;
	char *arg;
	char *message;
};
int	OptInit(/* char**,struct s_options*,FILE* */);
int	OptNArgs(/* void */);
char  *OptArg(/* int */);
void   OptErr(/* int */);
void   OptPrint(/* void */);

