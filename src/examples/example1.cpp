/* Driver template for the LMNO parser generator.
 * The author disclaims copyright to this source code.
 */


/* First off, code is included which follows the "%include" declaration
 * in the input file. */
#include <iostream>
 using std::ostream;
#include <string>
 using std::string;
#include <deque>
 using std::deque;

#line 15 "src/examples/example1.lmn"
   
#include <iostream>  
#include "example1.h"

#line 21 "src/examples/example1.cpp"


/* Next is all token values, in a form suitable for use by makeheaders.
 * This section will be null unless lmno is run with the -m switch.
 */
/* 
 * These constants (all generated automatically by the parser generator)
 * specify the various kinds of tokens (terminals) that the parser
 * understands. 
 *
 * Each symbol here is a terminal symbol in the grammar.
 */

// Make sure the INTERFACE macro is defined.
#ifndef INTERFACE
# define INTERFACE 1
#endif

/* The next thing included is series of defines which control
 * various aspects of the generated parser.
 *    YYCODETYPE         is the data type used for storing terminal
 *                       and nonterminal numbers.  "unsigned char" is
 *                       used if there are fewer than 250 terminals
 *                       and nonterminals.  "int" is used otherwise.
 *    YYNOCODE           is a number of type YYCODETYPE which corresponds
 *                       to no legal terminal or nonterminal number.  This
 *                       number is used to fill in empty slots of the hash 
 *                       table.
 *    YYFALLBACK         If defined, this indicates that one or more tokens
 *                       have fall-back values which should be used if the
 *                       original value of the token will not parse.
 *    YYACTIONTYPE       is the data type used for storing terminal
 *                       and nonterminal numbers.  "unsigned char" is
 *                       used if there are fewer than 250 rules and
 *                       states combined.  "int" is used otherwise.
 *    ParseTOKENTYPE     is the data type used for minor tokens given 
 *                       directly to the parser from the tokenizer.
 *    YYMINORTYPE        is the data type used for all minor tokens.
 *                       This is typically a union of many types, one of
 *                       which is ParseTOKENTYPE.  The entry in the union
 *                       for base tokens is called "yy0".
 *    YYSTACKDEPTH       is the maximum depth of the parser's stack.
 *    ParseARG_SDECL     A static variable declaration for the %extra_argument
 *    ParseARG_PDECL     A parameter declaration for the %extra_argument
 *    ParseARG_STORE     Code to store %extra_argument into yypParser
 *    ParseARG_FETCH     Code to extract %extra_argument from yypParser
 *    YYNSTATE           the combined number of states.
 *    YYNRULE            the number of rules in the grammar
 *    YYERRORSYMBOL      is the code number of the error symbol.  If not
 *                       defined, then do no error processing.
 */
#define YYCODETYPE unsigned char
#define YYNOCODE 10
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE int
union YYMINORTYPE
{
	YYMINORTYPE() : __dummy(0) { }
	int __dummy;
	ParseTOKENTYPE yy0;
	int yy19;
};
#define YYSTACKDEPTH 100
#define ParseARG_SDECL
#define ParseARG_PDECL
#define ParseARG_FETCH
#define ParseARG_STORE
#define YYNSTATE 11
#define YYNRULE 6
#define YYERRORSYMBOL 6
#define YYERRSYMDT yy19
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* Next are that tables used to determine what action to take based on the
 * current state and lookahead token.  These tables are used to implement
 * functions that take a state number and lookahead value and return an
 * action integer.  
 *
 * Suppose the action integer is N.  Then the action is determined as
 * follows
 *
 *   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
 *                                      token onto the stack and goto state N.
 *
 *   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
 *
 *   N == YYNSTATE+YYNRULE              A syntax error has occurred.
 *
 *   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
 *
 *   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
 *                                      slots in the yy_action[] table.
 *
 * The action table is constructed as a single large table named yy_action[].
 * Given state S and lookahead X, the action is computed as
 *
 *      yy_action[ yy_shift_ofst[S] + X ]
 *
 * If the index value yy_shift_ofst[S]+X is out of range or if the value
 * yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
 * is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
 * and that yy_default[S] should be used instead.  
 *
 * The formula above is for computing the action when the lookahead is
 * a terminal symbol.  If the lookahead is a non-terminal (as occurs after
 * a reduce action) then the yy_reduce_ofst[] array is used in place of
 * the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
 * YY_SHIFT_USE_DFLT.
 *
 * The following are the tables generated in this section:
 *
 *  yy_action[]        A single table containing all actions.
 *  yy_lookahead[]     A table containing the lookahead for each entry in
 *                     yy_action.  Used to detect hash collisions.
 *  yy_shift_ofst[]    For each state, the offset into yy_action for
 *                     shifting terminals.
 *  yy_reduce_ofst[]   For each state, the offset into yy_action for
 *                     shifting non-terminals after a reduce.
 *  yy_default[]       Default action for each state.
 */
