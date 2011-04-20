// report.c
// LMNO LALR(1) parser generator
// Procedures for generating reports and tables
//
// Copyright ©2010 Brigham Toskin
// (Based on LEMON v1 parser generator, public domain)
//////////////////////////////////////////////////////


#include "global.h"

 
extern int access();

/* Generate a filename with the given suffix.  Space to hold the
 ** name comes from malloc() and must be freed by the calling
 ** function.
 */
PRIVATE char *file_makename(struct lmno *lmnop, char *suffix)
{
	char *name;
	char *cp;
	
	name = malloc(strlen(lmnop->filename) + strlen(suffix) + 5);
	if(name==0)
	{
		fprintf(stderr, "Can't allocate space for a filename.\n");
		exit(1);
	}
	strcpy(name, lmnop->filename);
	cp = strrchr(name, '.');
	if(cp)
		*cp = 0;
	strcat(name, suffix);
	return name;
}

/* Open a file with a name based on the name of the input file,
 ** but with a different (specified) suffix, and return a pointer
 ** to the stream */
PRIVATE FILE *file_open(struct lmno *lmnop, char *suffix, char *mode)
{
	FILE *fp;
	
	if(lmnop->outname)
		free(lmnop->outname);
	lmnop->outname = file_makename(lmnop, suffix);
	fp = fopen(lmnop->outname,mode);
	if(fp==0 && *mode=='w')
	{
		fprintf(stderr,"Can't open file \"%s\".\n",lmnop->outname);
		lmnop->errorcnt++;
		return 0;
	}
	return fp;
}

/* Duplicate the input file without comments and without actions 
 ** on rules */
void Reprint(struct lmno *lmnop)
{
	struct rule *rp;
	struct symbol *sp;
	int i, j, maxlen, len, ncolumns, skip;
	printf("// Reprint of input file \"%s\".\n// Symbols:\n",lmnop->filename);
	maxlen = 10;
	for(i=0; i<lmnop->nsymbol; i++)
	{
		sp = lmnop->symbols[i];
		len = strlen(sp->name);
		if(len>maxlen) maxlen = len;
	}
	ncolumns = 76/(maxlen+5);
	if(ncolumns<1)
		ncolumns = 1;
	skip = (lmnop->nsymbol + ncolumns - 1)/ncolumns;
	for(i=0; i<skip; i++)
	{
		printf("//");
		for(j=i; j<lmnop->nsymbol; j+=skip)
		{
			sp = lmnop->symbols[j];
			assert(sp->index==j);
			printf(" %3d %-*.*s",j,maxlen,maxlen,sp->name);
		}
		printf("\n");
	}
	for(rp=lmnop->rule; rp; rp=rp->next)
	{
		printf("%s",rp->lhs->name);
		/*	if(rp->lhsalias) printf("(%s)",rp->lhsalias); */
		printf(" ->");
		for(i=0; i<rp->nrhs; i++)
		{
			printf(" %s",rp->rhs[i]->name);
			/*	  if(rp->rhsalias[i]) printf("(%s)",rp->rhsalias[i]); */
		}
		printf(".");
		if(rp->precsym)
			printf(" [%s]",rp->precsym->name);
		/*	if(rp->code) printf("\n	%s",rp->code); */
		printf("\n");
	}
}

void ConfigPrint(FILE *fp, struct config *cfp)
{
	struct rule *rp;
	int i;
	rp = cfp->rp;
	fprintf(fp,"%s ->",rp->lhs->name);
	for(i=0; i<=rp->nrhs; i++)
	{
		if(i==cfp->dot)
			fprintf(fp," *");
		if(i==rp->nrhs)
			break;
		fprintf(fp," %s",rp->rhs[i]->name);
	}
}

/* #define TEST */
#ifdef TEST
/* Print a set */
PRIVATE void SetPrint(FILE *out, char *set, struct lmno *lmnop)
{
	int i;
	char *spacer;
	spacer = "";
	fprintf(out,"%12s[","");
	for(i=0; i<lmnop->nterminal; i++)
	{
		if(SetFind(set,i))
		{
			fprintf(out,"%s%s",spacer,lmnop->symbols[i]->name);
			spacer = " ";
		}
	}
	fprintf(out,"]\n");
}

/* Print a plink chain */
PRIVATE void PlinkPrint(FILE *out, struct plink *plp, char *tag)
{
	while(plp)
	{
		fprintf(out,"%12s%s (state %2d) ","",tag,plp->cfp->stp->index);
		ConfigPrint(out,plp->cfp);
		fprintf(out,"\n");
		plp = plp->next;
	}
}
#endif

/* Print an action to the given file descriptor.  Return FALSE if
 ** nothing was actually printed.
 */
int PrintAction(struct action *ap, FILE *fp, int indent)
{
	int result = 1;
	switch(ap->type)
	{
		case SHIFT:
			fprintf(fp,"%*s shift  %d",indent,ap->sp->name,ap->x.stp->index);
			break;
		case REDUCE:
			fprintf(fp,"%*s reduce %d",indent,ap->sp->name,ap->x.rp->index);
			break;
		case ACCEPT:
			fprintf(fp,"%*s accept",indent,ap->sp->name);
			break;
		case ERROR:
			fprintf(fp,"%*s error",indent,ap->sp->name);
			break;
		case CONFLICT:
			fprintf(fp,"%*s reduce %-3d ** Parsing conflict **",
					indent,ap->sp->name,ap->x.rp->index);
			break;
		case SH_RESOLVED:
		case RD_RESOLVED:
		case NOT_USED:
			result = 0;
			break;
	}
	return result;
}

