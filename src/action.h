// action.h
// LMNO LALR(1) parser generator
// Routines processing parser actions
//
// Copyright ©2010 Brigham Toskin
// (Based on LEMON v1 parser generator, public domain)
//////////////////////////////////////////////////////


struct action *Action_new();
struct action *Action_sort();
void Action_add();


// The state of the yy_action table under construction is an instance of
// the following structure
//struct acttab acttab;
typedef struct acttab
{
	int nAction;				 /* Number of used slots in aAction[] */
	int nActionAlloc;			/* Slots allocated for aAction[] */
	struct
	{
		int lookahead;		   /* Value of the lookahead token */
		int action;			  /* Action to take on the given lookahead */
	} *aAction,				  /* The yy_action[] table under construction */
	*aLookahead;				 /* A single new transaction set */
	int mnLookahead;			 /* Minimum aLookahead[].lookahead */
	int mnAction;				/* Action associated with mnLookahead */
	int mxLookahead;			 /* Maximum aLookahead[].lookahead */
	int nLookahead;			  /* Used slots in aLookahead[] */
	int nLookaheadAlloc;		 /* Slots allocated in aLookahead[] */
} acttab;

/* Return the number of entries in the yy_action table */
#define acttab_size(X) ((X)->nAction)

/* The value for the N-th entry in yy_action */
#define acttab_yyaction(X,N)  ((X)->aAction[N].action)

/* The value for the N-th entry in yy_lookahead */
#define acttab_yylookahead(X,N)  ((X)->aAction[N].lookahead)

void acttab_free(acttab *p);
acttab *acttab_alloc(void);
void acttab_action(acttab *p, int lookahead, int action);
int acttab_insert(acttab *p);