static YYACTIONTYPE yy_action[] = {
 /*     0 */    11,    4,    2,    8,    6,    8,    6,    9,   18,    1,
 /*    10 */    10,    5,    7,   17,    3,
};
static YYCODETYPE yy_lookahead[] = {
 /*     0 */     0,    1,    2,    3,    4,    3,    4,    8,    7,    8,
 /*    10 */     5,    8,    8,    9,    8,
};
#define YY_SHIFT_USE_DFLT (-1)
static signed char yy_shift_ofst[] = {
 /*     0 */     5,    0,    5,    2,    5,    2,    5,   -1,    5,   -1,
 /*    10 */    -1,
};
#define YY_REDUCE_USE_DFLT (-2)
static signed char yy_reduce_ofst[] = {
 /*     0 */     1,   -2,    6,   -2,    3,   -2,    4,   -2,   -1,   -2,
 /*    10 */    -2,
};
static YYACTIONTYPE yy_default[] = {
 /*     0 */    17,   17,   17,   12,   17,   13,   17,   14,   17,   15,
 /*    10 */    16,
};
#define YY_SZ_ACTTAB (sizeof(yy_action)/sizeof(yy_action[0]))

/* The next table maps tokens into fallback tokens.  If a construct
 * like the following:
 * 
 *      %fallback ID X Y Z.
 *
 * appears in the grammer, then ID becomes a fallback token for X, Y,
 * and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
 * but it does not parse, the type of the token is changed to ID and
 * the parse is retried before an error is thrown.
 */
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

// Stack Entry /////////////////////////////////////////////////////////////////

/*
 * Information stored includes:
 *
 *  +  The state number for the parser at this level of the stack.
 *
 *   +  The value of the token stored at this level of the stack.
 *      (In other words, the "major" token.)
 *
 *   +  The semantic value stored at this level of the stack.  This is
 *      the information used by the action routines in the grammar.
 *      It is sometimes called the "minor" token.
 */
struct yyStackEntry
{
	yyStackEntry() : stateno(0), major(0) { }
	yyStackEntry(int state, int major, YYMINORTYPE minor)
	: stateno(state), major(major), minor(minor)
	{
	}

	int stateno;       /* The state-number */
	int major;         /* The major token value.  This is the code
						** number for the token at this stack level */
	YYMINORTYPE minor; /* The user-supplied minor token value.  This
						** is the value of the token  */
};

// Shift-Reduce Stack //////////////////////////////////////////////////////////

class yyStack
{
public:
	virtual void push(const yyStackEntry& item);
	virtual yyStackEntry pop();
	virtual void lop();
	virtual void lop(size_t count);
	virtual yyStackEntry& top();
	virtual void pick(size_t n);
	virtual yyStackEntry& peek(size_t n);
	virtual void dup();
	virtual void over();
	virtual void toss(size_t n);
	virtual const yyStackEntry& yank(size_t n);
	virtual void roll(size_t n);
	virtual void swap();
	virtual void rot();
	