/* Generate the "y.output" log file */
void ReportOutput(struct lmno *lmnop)
{
	int i;
	struct state *stp;
	struct config *cfp;
	struct action *ap;
	FILE *fp;
	
	fp = file_open(lmnop,".out","w");
	if(fp==0)
		return;
	fprintf(fp," \b");
	for(i=0; i<lmnop->nstate; i++)
	{
		stp = lmnop->sorted[i];
		fprintf(fp,"State %d:\n",stp->index);
		if(lmnop->basisflag)
			cfp=stp->bp;
		else
			cfp=stp->cfp;
		while(cfp)
		{
			char buf[20];
			if(cfp->dot==cfp->rp->nrhs)
			{
				sprintf(buf,"(%d)",cfp->rp->index);
				fprintf(fp,"	%5s ",buf);
			}
			else
			{
				fprintf(fp,"		  ");
			}
			ConfigPrint(fp,cfp);
			fprintf(fp,"\n");
#ifdef TEST
			SetPrint(fp,cfp->fws,lmnop);
			PlinkPrint(fp,cfp->fplp,"To  ");
			PlinkPrint(fp,cfp->bplp,"From");
#endif
			if(lmnop->basisflag)
				cfp=cfp->bp;
			else
				cfp=cfp->next;
		}
		fprintf(fp,"\n");
		for(ap=stp->ap; ap; ap=ap->next)
		{
			if(PrintAction(ap,fp,30))
				fprintf(fp,"\n");
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	return;
}

/* Search for the file "name" which is in the same directory as
 ** the exacutable */
PRIVATE char *pathsearch(char *argv0, char *name, int modemask)
{
	char *pathlist;
	char *path,*cp;
	char c;
	
#ifdef __WIN32__
	cp = strrchr(argv0,'\\');
#else
	cp = strrchr(argv0,'/');
#endif
	if(cp)
	{
		c = *cp;
		*cp = 0;
		path = (char *)malloc(strlen(argv0) + strlen(name) + 2);
		if(path)
			sprintf(path,"%s/%s",argv0,name);
		*cp = c;
	}
	else
	{
		extern char *getenv();
		pathlist = getenv("PATH");
		if(pathlist==0)
			pathlist = ".:/bin:/usr/bin";
		path = (char *)malloc(strlen(pathlist)+strlen(name)+2);
		if(path!=0)
		{
			while(*pathlist)
			{
				cp = strchr(pathlist,':');
				if(cp==0)
					cp = &pathlist[strlen(pathlist)];
				c = *cp;
				*cp = 0;
				sprintf(path,"%s/%s",pathlist,name);
				*cp = c;
				if(c==0)
					pathlist = "";
				else
					pathlist = &cp[1];
				if(access(path,modemask)==0)
					break;
			}
		}
	}
	return path;
}

/* Given an action, compute the integer value for that action
 ** which is to be put in the action table of the generated machine.
 ** Return negative if no action should be generated.
 */
PRIVATE int compute_action(struct lmno *lmnop, struct action *ap)
{
	int act;
	switch(ap->type)
	{
		case SHIFT:
			act = ap->x.stp->index;
			break;
		case REDUCE:
			act = ap->x.rp->index + lmnop->nstate;
			break;
		case ERROR:
			act = lmnop->nstate + lmnop->nrule;
			break;
		case ACCEPT:
			act = lmnop->nstate + lmnop->nrule + 1;
			break;
		default:
			act = -1;
			break;
	}
	return act;
}

// Template Routines ///////////////////////////////////////////////////////////

/* The next function finds the template file and opens it, returning
 ** a pointer to the opened file. */
PRIVATE FILE *tplt_open(struct lmno *lmnop)
{
	static char templatename[] = "parser_template.tpp";
	char buf[1000];
	FILE *in;
	char *tpltname;
	char *cp;
	
	// truncate filename to parser_template.t if we want C output
	if(lmnop->export_c)
		templatename[strlen(templatename) - 2] = '\0';
	
	cp = strrchr(lmnop->filename,'.');
	if(cp)
	{
		sprintf(buf,"%.*s.lt",(int)(cp-lmnop->filename),lmnop->filename);
	}
	else
	{
		sprintf(buf,"%s.lt",lmnop->filename);
	}
	
	if(access(buf,004)==0)
	{
		tpltname = buf;
	}
	else if(access(templatename,004)==0){
		tpltname = templatename;
	}
	else
	{
		tpltname = pathsearch(lmnop->argv0,templatename,0);
	}
	
	if(tpltname==0)
	{
		fprintf(stderr,"Can't find the parser driver template file \"%s\".\n",
				templatename);
		lmnop->errorcnt++;
		return 0;
	}
	in = fopen(tpltname,"r");
	if(in==0)
	{
		fprintf(stderr,"Can't open the template file \"%s\".\n",templatename);
		lmnop->errorcnt++;
		return 0;
	}
	return in;
}

/* The next function finds the header template file and opens it, returning
 ** a pointer to the opened file. */
PRIVATE FILE *htplt_open(struct lmno *lmnop)
{
	static char templatename[] = "parser_template.thpp";
	char buf[1000];
	FILE *in;
	char *tpltname;
	char *cp;
	
	// truncate filename to parser_template.th if we want C output
	if(lmnop->export_c)
		templatename[strlen(templatename) - 2] = '\0';
	
	cp = strrchr(lmnop->filename,'.');
	if(cp)
	{
		sprintf(buf,"%.*s.lt",(int)(cp-lmnop->filename),lmnop->filename);
	}
	else
	{
		sprintf(buf,"%s.lt",lmnop->filename);
	}
	
	if(access(buf,004)==0)
	{
		tpltname = buf;
	}
	else if(access(templatename,004)==0){
		tpltname = templatename;
	}
	else
	{
		tpltname = pathsearch(lmnop->argv0,templatename,0);
	}
	
	if(tpltname==0)
	{
		fprintf(stderr,"Can't find the parser header template file \"%s\".\n",
				templatename);
		lmnop->errorcnt++;
		return 0;
	}
	in = fopen(tpltname,"r");
	if(in==0)
	{
		fprintf(stderr,"Can't open the parser header template file \"%s\".\n",
				templatename);
		lmnop->errorcnt++;
		return 0;
	}
	return in;
}

#define LINESIZE 1000

/* This function transfers data from "in" to "out" until
 ** a line is seen which begins with "%%".  The line number is
 ** tracked.
 **
 ** if name!=0, then any word that begin with "%name" is changed to
 ** begin with *name instead.
 */
PRIVATE void tplt_xfer(char *name, FILE *in, FILE *out, int *lineno)
{
	int i, iStart;
	char line[LINESIZE];
	while(fgets(line, LINESIZE, in) && !(line[0] =='%' && line[1] =='%'))
	{
		(*lineno)++;
		iStart = 0;
		if(name)
		{
			for(i = 0; line[i]; i++)
			{
				if(line[i]=='%' && strncmp(&line[i],"%name",5)==0 &&
				   (i == 0 || !isalpha(line[i-1])))
				{
					if(i > iStart)
						fprintf(out,"%.*s", i - iStart, &line[iStart]);
					fprintf(out, "%s", name);
					i += 4;
					iStart = i + 1;
				}
			}
		}
		fprintf(out,"%s",&line[iStart]);
	}
}

// Print a string to the file and keep the linenumber up to date
PRIVATE void tplt_print(FILE *out, struct lmno *lmnop, char *str,
						int strln, int *lineno)
{
	if(str == 0 || out == 0)
		return;
	fprintf(out,"#line %d \"%s\"\n",strln,lmnop->filename); (*lineno)++;
	while(*str)
	{
		if(*str=='\n')
			(*lineno)++;
		putc(*str,out);
		str++;
	}
	fprintf(out,"\n#line %d \"%s\"\n",*lineno+2,lmnop->outname); (*lineno)+=2;
	return;
}

// print user's copyright notice, keeping lineno up to date
PRIVATE void copyright_print(FILE *out, struct lmno *lmnop, int *lineno)
{
	if(out == 0)
		return;

	// check if user supplied copyright info		
	char* str = lmnop->copyright;
	if(str == 0)
	{
		fprintf(out, "// (None given; use the %%copyright{} declaration"
				" to add this information.)\n");
		(*lineno)++;
		return;
	}
	
	// skip leading and trailing blank lines
	while(*str && (*str == '\n' || *str == '\r' || *str == '\t' || *str == ' '))
		str++;
	int tail = strlen(str) - 1;
	int found = 0;
	while((tail >= 0) &&
		  (str[tail] == '\n' || str[tail] == '\r' ||
		  str[tail] == '\t' || str[tail] == ' '))
	 {
	 	found = 1;
		tail--;
	 }
	 if(found)
		str[tail + 1] = 0;
	fprintf(out, "// ");

	// keep track of new lines
	while(*str)
	{
		if(*str=='\n')
		{
			fprintf(out, "\n// ");
			(*lineno)++;
			str++;
		}
		putc(*str,out);
		str++;
	}
	putc('\n', out);
}

/*
 ** The following routine emits code for the destructor for the
 ** symbol sp
 */
void emit_destructor_code(FILE *out, struct symbol *sp,
						  struct lmno *lmnop, int *lineno)
{
	char *cp = 0;
	
	int linecnt = 0;
	if(sp->type==TERMINAL)
	{
		cp = lmnop->tokendest;
		if(cp==0)
			return;
		fprintf(out,"#line %d \"%s\"\n{",lmnop->tokendestln,lmnop->filename);
	}
	else if(sp->destructor)
	{
		cp = sp->destructor;
		fprintf(out,"#line %d \"%s\"\n{",sp->destructorln,lmnop->filename);
	}
	else if(lmnop->vardest)
	{
		cp = lmnop->vardest;
		if(cp==0)
			return;
		fprintf(out,"#line %d \"%s\"\n{",lmnop->vardestln,lmnop->filename);
	}
	else
	{
		assert(0);  /* Cannot happen */
	}
	for(; *cp; cp++)
	{
		if(*cp=='$' && cp[1]=='$')
		{
			fprintf(out,"(yypminor->yy%d)",sp->dtnum);
			cp++;
			continue;
		}
		if(*cp=='\n')
			linecnt++;
		fputc(*cp,out);
	}
	(*lineno) += 3 + linecnt;
	fprintf(out,"}\n#line %d \"%s\"\n",*lineno,lmnop->outname);
	return;
}

/*
 ** Return TRUE (non-zero) if the given symbol has a destructor.
 */
int has_destructor(struct symbol *sp, struct lmno *lmnop)
{
	int ret;
	if(sp->type==TERMINAL)
	{
		ret = lmnop->tokendest!=0;
	}
	else
	{
		ret = lmnop->vardest!=0 || sp->destructor!=0;
	}
	return ret;
}

/*
 ** Append text to a dynamically allocated string.  If zText is 0 then
 ** reset the string to be empty again.  Always return the complete text
 ** of the string (which is overwritten with each call).
 **
 ** n bytes of zText are stored.  If n==0 then all of zText up to the first
 ** \000 terminator is stored.  zText can contain up to two instances of
 ** %d.  The values of p1 and p2 are written into the first and second
 ** %d.
 **
 ** If n==-1, then the previous character is overwritten.
 */
PRIVATE char *append_str(char *zText, int n, int p1, int p2)
{
	static char *z = 0;
	static int alloced = 0;
	static int used = 0;
	int c;
	char zInt[40];
	
	if(zText==0)
	{
		used = 0;
		return z;
	}
	if(n<=0)
	{
		if(n<0)
		{
			used += n;
			assert(used>=0);
		}
		n = strlen(zText);
	}
	if(n+sizeof(zInt)*2+used >= alloced)
	{
		alloced = n + sizeof(zInt)*2 + used + 200;
		z = realloc(z,  alloced);
	}
	if(z==0)
		return "";
	while(n-- > 0)
	{
		c = *(zText++);
		if(c=='%' && zText[0]=='d')
		{
			sprintf(zInt, "%d", p1);
			p1 = p2;
			strcpy(&z[used], zInt);
			used += strlen(&z[used]);
			zText++;
			n--;
		}
		else
		{
			z[used++] = c;
		}
	}
	z[used] = 0;
	return z;
}

/*
 ** zCode is a string that is the action associated with a rule.  Expand
 ** the symbols in this string so that they refer to elements of the parser
 ** stack.
 ** (Return a new string stored in space obtained from malloc?)
 */
PRIVATE void translate_code(struct lmno *lmnop, struct rule *rp)
{
	char *cp, *xp;
	bool lhsused = false;	// True if the LHS element has been used
	char used[MAXRHS];		// True for each RHS element which is used
	
	for(int i = 0; i < rp->nrhs; i++)
		used[i] = 0;
	
	append_str(0,0,0,0);
	for(cp=rp->code; *cp; cp++)
	{
		if(isalpha(*cp) && (cp==rp->code || (!isalnum(cp[-1]) && cp[-1]!='_')))
		{
			char saved;
			for(xp= &cp[1]; isalnum(*xp) || *xp=='_'; xp++) { } // find ident
			saved = *xp;
			*xp = 0;
			if(rp->lhsalias && strcmp(cp,rp->lhsalias)==0)
			{
				append_str("yygotominor.yy%d",0,rp->lhs->dtnum,0);
				cp = xp;
				lhsused = true;
			}
			else
			{
				for(int i = 0; i < rp->nrhs; i++)
				{
					if(rp->rhsalias[i] && strcmp(cp,rp->rhsalias[i])==0)
					{
						// If the argument is "@X" then substituted
						// the token number of X, not the value of X
						if(cp!=rp->code && cp[-1]=='@')
						{
							append_str("yymsp[%d].major",-1,i-rp->nrhs+1,0);
						}
						else
						{
							append_str("yymsp[%d].minor.yy%d",0,
									   i-rp->nrhs+1,rp->rhs[i]->dtnum);
						}
						cp = xp;
						used[i] = 1;
						break;
					}
				}
			}
			*xp = saved;
		}
		append_str(cp, 1, 0, 0);
	} // End loop
	
	// Check to make sure the LHS has been used
	if(rp->lhsalias && !lhsused)
	{
		ErrorMsg(lmnop->filename,rp->ruleline,
				 "Label \"%s\" for \"%s(%s)\" is never used.",
				 rp->lhsalias,rp->lhs->name,rp->lhsalias);
		lmnop->errorcnt++;
	}
	
	// Generate destructor code for RHS symbols which are not used in the
	// reduction code
	for(int i = 0; i < rp->nrhs; i++)
	{
		if(rp->rhsalias[i] && !used[i])
		{
			ErrorMsg(lmnop->filename, rp->ruleline,
					 "Label %s for \"%s(%s)\" is never used.",
					 rp->rhsalias[i], rp->rhs[i]->name, rp->rhsalias[i]);
			lmnop->errorcnt++;
		}
		else if(rp->rhsalias[i]==0)
		{
			if(has_destructor(rp->rhs[i],lmnop))
			{
				append_str("	destructor(%d, &yymsp[%d].minor);\n", 0,
						   rp->rhs[i]->index, i - rp->nrhs + 1);
			}
			else
			{
				/* No destructor defined for this term */
			}
		}
	}
	cp = append_str(0,0,0,0);
	rp->code = Strsafe(cp);
}

/* 
 ** Generate code which executes when the rule "rp" is reduced.  Write
 ** the code to "out".  Make sure lineno stays up-to-date.
 */
PRIVATE void emit_code(FILE *out, struct rule *rp,
					   struct lmno *lmnop, int *lineno)
{
	char *cp;
	int linecnt = 0;
	
	/* Generate code to do the reduce action */
	if(rp->code)
	{
		fprintf(out,"#line %d \"%s\"\n{",rp->line,lmnop->filename);
		fprintf(out,"%s",rp->code);
		for(cp=rp->code; *cp; cp++)
		{
			if(*cp=='\n')
				linecnt++;
		} /* End loop */
		(*lineno) += 3 + linecnt;
		fprintf(out,"}\n#line %d \"%s\"\n",*lineno,lmnop->outname);
	} /* End if(rp->code) */
	
	return;
}

/*
 ** Print the definition of the union used for the parser's data stack.
 ** This union contains fields for every possible data type for tokens
 ** and nonterminals.  In the process of computing and printing this
 ** union, also set the ".dtnum" field of every terminal and nonterminal
 ** symbol.
 */
void print_stack_union(FILE *out, struct lmno *lmnop, int *plineno, int mhflag)
{
	int lineno = *plineno;	/* The line number of the output */
	char **types;			 /* A hash table of datatypes */
	int arraysize;			/* Size of the "types" array */
	int maxdtlength;		  /* Maximum length of any ".datatype" field. */
	char *stddt;			  /* Standardized name for a datatype */
	int i,j;				  /* Loop counters */
	int hash;				 /* For hashing the name of a type */
	char *name;			   /* Name of the parser */
	
	/* Allocate and initialize types[] and allocate stddt[] */
	arraysize = lmnop->nsymbol * 2;
	types = (char**)malloc(arraysize * sizeof(char*));
	for(i=0; i<arraysize; i++) types[i] = 0;
	maxdtlength = 0;
	if(lmnop->vartype)
	{
		maxdtlength = strlen(lmnop->vartype);
	}
	for(i=0; i<lmnop->nsymbol; i++)
	{
		int len;
		struct symbol *sp = lmnop->symbols[i];
		if(sp->datatype==0)
			continue;
		len = strlen(sp->datatype);
		if(len>maxdtlength)
			maxdtlength = len;
	}
	stddt = (char*)malloc(maxdtlength*2 + 1);
	if(types==0 || stddt==0)
	{
		fprintf(stderr,"Out of memory.\n");
		exit(1);
	}
	
	/* Build a hash table of datatypes. The ".dtnum" field of each symbol
	 ** is filled in with the hash index plus 1.  A ".dtnum" value of 0 is
	 ** used for terminal symbols.  If there is no %default_type defined then
	 ** 0 is also used as the .dtnum value for nonterminals which do not specify
	 ** a datatype using the %type directive.
	 */
	for(i=0; i<lmnop->nsymbol; i++)
	{
		struct symbol *sp = lmnop->symbols[i];
		char *cp;
		if(sp==lmnop->errsym)
		{
			sp->dtnum = arraysize+1;
			continue;
		}
		if(sp->type!=NONTERMINAL || (sp->datatype==0 && lmnop->vartype==0))
		{
			sp->dtnum = 0;
			continue;
		}
		cp = sp->datatype;
		if(cp==0)
			cp = lmnop->vartype;
		j = 0;
		while(isspace(*cp))
			cp++;
		while(*cp)
			stddt[j++] = *cp++;
		while(j>0 && isspace(stddt[j-1]))
			j--;
		stddt[j] = 0;
		hash = 0;
		for(j=0; stddt[j]; j++)
		{
			hash = hash*53 + stddt[j];
		}
		hash = (hash & 0x7fffffff)%arraysize;
		while(types[hash])
		{
			if(strcmp(types[hash],stddt)==0)
			{
				sp->dtnum = hash + 1;
				break;
			}
			hash++;
			if(hash>=arraysize)
				hash = 0;
		}
		if(types[hash]==0)
		{
			sp->dtnum = hash + 1;
			types[hash] = (char*)malloc(strlen(stddt)+1);
			if(types[hash]==0)
			{
				fprintf(stderr,"Out of memory.\n");
				exit(1);
			}
			strcpy(types[hash],stddt);
		}
	}
	
	/* Print out the definition of YYTOKENTYPE and YYMINORTYPE */
	name = lmnop->name ? lmnop->name : "Parse";
	lineno = *plineno;
	if(mhflag)
	{
		fprintf(out,"#if INTERFACE\n");
		lineno++;
	}
	fprintf(out,"#define %sTOKENTYPE %s\n",name,
			lmnop->tokentype?lmnop->tokentype:"void*");  lineno++;
	if(mhflag)
	{
		fprintf(out,"#endif\n");
		lineno++;
	}
	fprintf(out,"union YYMINORTYPE\n{\n");
	lineno+=2;
	if(!lmnop->export_c) // give that bitch a useful constructor in C++
	{
		fprintf(out, "	YYMINORTYPE() : __dummy(0) { }\n");
		lineno++;
		fprintf(out, "	int __dummy;\n");
		lineno++;
	}
	fprintf(out,"	%sTOKENTYPE yy0;\n",name);
	lineno++;
	for(i=0; i<arraysize; i++)
	{
		if(types[i]==0)
			continue;
		fprintf(out,"	%s yy%d;\n",types[i],i+1);
		lineno++;
		free(types[i]);
	}
	fprintf(out,"	int yy%d;\n",lmnop->errsym->dtnum);
	lineno++;
	free(stddt);
	free(types);
	fprintf(out,"};\n");
	lineno++;
	if(lmnop->export_c)
	{
		fprintf(out,"typedef union YYMINORTYPE YYMINORTYPE;\n");
		lineno++;
	}
	*plineno = lineno;
}

/*
 ** Return the name of a C datatype able to represent values between
 ** lwr and upr, inclusive.
 */
static const char *minimum_size_type(int lwr, int upr)
{
	if(lwr>=0)
	{
		if(upr<=255)
		{
			return "unsigned char";
		}
		else if(upr<65535)
		{
			return "unsigned short int";
		}
		else
		{
			return "unsigned int";
		}
	}
	else if(lwr>=-127 && upr<=127)
	{
		return "signed char";
	}
	else if(lwr>=-32767 && upr<32767)
	{
		return "short";
	}
	else
	{
		return "int";
	}
}

/*
 ** Each state contains a set of token transaction and a set of
 ** nonterminal transactions.  Each of these sets makes an instance
 ** of the following structure.  An array of these structures is used
 ** to order the creation of entries in the yy_action[] table.
 */
struct axset
{
	struct state *stp;   /* A pointer to a state */
	int isTkn;		   /* True to use tokens.  False for non-terminals */
	int nAction;		 /* Number of actions */
};

/*
 ** Compare to axset structures for sorting purposes
 */
static int axset_compare(const void *a, const void *b)
{
	struct axset *p1 = (struct axset*)a;
	struct axset *p2 = (struct axset*)b;
	return p2->nAction - p1->nAction;
}

/* Generate C source code for the parser */
void ReportTable(struct lmno *lmnop, int mhflag)
{
	FILE *out, *in;
	char line[LINESIZE];
	int  lineno;
	struct state *stp;
	struct action *ap;
	struct rule *rp;
	struct acttab *pActtab;
	int i, j, n;
	int mnTknOfst, mxTknOfst;
	int mnNtOfst, mxNtOfst;
	struct axset *ax;

	// open input template and target output file and advance to first insertion
	in = tplt_open(lmnop);
	if(in == 0)
		return;
	out = (lmnop->export_c ?
			file_open(lmnop,".c","w") :
			file_open(lmnop,".cpp","w") );
	if(out == 0)
	{
		fclose(in);
		return;
	}
	lineno = 1;
	tplt_xfer(lmnop->name,in,out,&lineno);
	
	// insert user's copyright and license information.
	copyright_print(out, lmnop, &lineno);
	tplt_xfer(lmnop->name,in,out,&lineno);
	
	/* Generate the action table and its associates:
	 **
	 **  yy_action[]		A single table containing all actions.
	 **  yy_lookahead[]	 A table containing the lookahead for each entry in
	 **					 yy_action.  Used to detect hash collisions.
	 **  yy_shift_ofst[]	For each state, the offset into yy_action for
	 **					 shifting terminals.
	 **  yy_reduce_ofst[]   For each state, the offset into yy_action for
	 **					 shifting non-terminals after a reduce.
	 **  yy_default[]	   Default action for each state.
	 */
	
	/* Compute the actions on all states and count them up */
	ax = malloc(sizeof(ax[0])*lmnop->nstate*2);
	if(ax==0)
	{
		fprintf(stderr,"malloc failed\n");
		exit(1);
	}
	for(i=0; i<lmnop->nstate; i++)
	{
		stp = lmnop->sorted[i];
		stp->nTknAct = stp->nNtAct = 0;
		stp->iDflt = lmnop->nstate + lmnop->nrule;
		stp->iTknOfst = NO_OFFSET;
		stp->iNtOfst = NO_OFFSET;
		for(ap=stp->ap; ap; ap=ap->next)
		{
			if(compute_action(lmnop,ap)>=0)
			{
				if(ap->sp->index<lmnop->nterminal)
				{
					stp->nTknAct++;
				}
				else if(ap->sp->index<lmnop->nsymbol)
				{
					stp->nNtAct++;
				}
				else
				{
					stp->iDflt = compute_action(lmnop, ap);
				}
			}
		}
		ax[i*2].stp = stp;
		ax[i*2].isTkn = 1;
		ax[i*2].nAction = stp->nTknAct;
		ax[i*2+1].stp = stp;
		ax[i*2+1].isTkn = 0;
		ax[i*2+1].nAction = stp->nNtAct;
	}
	mxTknOfst = mnTknOfst = 0;
	mxNtOfst = mnNtOfst = 0;
	
	/* Compute the action table.  In order to try to keep the size of the
	 ** action table to a minimum, the heuristic of placing the largest action
	 ** sets first is used.
	 */
	qsort(ax, lmnop->nstate*2, sizeof(ax[0]), axset_compare);
	pActtab = acttab_alloc();
	for(i=0; i<lmnop->nstate*2 && ax[i].nAction>0; i++)
	{
		stp = ax[i].stp;
		if(ax[i].isTkn)
		{
			for(ap=stp->ap; ap; ap=ap->next)
			{
				int action;
				if(ap->sp->index>=lmnop->nterminal)
					continue;
				action = compute_action(lmnop, ap);
				if(action<0)
					continue;
				acttab_action(pActtab, ap->sp->index, action);
			}
			stp->iTknOfst = acttab_insert(pActtab);
			if(stp->iTknOfst<mnTknOfst)
				mnTknOfst = stp->iTknOfst;
			if(stp->iTknOfst>mxTknOfst)
				mxTknOfst = stp->iTknOfst;
		}
		else
		{
			for(ap=stp->ap; ap; ap=ap->next)
			{
				int action;
				if(ap->sp->index<lmnop->nterminal)
					continue;
				if(ap->sp->index==lmnop->nsymbol)
					continue;
				action = compute_action(lmnop, ap);
				if(action<0)
					continue;
				acttab_action(pActtab, ap->sp->index, action);
			}
			stp->iNtOfst = acttab_insert(pActtab);
			if(stp->iNtOfst<mnNtOfst)
				mnNtOfst = stp->iNtOfst;
			if(stp->iNtOfst>mxNtOfst)
				mxNtOfst = stp->iNtOfst;
		}
	}
	free(ax);
	
	/* Output the yy_action table */
	fprintf(out,"static YYACTIONTYPE yy_action[] = {\n");
	lineno++;
	n = acttab_size(pActtab);
	for(i=j=0; i<n; i++)
	{
		int action = acttab_yyaction(pActtab, i);
		if(action<0)
			action = lmnop->nsymbol + lmnop->nrule + 2;
		if(j==0)
			fprintf(out," /* %5d */ ", i);
		fprintf(out, " %4d,", action);
		if(j==9 || i==n-1)
		{
			fprintf(out, "\n");
			lineno++;
			j = 0;
		}
		else
		{
			j++;
		}
	}
	fprintf(out, "};\n"); lineno++;
	
	/* Output the yy_lookahead table */
	fprintf(out,"static YYCODETYPE yy_lookahead[] = {\n");
	lineno++;
	for(i=j=0; i<n; i++)
	{
		int la = acttab_yylookahead(pActtab, i);
		if(la<0)
			la = lmnop->nsymbol;
		if(j==0)
			fprintf(out," /* %5d */ ", i);
		fprintf(out, " %4d,", la);
		if(j==9 || i==n-1)
		{
			fprintf(out, "\n");
			lineno++;
			j = 0;
		}
		else
		{
			j++;
		}
	}
	fprintf(out, "};\n");
	lineno++;
	
	/* Output the yy_shift_ofst[] table */
	fprintf(out, "#define YY_SHIFT_USE_DFLT (%d)\n", mnTknOfst-1);
	lineno++;
	fprintf(out, "static %s yy_shift_ofst[] = {\n", 
			minimum_size_type(mnTknOfst-1, mxTknOfst));
	lineno++;
	n = lmnop->nstate;
	for(i=j=0; i<n; i++)
	{
		int ofst;
		stp = lmnop->sorted[i];
		ofst = stp->iTknOfst;
		if(ofst==NO_OFFSET)
			ofst = mnTknOfst - 1;
		if(j==0)
			fprintf(out," /* %5d */ ", i);
		fprintf(out, " %4d,", ofst);
		if(j==9 || i==n-1)
		{
			fprintf(out, "\n");
			lineno++;
			j = 0;
		}
		else
		{
			j++;
		}
	}
	fprintf(out, "};\n"); lineno++;
	
	/* Output the yy_reduce_ofst[] table */
	fprintf(out, "#define YY_REDUCE_USE_DFLT (%d)\n", mnNtOfst-1);
	lineno++;
	fprintf(out, "static %s yy_reduce_ofst[] = {\n", 
			minimum_size_type(mnNtOfst-1, mxNtOfst));
	lineno++;
	n = lmnop->nstate;
	for(i=j=0; i<n; i++)
	{
		int ofst;
		stp = lmnop->sorted[i];
		ofst = stp->iNtOfst;
		if(ofst==NO_OFFSET)
			ofst = mnNtOfst - 1;
		if(j==0)
			fprintf(out," /* %5d */ ", i);
		fprintf(out, " %4d,", ofst);
		if(j==9 || i==n-1)
		{
			fprintf(out, "\n");
			lineno++;
			j = 0;
		}
		else
		{
			j++;
		}
	}
	fprintf(out, "};\n"); lineno++;
	
	/* Output the default action table */
	fprintf(out, "static YYACTIONTYPE yy_default[] = {\n");
	lineno++;
	n = lmnop->nstate;
	for(i=j=0; i<n; i++)
	{
		stp = lmnop->sorted[i];
		if(j==0)
			fprintf(out," /* %5d */ ", i);
		fprintf(out, " %4d,", stp->iDflt);
		if(j==9 || i==n-1)
		{
			fprintf(out, "\n");
			lineno++;
			j = 0;
		}
		else
		{
			j++;
		}
	}
	fprintf(out, "};\n");
	lineno++;
	tplt_xfer(lmnop->name,in,out,&lineno);
	
	/* Generate the table of fallback tokens.
	 */
	if(lmnop->has_fallback)
	{
		for(i=0; i<lmnop->nterminal; i++)
		{
			struct symbol *p = lmnop->symbols[i];
			if(p->fallback==0)
			{
				fprintf(out, "	0,  /* %10s => nothing */\n", p->name);
			}
			else
			{
				fprintf(out, "  %3d,  /* %10s => %s */\n", p->fallback->index,
						p->name, p->fallback->name);
			}
			lineno++;
		}
	}
	tplt_xfer(lmnop->name, in, out, &lineno);
	
	/* Generate a table containing the symbolic name of every symbol
	 */
	for(i=0; i<lmnop->nsymbol; i++)
	{
		sprintf(line,"\"%s\",",lmnop->symbols[i]->name);
		fprintf(out,"  %-15s",line);
		if((i&3)==3)
		{
			fprintf(out,"\n");
			lineno++;
		}
	}
	if((i&3)!=0)
	{
		fprintf(out,"\n");
		lineno++;
	}
	tplt_xfer(lmnop->name,in,out,&lineno);
	
	/* Generate a table containing a text string that describes every
	 ** rule in the rule set of the grammer.  This information is used
	 ** when tracing REDUCE actions.
	 */
	for(i=0, rp=lmnop->rule; rp; rp=rp->next, i++)
	{
		assert(rp->index==i);
		fprintf(out," /* %3d */ \"%s ->", i, rp->lhs->name);
		for(j=0; j<rp->nrhs; j++)
			fprintf(out," %s",rp->rhs[j]->name);
		fprintf(out,"\",\n");
		lineno++;
	}
	tplt_xfer(lmnop->name,in,out,&lineno);
	
	/* Generate code which executes every time a symbol is popped from
	 ** the stack while processing errors or while destroying the parser. 
	 ** (In other words, generate the %destructor actions)
	 */
	if(lmnop->tokendest)
	{
		for(i=0; i<lmnop->nsymbol; i++)
		{
			struct symbol *sp = lmnop->symbols[i];
			if(sp==0 || sp->type!=TERMINAL) continue;
			fprintf(out,"	case %d:\n",sp->index);
			lineno++;
		}
		for(i=0; i<lmnop->nsymbol && lmnop->symbols[i]->type!=TERMINAL; i++) { }
		if(i<lmnop->nsymbol)
		{
			emit_destructor_code(out,lmnop->symbols[i],lmnop,&lineno);
			fprintf(out,"	  break;\n");
			lineno++;
		}
	}
	for(i=0; i<lmnop->nsymbol; i++)
	{
		struct symbol *sp = lmnop->symbols[i];
		if(sp==0 || sp->type==TERMINAL || sp->destructor==0)
			continue;
		fprintf(out,"	case %d:\n",sp->index);
		lineno++;
		
		/* Combine duplicate destructors into a single case */
		for(j=i+1; j<lmnop->nsymbol; j++)
		{
			struct symbol *sp2 = lmnop->symbols[j];
			if(sp2 && sp2->type!=TERMINAL && sp2->destructor &&
				sp2->dtnum==sp->dtnum &&
				strcmp(sp->destructor,sp2->destructor)==0)
			{
				fprintf(out,"	case %d:\n",sp2->index);
				lineno++;
				sp2->destructor = 0;
			}
		}
		
		emit_destructor_code(out,lmnop->symbols[i],lmnop,&lineno);
		fprintf(out,"	  break;\n");
		lineno++;
	}
	if(lmnop->vardest)
	{
		struct symbol *dflt_sp = 0;
		for(i=0; i<lmnop->nsymbol; i++)
		{
			struct symbol *sp = lmnop->symbols[i];
			if(sp==0 || sp->type==TERMINAL ||
				sp->index<=0 || sp->destructor!=0)
				continue;
			fprintf(out,"	case %d:\n",sp->index);
			lineno++;
			dflt_sp = sp;
		}
		if(dflt_sp!=0)
		{
			emit_destructor_code(out,dflt_sp,lmnop,&lineno);
			fprintf(out,"	  break;\n");
			lineno++;
		}
	}
	tplt_xfer(lmnop->name,in,out,&lineno);
	
	/* Generate code which executes whenever the parser stack overflows */
	if(lmnop->export_c)
	{
		tplt_print(out,lmnop,lmnop->overflow,lmnop->overflowln,&lineno);
		tplt_xfer(lmnop->name,in,out,&lineno);
	}
	
	/* Generate the table of rule information 
	 **
	 ** Note: This code depends on the fact that rules are number
	 ** sequentually beginning with 0.
	 */
	for(rp=lmnop->rule; rp; rp=rp->next)
	{
		fprintf(out,"  { %d, %d },\n",rp->lhs->index,rp->nrhs);
		lineno++;
	}
	tplt_xfer(lmnop->name,in,out,&lineno);
	
	/* Generate code which execution during each REDUCE action */
	for(rp=lmnop->rule; rp; rp=rp->next)
	{
		if(rp->code)
			translate_code(lmnop, rp);
	}
	for(rp=lmnop->rule; rp; rp=rp->next)
	{
		struct rule *rp2;
		if(rp->code==0)
			continue;
		fprintf(out,"	  case %d:\n",rp->index);
		lineno++;
		for(rp2=rp->next; rp2; rp2=rp2->next)
		{
			if(rp2->code==rp->code)
			{
				fprintf(out,"	  case %d:\n",rp2->index);
				lineno++;
				rp2->code = 0;
			}
		}
		emit_code(out,rp,lmnop,&lineno);
		fprintf(out,"		break;\n");
		lineno++;
	}
	tplt_xfer(lmnop->name,in,out,&lineno);
	
	/* Generate code which executes if a parse fails */
	tplt_print(out,lmnop,lmnop->failure,lmnop->failureln,&lineno);
	tplt_xfer(lmnop->name,in,out,&lineno);
	
	/* Generate code which executes when a syntax error occurs */
	tplt_print(out,lmnop,lmnop->error,lmnop->errorln,&lineno);
	tplt_xfer(lmnop->name,in,out,&lineno);
	
	/* Generate code which executes when the parser accepts its input */
	tplt_print(out,lmnop,lmnop->accept,lmnop->acceptln,&lineno);
	tplt_xfer(lmnop->name,in,out,&lineno);
	
	/* Append any addition code the user desires */
	tplt_print(out,lmnop,lmnop->extracode,lmnop->extracodeln,&lineno);
	
	fclose(in);
	fclose(out);
	return;
}

/* Generate a header file for the parser */
void ReportHeader(struct lmno *lmnop)
{
	// open input template and target output file and advance to first insertion
	FILE* in = htplt_open(lmnop);
	if(in == 0)
		return;
	FILE* out = file_open(lmnop, ".h", "w");
	if(out == 0)
	{
		fclose(in);
		return;
	}
	int lineno = 1;
	tplt_xfer(lmnop->name,in,out,&lineno);
	
	// insert user's copyright and license information.
	copyright_print(out, lmnop, &lineno);
	tplt_xfer(lmnop->name,in,out,&lineno);
	
	// Generate the include code, if any
	tplt_print(out, lmnop, lmnop->include, lmnop->includeln, &lineno);
	tplt_xfer(lmnop->name,in,out,&lineno);
	
	// output token definitions
	char *prefix = (lmnop->tokenprefix ? lmnop->tokenprefix : "");
	for(int i = 1; i < lmnop->nterminal; i++)
	{
		fprintf(out,"#define %s%-30s %2d\n", prefix, lmnop->symbols[i]->name, i);
	}
	tplt_xfer(lmnop->name,in,out,&lineno);
	
	// output type and data defines
	fprintf(out,"#define YYCODETYPE %s\n",
			minimum_size_type(0, lmnop->nsymbol+5)); lineno++;
	fprintf(out,"#define YYNOCODE %d\n",lmnop->nsymbol+1);  lineno++;
	fprintf(out,"#define YYACTIONTYPE %s\n",
			minimum_size_type(0, lmnop->nstate+lmnop->nrule+5));  lineno++;
	print_stack_union(out, lmnop, &lineno, 0);
	if(lmnop->stacksize)
	{
		if(atoi(lmnop->stacksize) <= 0)
		{
			ErrorMsg(lmnop->filename, 0, "Illegal stack size: [%s].  "
				"The stack size should be a positive integer constant.",
				lmnop->stacksize);
			lmnop->errorcnt++;
			lmnop->stacksize = "100";
		}
		fprintf(out,"#define YYSTACKDEPTH %s\n",lmnop->stacksize);  lineno++;
	}
	else
	{
		fprintf(out,"#define YYSTACKDEPTH 100\n");  lineno++;
	}
	char* name = lmnop->name ? lmnop->name : "Parse";
	if(lmnop->arg && lmnop->arg[0])
	{
		int i;
		i = strlen(lmnop->arg);
		while(i>=1 && isspace(lmnop->arg[i-1]))
			i--;
		while(i>=1 && (isalnum(lmnop->arg[i-1]) || lmnop->arg[i-1]=='_'))
			i--;
		fprintf(out,"#define %sARG_SDECL %s;\n",name,lmnop->arg);
		lineno++;
		fprintf(out,"#define %sARG_PDECL ,%s\n",name,lmnop->arg);
		lineno++;
		fprintf(out,"#define %sARG_FETCH %s = yypParser->%s\n",
				name,lmnop->arg,&lmnop->arg[i]);
		lineno++;
		fprintf(out,"#define %sARG_STORE yypParser->%s = %s\n",
				name,&lmnop->arg[i],&lmnop->arg[i]);
		lineno++;
	}
	else
	{
		fprintf(out,"#define %sARG_SDECL\n",name);
		lineno++;
		fprintf(out,"#define %sARG_PDECL\n",name);
		lineno++;
		fprintf(out,"#define %sARG_FETCH\n",name);
		lineno++;
		fprintf(out,"#define %sARG_STORE\n",name);
		lineno++;
	}
	fprintf(out,"#define YYNSTATE %d\n",lmnop->nstate);
	lineno++;
	fprintf(out,"#define YYNRULE %d\n",lmnop->nrule);
	lineno++;
	fprintf(out,"#define YYERRORSYMBOL %d\n",lmnop->errsym->index);
	lineno++;
	fprintf(out,"#define YYERRSYMDT yy%d\n",lmnop->errsym->dtnum);
	lineno++;
	if(lmnop->has_fallback)
	{
		fprintf(out,"#define YYFALLBACK 1\n");  lineno++;
	}
	
	// output the rest of the file
	tplt_xfer(lmnop->name,in,out,&lineno);
	fclose(in);
	fclose(out);
}

/* Reduce the size of the action tables, if possible, by making use
 ** of defaults.
 **
 ** In this version, we take the most frequent REDUCE action and make
 ** it the default.  Only default a reduce if there are more than one.
 */
void CompressTables(struct lmno *lmnop)
{
	struct state *stp;
	struct action *ap, *ap2;
	struct rule *rp, *rp2, *rbest;
	int nbest, n;
	int i;
	
	for(i=0; i<lmnop->nstate; i++)
	{
		stp = lmnop->sorted[i];
		nbest = 0;
		rbest = 0;
		
		for(ap=stp->ap; ap; ap=ap->next)
		{
			if(ap->type!=REDUCE)
				continue;
			rp = ap->x.rp;
			if(rp==rbest)
				continue;
			n = 1;
			for(ap2=ap->next; ap2; ap2=ap2->next)
			{
				if(ap2->type!=REDUCE)
					continue;
				rp2 = ap2->x.rp;
				if(rp2==rbest)
					continue;
				if(rp2==rp)
					n++;
			}
			if(n>nbest)
			{
				nbest = n;
				rbest = rp;
			}
		}
		
		/* Do not make a default if the number of rules to default
		 ** is not at least 2 */
		if(nbest<2)
			continue;
		
		
		/* Combine matching REDUCE actions into a single default */
		for(ap=stp->ap; ap; ap=ap->next)
		{
			if(ap->type==REDUCE && ap->x.rp==rbest)
				break;
		}
		assert(ap);
		ap->sp = Symbol_new("{default}");
		for(ap=ap->next; ap; ap=ap->next)
		{
			if(ap->type==REDUCE && ap->x.rp==rbest)
				ap->type = NOT_USED;
		}
		stp->ap = Action_sort(stp->ap);
	}
}