	virtual void clear();
	virtual size_t size();
	virtual bool empty();
	
	virtual yyStackEntry& operator[](size_t);
private:
	yyStackEntry popped_val;
	deque<yyStackEntry> c;
};

void yyStack::push(const yyStackEntry& item)
{
	c.push_back(item);
}

// pop head off (and return)
yyStackEntry yyStack::pop()
{
	popped_val = c.back();
	c.pop_back();
	return popped_val;
}

// lop head off (and discard)
void yyStack::lop()
{
	c.pop_back();
}

// lop head off (and discard)
void yyStack::lop(size_t count)
{
	while (count--)
	{
		c.pop_back();
	}
}

// return a reference to TOS
yyStackEntry& yyStack::top()
{
	return c.back();
}

// push a copy of the nth item from the top
void yyStack::pick(size_t n)
{
	c.push_back(this->c[c.size() - 1 - n]);
}

// push a duplicate of TOS
void yyStack::dup()
{
	c.push_back(c.back());
}

// push a dup of item under TOS
void yyStack::over()
{
	pick(1);
}

// return a reference to the nth item from TOS
yyStackEntry& yyStack::peek(size_t n)
{
	return this->c[c.size() - 1 - n];
}

// grab (and discard) nth item from TOS
void yyStack::toss(size_t n)
{
	yank(n);
}

// grab (and return) nth item from TOS
const yyStackEntry& yyStack::yank(size_t n)
{
	int top = c.size() - 1;
	n = top - n;
	popped_val = this->c[n];
	c.erase(c.begin()+n);
	return popped_val;
}

// grab (and push) nth item form TOS
void yyStack::roll(size_t n)
{
	c.push_back(yank(n));
}

// swap top two items
void yyStack::swap()
{
	//equivalent to roll(1);
	int n = c.size() - 1, m = n-1;
	yyStackEntry tmp = this->c[n];
	this->c[n] = this->c[m];
	this->c[m] = tmp;
}

// grab (and push) 2nd item from TOS
void yyStack::rot()
{
	roll(2);
}

// access arbitrary item in stack
yyStackEntry& yyStack::operator[](size_t i)
{
	return this->c[i];
}

// empty the stack
void yyStack::clear()
{
	c.clear();
}

// return stack height
size_t yyStack::size()
{
	return c.size();
}

// is stack empty?
bool yyStack::empty()
{
	return c.empty();
}

// Main Parser Class ///////////////////////////////////////////////////////////

/* The state of the parser is completely contained in an instance of
 * the following structure */
class yyParser
{
public:
	yyParser() : errCount(0) { stack.push(yyStackEntry()); }
	
	void Parse(int yymajor, ParseTOKENTYPE yyminor ParseARG_PDECL);
	
	void ParseTrace(ostream *traceStream, const string& tracePrompt);
	void ParseTrace();
	const string ParseTokenName(int tokenType);
	
protected:
	void destructor(YYCODETYPE yymajor, YYMINORTYPE *yypminor);

	int find_shift_action(int iLookAhead);
	int find_reduce_action(int iLookAhead);
	void shift(int yyNewState, int yyMajor, YYMINORTYPE *yypMinor);
	void reduce(int yyruleno);
	void accept();
	
	void parse_failed();
	void syntax_error(int yymajor, YYMINORTYPE yyminor);

	int errCount;						// Shifts left before out of the error
	ParseARG_SDECL						// A place to hold %extra_argument
	yyStack stack;		// The parser's shift/reduce stack
	
	#ifndef NDEBUG
	static std::ostream* yyTraceStream;
	static string yyTracePrompt;
	static const string yyTokenName[];
	static const string yyRuleName[];
	#endif // NDEBUG
};

// Debug Tracing Data //
#ifndef NDEBUG
std::ostream* yyParser::yyTraceStream = NULL;
string yyParser::yyTracePrompt = "";

// the names of all terminals and nonterminals, for tracing shifts
const string yyParser::yyTokenName[] = { 
  "$",             "PLUS",          "MINUS",         "DIVIDE",      
  "TIMES",         "INTEGER",       "error",         "program",     
  "expr",        
};
// the names of all rules, for tracing reduce actions
const string yyParser::yyRuleName[] = {
 /*   0 */ "program -> expr",
 /*   1 */ "expr -> expr MINUS expr",
 /*   2 */ "expr -> expr PLUS expr",
 /*   3 */ "expr -> expr TIMES expr",
 /*   4 */ "expr -> expr DIVIDE expr",
 /*   5 */ "expr -> INTEGER",
};
#endif /* NDEBUG */

/* 
 * Turn parser tracing on by giving a stream to which to write the trace
 * and a prompt to preface each trace message.  Tracing is turned off
 * by making either argument NULL 
 *
 * Inputs:
 * <ul>
 * <li> A FILE* to which trace output should be written.
 *      If NULL, then tracing is turned off.
 * <li> A prefix string written at the beginning of every
 *      line of trace output.  If NULL, then tracing is
 *      turned off.
 * </ul>
 *
 * Outputs:
 * None.
 */
void yyParser::ParseTrace(ostream *traceStream, const string& tracePrompt)
{
#ifndef NDEBUG
	yyTraceStream = traceStream;
	yyTracePrompt = tracePrompt;
	if(yyTraceStream == NULL)
		yyTracePrompt.clear();
	else if(yyTracePrompt == "")
		yyTraceStream = NULL;
#endif
}

// shortcut overload to disable tracing
void yyParser::ParseTrace()
{
#ifndef NDEBUG
	yyTraceStream = NULL;
	yyTracePrompt = "";
#endif
}

// This function returns the symbolic name associated with a token value.
const string yyParser::ParseTokenName(int tokenType)
{
#ifndef NDEBUG
	if(tokenType>0 && tokenType<(sizeof(yyTokenName)/sizeof(yyTokenName[0])))
	{
		return yyTokenName[tokenType];
	}
	else
	{
		return "Unknown";
	}
#else
	return "";
#endif
}

/*
 * The following function deletes the value associated with a
 * symbol.  The symbol can be either a terminal or nonterminal.
 * "yymajor" is the symbol code, and "yypminor" is a pointer to
 * the value.
 */
void yyParser::destructor(YYCODETYPE yymajor, YYMINORTYPE *yypminor)
{
	switch(yymajor)
	{
			/* Here is inserted the actions which take place when a
			 * terminal or non-terminal is destroyed.  This can happen
			 * when the symbol is popped from the stack during a
			 * reduce or during error processing or when a parser is 
			 * being destroyed before it is finished parsing.
			 *
			 * Note: during a reduce, the only symbols destroyed are those
			 * which appear on the RHS of the rule, but which are not used
			 * inside the C code.
			 */
		default:
			break;   /* If no destructor action specified: do nothing */
	}
}

/*
 * Find the appropriate action for a parser given the terminal
 * look-ahead token iLookAhead.
 *
 * If the look-ahead token is YYNOCODE, then check to see if the action is
 * independent of the look-ahead.  If it is, return the action, otherwise
 * return YY_NO_ACTION.
 */
int yyParser::find_shift_action(int iLookAhead)
{
	int i;
	//int stateno = pParser->stack[pParser->index].stateno;
	int stateno = stack.top().stateno;

	i = yy_shift_ofst[stateno];
	if(i==YY_SHIFT_USE_DFLT)
	{
		return yy_default[stateno];
	}
	if(iLookAhead==YYNOCODE)
	{
		return YY_NO_ACTION;
	}
	i += iLookAhead;
	if(i<0 || i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead)
	{
#ifdef YYFALLBACK
		int iFallback;            /* Fallback token */
		if(iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
		   && (iFallback = yyFallback[iLookAhead])!=0)
		{
#ifndef NDEBUG
			if(yyTraceStream)
			{
				*yyTraceStream << yyTracePrompt << "FALLBACK "
				<< yyTokenName[iLookAhead] << "=> "
				<< yyTokenName[iFallback] << std::endl;
			}
#endif
			return find_shift_action(iFallback);
		}
#endif
		return yy_default[stateno];
	}
	else
	{
		return yy_action[i];
	}
}

/*
 * Find the appropriate action for a parser given the non-terminal
 * look-ahead token iLookAhead.
 *
 * If the look-ahead token is YYNOCODE, then check to see if the action is
 * independent of the look-ahead.  If it is, return the action, otherwise
 * return YY_NO_ACTION.
 */
int yyParser::find_reduce_action(int iLookAhead)
{
	int i;
	int stateno = stack.top().stateno;
	
	i = yy_reduce_ofst[stateno];
	if(i==YY_REDUCE_USE_DFLT)
	{
		return yy_default[stateno];
	}
	if(iLookAhead==YYNOCODE)
	{
		return YY_NO_ACTION;
	}
	i += iLookAhead;
	if(i<0 || i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead)
	{
		return yy_default[stateno];
	}
	else
	{
		return yy_action[i];
	}
}

/*
 * Perform a shift action.
 */
void yyParser::shift(int yyNewState, int yyMajor, YYMINORTYPE *yypMinor)
{	
// TODO: remove this insertion point from lmno.c
// stack will never overflow
#if 0
#endif
	stack.push(yyStackEntry(yyNewState, yyMajor, *yypMinor));
	/*yyStackEntry& yytos = stack.top();
	yytos->stateno = yyNewState;
	yytos->major = yyMajor;
	yytos->minor = *yypMinor;*/
#ifndef NDEBUG
	if(yyTraceStream && stack.size())
	{
		int i;
		*yyTraceStream << yyTracePrompt << "Shift " << yyNewState << '\n'
		<< yyTracePrompt << "Stack: ";
		for(i=0; i < stack.size(); i++)
			*yyTraceStream << yyTokenName[stack[i].major];
		*yyTraceStream << std::endl;
	}
#endif
}

/* The following table contains information about every rule that
 * is used during the reduce.
 */
static struct {
	YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
	unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 7, 1 },
  { 8, 3 },
  { 8, 3 },
  { 8, 3 },
  { 8, 3 },
  { 8, 1 },
};

/*
 * Perform a reduce action and the shift that must immediately
 * follow the reduce.
 */
void yyParser::reduce(int yyruleno)
{
	int yygoto;                     /* The next state */
	int yyact;                      /* The next action */
	YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
	yyStackEntry *yymsp;            /* The top of the parser's stack */
	int yysize;                     /* Amount to pop the stack */
	ParseARG_FETCH;
	yymsp = &stack.top();
	
#ifndef NDEBUG
	if(yyTraceStream && yyruleno>=0 
	   && yyruleno<sizeof(yyRuleName)/sizeof(yyRuleName[0]))
	{
		*yyTraceStream << yyTracePrompt << "Reduce [" << yyRuleName[yyruleno]
		<< "]." << std::endl;
	}
#endif /* NDEBUG */
	
	switch( yyruleno)
	{
			/* Beginning here are the reduction cases.  A typical example
			 * follows:
			 *   case 0:
			 *  #line <lineno> <grammarfile>
			 *     { ... }           // User supplied code
			 *  #line <lineno> <thisfile>
			 *     break;
			 */
	  case 0:
#line 24 "src/examples/example1.lmn"
{ std::cout << "Result=" << yymsp[0].minor.yy0 << std::endl; }
#line 664 "src/examples/example1.cpp"
		break;
	  case 1:
#line 26 "src/examples/example1.lmn"
{ yygotominor.yy0 = yymsp[-2].minor.yy0 - yymsp[0].minor.yy0; }
#line 669 "src/examples/example1.cpp"
		break;
	  case 2:
#line 27 "src/examples/example1.lmn"
{ yygotominor.yy0 = yymsp[-2].minor.yy0 + yymsp[0].minor.yy0; }
#line 674 "src/examples/example1.cpp"
		break;
	  case 3:
#line 28 "src/examples/example1.lmn"
{ yygotominor.yy0 = yymsp[-2].minor.yy0 * yymsp[0].minor.yy0; }
#line 679 "src/examples/example1.cpp"
		break;
	  case 4:
#line 29 "src/examples/example1.lmn"
{ 

         if(yymsp[0].minor.yy0 != 0){
           yygotominor.yy0 = yymsp[-2].minor.yy0 / yymsp[0].minor.yy0;
          }else{
           std::cout << "divide by zero" << std::endl;
           }
}
#line 691 "src/examples/example1.cpp"
		break;
	  case 5:
#line 38 "src/examples/example1.lmn"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 696 "src/examples/example1.cpp"
		break;
	}
	yygoto = yyRuleInfo[yyruleno].lhs;
	yysize = yyRuleInfo[yyruleno].nrhs;
	//index -= yysize;
	stack.lop(yysize);
	yyact = find_reduce_action(yygoto);
	if(yyact < YYNSTATE)
	{
		shift(yyact,yygoto,&yygotominor);
	}
	else if(yyact == YYNSTATE + YYNRULE + 1)
	{
		accept();
	}
}

/*
 * The following code executes when the parse fails
 */
void yyParser::parse_failed()
{
	ParseARG_FETCH;
#ifndef NDEBUG
	if(yyTraceStream)
	{
		*yyTraceStream << yyTracePrompt << "Fail!" << std::endl;
	}
#endif
	//while(index >= 0)
	//yy_pop_parser_stack(yypParser);
	stack.clear();
	/* Here code is inserted which will be executed whenever the
	 * parser fails */
	ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
 * The following code executes when a syntax error first occurs.
 */
void yyParser::syntax_error(int yymajor, YYMINORTYPE yyminor)
{
	ParseARG_FETCH;
#define TOKEN (yyminor.yy0)
#line 20 "src/examples/example1.lmn"
  
  std::cout << "Syntax error!" << std::endl;  

#line 745 "src/examples/example1.cpp"
	ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
#undef TOKEN
}

/*
 * The following is executed when the parser accepts
 */
void yyParser::accept()
{
	ParseARG_FETCH;
#ifndef NDEBUG
	if(yyTraceStream)
	{
		*yyTraceStream << yyTracePrompt << "Accept!" << std::endl;
	}
#endif
	//while(yypParser->index>=0) yy_pop_parser_stack(yypParser);
	stack.clear();

	/* Here code is inserted which will be executed whenever the
	 * parser accepts */
	ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
 * The first argument is a pointer to a structure obtained from
 * "ParseAlloc" which describes the current state of the parser.
 * The second argument is the major token number.  The third is
 * the minor token.  The fourth optional argument is whatever the
 * user wants (and specified in the grammar) and is available for
 * use by the action routines.
 *
 * Inputs:
 * <ul>
 * <li> A pointer to the parser (an opaque structure.)
 * <li> The major token number.
 * <li> The minor token number.
 * <li> An option argument of a grammar-specified type.
 * </ul>
 *
 * Outputs:
 * None.
 */
void yyParser::Parse(int yymajor, ParseTOKENTYPE yyminor ParseARG_PDECL)
{
	YYMINORTYPE yyminorunion;
	int yyact;            		/* The parser action. */
	bool yyendofinput;     		/* True if we are at the end of input */
	bool yyerrorhit = false;	/* True if yymajor has invoked an error */
	
	/* (re)initialize the parser, if necessary */
	if(stack.empty())
	{
		if(yymajor == 0)
			return;
		errCount = -1;
		stack.push(yyStackEntry());
	}
	yyminorunion.yy0 = yyminor;
	yyendofinput = (yymajor==0);
	ParseARG_STORE;
	
#ifndef NDEBUG
	if(yyTraceStream)
	{
		*yyTraceStream << yyTracePrompt << "Input " << yyTokenName[yymajor]
		<< std::endl;
	}
#endif
	
	do
	{
		yyact = find_shift_action(yymajor);
		if(yyact<YYNSTATE)
		{
			shift(yyact,yymajor,&yyminorunion);
			errCount--;
			if(yyendofinput && stack.size())
			{
				yymajor = 0;
			}
			else
			{
				yymajor = YYNOCODE;
			}
		}
		else if(yyact < YYNSTATE + YYNRULE)
		{
			reduce(yyact-YYNSTATE);
		}
		else if(yyact == YY_ERROR_ACTION)
		{
			int yymx;
#ifndef NDEBUG
			if(yyTraceStream)
			{
				*yyTraceStream << yyTracePrompt << "Syntax Error!" << std::endl;
			}
#endif
#ifdef YYERRORSYMBOL
			/* A syntax error has occurred.
			 * The response to an error depends upon whether or not the
			 * grammar defines an error token "ERROR".  
			 *
			 * This is what we do if the grammar does define ERROR:
			 *
			 *  * Call the %syntax_error function.
			 *
			 *  * Begin popping the stack until we enter a state where
			 *    it is legal to shift the error symbol, then shift
			 *    the error symbol.
			 *
			 *  * Set the error count to three.
			 *
			 *  * Begin accepting and shifting new tokens.  No new error
			 *    processing will occur until three tokens have been
			 *    shifted successfully.
			 *
			 */
			if(errCount<0){
				syntax_error(yymajor,yyminorunion);
			}
			yymx = stack.top().major;
			if(yymx==YYERRORSYMBOL || yyerrorhit)
			{
#ifndef NDEBUG
				if(yyTraceStream)
				{
					*yyTraceStream << yyTracePrompt << "Discard input token "
						<< yyTokenName[yymajor] << std::endl;
				}
#endif
				destructor(yymajor,&yyminorunion);
				yymajor = YYNOCODE;
			}
			else
			{
				while(stack.size() >= 0 &&
					  yymx != YYERRORSYMBOL &&
					  (yyact = find_shift_action(YYERRORSYMBOL)) >= YYNSTATE)
				{
					stack.lop();
				}
				if(stack.empty() || yymajor==0)
				{
					destructor(yymajor,&yyminorunion);
					parse_failed();
					yymajor = YYNOCODE;
				}
				else if(yymx!=YYERRORSYMBOL)
				{
					YYMINORTYPE u2;
					u2.YYERRSYMDT = 0;
					shift(yyact,YYERRORSYMBOL,&u2);
				}
			}
			errCount = 3;
			yyerrorhit = 1;
#else  /* YYERRORSYMBOL is not defined */
			/* This is what we do if the grammar does not define ERROR:
			 *
			 *  * Report an error message, and throw away the input token.
			 *
			 *  * If the input token is $, then fail the parse.
			 *
			 * As before, subsequent error messages are suppressed until
			 * three input tokens have been successfully shifted.
			 */
			if(errCount<=0)
			{
				syntax_error(yymajor,yyminorunion);
			}
			errCount = 3;
			destructor(yymajor,&yyminorunion);
			if(yyendofinput){
				parse_failed();
			}
			yymajor = YYNOCODE;
#endif
		}
		else
		{
			accept();
			yymajor = YYNOCODE;
		}
	}
	while(yymajor!=YYNOCODE && stack.size());
	return;
}
