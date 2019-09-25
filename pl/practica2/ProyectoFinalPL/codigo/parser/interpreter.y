/*! 
  \file interpreter.y
  \brief Grammar file
*/


%{
#include <iostream>
#include <string>

/*******************************************/
/* pow */
#include <math.h>
/*******************************************/

/*******************************************/
/* Use for recovery of runtime errors */
#include <setjmp.h>
#include <signal.h>
/*******************************************/

/* Error recovery functions */
#include "../error/error.hpp"

/* Macros for the screen */
#include "../includes/macros.hpp"


#include "../ast/ast.hpp"

/*******************************************/
#include "../table/table.hpp"
/*******************************************/

/*******************************************/
#include "../table/numericVariable.hpp"
/*******************************************/


#include "../table/logicalVariable.hpp"
#include "../table/stringVariable.hpp"

/*******************************************/
#include "../table/numericConstant.hpp"
/*******************************************/

/*******************************************/
#include "../table/logicalConstant.hpp"
/*******************************************/

/*******************************************/
#include "../table/builtinParameter1.hpp"
/*******************************************/

/*******************************************/
#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter2.hpp"
/*******************************************/

/*******************************************/
#include "../table/init.hpp"
/*******************************************/

/*! 
	\brief  Lexical or scanner function
	\return int
	\note   C++ requires that yylex returns an int value
	\sa     yyparser
*/
int yylex();

extern int control;

extern int lineNumber; //!< External line counter

extern bool interactiveMode; //!< Control the interactive mode of execution of the interpreter


/***********************************************************/

extern std::string progname; //!<  Program name
/***********************************************************/

/*******************************************/

/*
 jhmp_buf
    This is an array type capable of storing the information of a calling environment to be restored later.
   This information is filled by calling macro setjmp and can be restored by calling function longjmp.
*/
jmp_buf begin; //!<  It enables recovery of runtime errors 
/*******************************************/


/*******************************************/
/* NEW in example 7 */
extern lp::Table table; //!< Extern Table of Symbols

/*******************************************/
/* NEW in example 16 */
extern lp::AST *root; //!< External root of the abstract syntax tree AST

%}



/* In case of a syntactic error, more information is shown */
%error-verbose

/* Initial grammar symbol */
%start program

/*******************************************/
/* Data type YYSTYPE  */
/* NEW in example 4 */
%union {
  char * identifier; 				 /* NEW in example 7 */
  double number;  
  bool logic;						 
  std::string * strings;
  lp::ExpNode *expNode;  			 /* NEW in example 16 */
  std::list<lp::ExpNode *>  *parameters;    // New in example 16; NOTE: #include<list> must be in interpreter.l, init.cpp, interpreter.cpp
  std::list<lp::Statement *> *stmts; /* NEW in example 16 */
  lp::Statement *st;				 /* NEW in example 16 */
  lp::AST *prog;					 /* NEW in example 16 */
}

/* Type of the non-terminal symbols */
%type <expNode> exp cond 

%type <parameters> listOfExp  restOfListOfExp

%type <stmts> stmtlist

%type <st> stmt asgn print read if while repeat for erase place

%type <prog> program

// Defined token

/* Minimum precedence */

%token SEMICOLON

%token PRINT READ PRINT_STRING READ_STRING IF THEN ELSE END_IF WHILE DO END_WHILE REPEAT UNTIL FOR FROM STEP END_FOR ERASE PLACE

%right ASSIGNMENT

%token COMMA

%token <number> NUMBER

%token <logic> BOOL

%token <strings> STRING

/* MODIFIED in examples 11, 13 */
%token <identifier> VARIABLE UNDEFINED CONSTANT BUILTIN

/* Left associativity */

/*******************************************************/

%left OR

%left AND

%nonassoc GREATER_OR_EQUAL LESS_OR_EQUAL GREATER_THAN LESS_THAN EQUAL NOT_EQUAL

%left NOT

/*******************************************************/


%left PLUS MINUS 


%left MULTIPLICATION DIVISION DIVISION_INT MODULO CONCATENATION 

%left LPAREN RPAREN

%nonassoc  UNARY UNARY_PLUS UNARY_MINUS

// Maximum precedence 

%right POWER


%%
//! \name Grammar rules

/* MODIFIED  Grammar in example 16 */

program : stmtlist
		  { 
		    // Create a new AST
			$$ = new lp::AST($1); 

			// Assign the AST to the root
			root = $$; 

			// End of parsing
			//	return 1;
		  }
;

stmtlist:  /* empty: epsilon rule */
		  { 
			// create a empty list of statements
			$$ = new std::list<lp::Statement *>(); 
		  }  

        | stmtlist stmt 
		  { 
			// copy up the list and add the stmt to it
			$$ = $1;
			$$->push_back($2);

			// Control the interative mode of execution of the interpreter
			if ( (interactiveMode == true) && (control == 0) )
 			   $2->evaluate();
           }


        | stmtlist error 
           { 
			// just copy up the stmtlist when an error occurs
			$$ = $1;

			// The previous look-ahead token ought to be discarded with `yyclearin;'
			yyclearin; 
           } 
;
 

stmt: SEMICOLON  /* Empty statement: ";" */
	  {
		// Create a new empty statement node
		$$ = new lp::EmptyStmt(); 
	  }
	| asgn  SEMICOLON
	  {
		// Default action
		// $$ = $1;
	  }
	| print SEMICOLON
	  {
		// Default action
		// $$ = $1;
	  }
	| read SEMICOLON
	  {
		// Default action
		// $$ = $1;
	  }
	
	| if 
	 {
		// Default action
		// $$ = $1;
	 }
	| while 
	 {
		// Default action
	 }
	| repeat{
		// Default action
	}
	| for
	{
		// Default action
	}
	| erase{
		// Default action
	}
	| place{

	}
;

controlSymbol: {
	control++;
}

for:/* For statement with step */
	FOR controlSymbol VARIABLE FROM exp UNTIL exp STEP exp DO stmtlist END_FOR
	{
			$$ =new lp::ForStmt($3, $5, $7, $9, $11);
			control--;
	}
	/* For statement without step */
	|	FOR controlSymbol VARIABLE FROM exp UNTIL exp DO stmtlist END_FOR
	{
			$$ =new lp::ForStmt($3, $5, $7, $9);
			control--;
	}
	|	FOR FROM exp UNTIL exp STEP exp DO stmtlist END_FOR
	{
			execerror("Error sintáctico","bucle para, recibe una variable");
	}
	|	FOR FROM exp UNTIL exp DO stmtlist END_FOR
	{
			execerror("Error sintáctico","bucle para, recibe una variable");
	}
	|	FOR controlSymbol VARIABLE exp UNTIL exp STEP exp DO stmtlist END_FOR
	{
			warning("Error sintáctico","bucle para, falta sentencia \"desde\"");
			$$ =new lp::ForStmt($3, $4, $6, $8, $10);
			control--;
	}
	|	FOR controlSymbol VARIABLE exp UNTIL exp DO stmtlist END_FOR
	{
			warning("Error sintáctico","bucle para, falta sentencia \"desde\"");
			$$ =new lp::ForStmt($3, $4, $6, $8);
			control--;
	}
	|	FOR controlSymbol VARIABLE FROM exp UNTIL exp STEP exp stmtlist END_FOR
	{
			warning("Error sintáctico","bucle para, falta sentencia \"hacer\"");
			$$ =new lp::ForStmt($3, $5, $7, $9, $10);
			control--;
	}
	|	FOR controlSymbol VARIABLE FROM exp UNTIL exp stmtlist END_FOR
	{
			warning("Error sintáctico","bucle para, falta sentencia \"hacer\"");
			$$ =new lp::ForStmt($3, $5, $7, $8);
			control--;
	}
 
	
if:	/* Simple conditional statement */
	IF controlSymbol cond THEN stmtlist END_IF
    {
		// Create a new if statement node
		$$ = new lp::IfStmt($3, $5);
		control--;
	}

	/* Compound conditional statement */
	| IF controlSymbol cond THEN stmtlist ELSE stmtlist END_IF
	 {
		// Create a new if statement node
		$$ = new lp::IfStmt($3, $5, $7);
		control--;
	 }
;

	
while:  WHILE controlSymbol cond DO stmtlist END_WHILE
		{
			// Create a new while statement node
			$$ = new lp::WhileStmt($3, $5);
			control--;
        }
;

repeat: REPEAT controlSymbol stmtlist UNTIL cond
		{
			$$=new lp::RepeatStmt($5,$3);
			control--;
		}
;		

	
cond: 	LPAREN exp RPAREN
		{ 
			$$ = $2;
		}
;

erase:	ERASE
		{
			$$=new lp::EraseStmt();
		}
;

place:	PLACE LPAREN exp COMMA exp RPAREN
		{
			$$=new lp::PlaceStmt($3, $5);
		}
		|
		PLACE LPAREN COMMA RPAREN
		{
			execerror("Error semático:", "La función \"lugar\" recibe dos parámetros");
		}
		PLACE LPAREN COMMA RPAREN
		{
			execerror("Error semático:", "La función \"lugar\" recibe dos parámetros");
		}
;

asgn:   VARIABLE ASSIGNMENT exp 
		{ 
			// Create a new assignment node
			$$ = new lp::AssignmentStmt($1, $3);
		}

	|  VARIABLE ASSIGNMENT asgn 
		{ 
			// Create a new assignment node
			$$ = new lp::AssignmentStmt($1, (lp::AssignmentStmt *) $3);
		}

	   
	| CONSTANT ASSIGNMENT exp 
		{   
 			execerror("Error semático en la asignación: no está permitido modificar una constante ", $1);
		}
	   
	| CONSTANT ASSIGNMENT asgn 
		{   
 			execerror("Error semático en la asignación multiple: no está permitido modificar una constante ",$1);
		}
;


print:  PRINT exp 
		{
			// Create a new print node
			 $$ = new lp::PrintStmt($2);
		}
		| PRINT_STRING exp
		{
			$$ = new lp::PrintStringStmt($2);
		}
;	

read:  READ LPAREN VARIABLE RPAREN  
		{
			// Create a new read node
			 $$ = new lp::ReadStmt($3);
		}

		|

		READ_STRING LPAREN VARIABLE RPAREN
		{
			// Create a new read node
			 $$ = new lp::ReadStringStmt($3);
		}

  	  
		| READ LPAREN CONSTANT RPAREN  
		{   
 			execerror("Error semático en \"escribir\": no está permitido modificar una constante ",$3);
		}
		| READ VARIABLE RPAREN
		{
 			warning("Error sintáctico", "sentencia \"escribir\": falta parentesis derecho");
 			$$ = new lp::ReadStmt($2);
		}
		| READ LPAREN VARIABLE
		{
 			warning("Error sintáctico", "sentencia \"escribir\": falta parentesis izquierdo");
			$$ = new lp::ReadStmt($3);
		}
		| READ LPAREN RPAREN
		{
			execerror("Error semático:", "La función \"escribir\" recibe un parámetro");
		}
;



exp:	NUMBER 
		{ 
			// Create a new number node
			$$ = new lp::NumberNode($1);
		}

	|
		STRING{
			$$ = new lp::StringNode($1);
		}

	| 	exp PLUS exp 
		{ 
			// Create a new plus node
			 $$ = new lp::PlusNode($1, $3);
		}

	| 	exp MINUS exp
      	{
			// Create a new minus node
			$$ = new lp::MinusNode($1, $3);
		}

	| 	exp MULTIPLICATION exp 
		{ 
			// Create a new multiplication node
			$$ = new lp::MultiplicationNode($1, $3);
		}

	| 	exp DIVISION exp
		{
		  // Create a new division node	
		  $$ = new lp::DivisionNode($1, $3);
	    }
	|
		exp DIVISION_INT exp{
			// Create a new division int node	
			$$ = new lp::DivisionIntNode($1, $3);
		}
	| 	LPAREN exp RPAREN
       	{ 
		    // just copy up the expression node 
			$$ = $2;
		 }
	|
		UNARY_PLUS VARIABLE %prec UNARY{
			$$ = new lp::UnaryAddNode($2);
		}
	|
		UNARY_MINUS VARIABLE %prec UNARY{
			$$ = new lp::UnarySubstractNode($2);
		}
	|
		VARIABLE UNARY_PLUS %prec UNARY{
			$$ = new lp::UnaryAddNode($1);
		}
	|
		VARIABLE UNARY_MINUS %prec UNARY{
			$$ = new lp::UnarySubstractNode($1);
		}
  	| 	PLUS exp %prec UNARY
		{ 
		  // Create a new unary plus node	
  		  $$ = new lp::UnaryPlusNode($2);
		}
	| 	MINUS exp %prec UNARY
		{ 
		  // Create a new unary minus node	
  		  $$ = new lp::UnaryMinusNode($2);
		}

	|	exp MODULO exp 
		{
		  // Create a new modulo node	

		  $$ = new lp::ModuloNode($1, $3);
        }

	|	exp POWER exp 
     	{ 
		  // Create a new power node	
  		  $$ = new lp::PowerNode($1, $3);
		}
	|	exp CONCATENATION exp
		{
		  // Create a new concatenate node	
  		  $$ = new lp::ConcatenateNode($1, $3);
		}
	| VARIABLE
		{
		  // Create a new variable node	
		  $$ = new lp::VariableNode($1);
		}

	 | CONSTANT
		{
		  // Create a new constant node	
		  $$ = new lp::ConstantNode($1);

		}

	| BUILTIN LPAREN listOfExp RPAREN
		{
			// Get the identifier in the table of symbols as Builtin
			lp::Builtin *f= (lp::Builtin *) table.getSymbol($1);

			// Check the number of parameters 
			if (f->getNParameters() ==  (int) $3->size())
			{
				switch(f->getNParameters())
				{
					case 0:
						{
							// Create a new Builtin Function with 0 parameters node	
							$$ = new lp::BuiltinFunctionNode_0($1);
						}
						break;

					case 1:
						{
							// Get the expression from the list of expressions
							lp::ExpNode *e = $3->front();

							// Create a new Builtin Function with 1 parameter node	
							$$ = new lp::BuiltinFunctionNode_1($1,e);
						}
						break;

					case 2:
						{
							// Get the expressions from the list of expressions
							lp::ExpNode *e1 = $3->front();
							$3->pop_front();
							lp::ExpNode *e2 = $3->front();

							// Create a new Builtin Function with 2 parameters node	
							$$ = new lp::BuiltinFunctionNode_2($1,e1,e2);
						}
						break;

					default:
				  			 execerror("Error sintáctico: demasiados parámetros para la función", $1);
				} 
			}
			else
	  			 execerror("Error sintáctico: número de parámetros incompatibles con la función", $1);
		}

	| exp GREATER_THAN exp
	 	{
		  // Create a new "greater than" node	
 			$$ = new lp::GreaterThanNode($1,$3);
		}

	| exp GREATER_OR_EQUAL exp 
	 	{
		  // Create a new "greater or equal" node	
 			$$ = new lp::GreaterOrEqualNode($1,$3);
		}

	| exp LESS_THAN exp 	
	 	{
		  // Create a new "less than" node	
 			$$ = new lp::LessThanNode($1,$3);
		}

	| exp LESS_OR_EQUAL exp 
	 	{
		  // Create a new "less or equal" node	
 			$$ = new lp::LessOrEqualNode($1,$3);
		}

	| exp EQUAL exp 	
	 	{
		  // Create a new "equal" node	
 			$$ = new lp::EqualNode($1,$3);
		}

    | exp NOT_EQUAL exp 	
	 	{
		  // Create a new "not equal" node	
 			$$ = new lp::NotEqualNode($1,$3);
		}

    | exp AND exp 
	 	{
		  // Create a new "logic and" node	
 			$$ = new lp::AndNode($1,$3);
		}

    | exp OR exp 
	 	{
		  // Create a new "logic or" node	
 			$$ = new lp::OrNode($1,$3);
		}

    | NOT exp 
	 	{
		  // Create a new "logic negation" node	
 			$$ = new lp::NotNode($2);
		}
;


listOfExp: 
			/* Empty list of numeric expressions */
			{
			    // Create a new list STL
				$$ = new std::list<lp::ExpNode *>(); 
			}

	|  exp restOfListOfExp
			{
				$$ = $2;

				// Insert the expression in the list of expressions
				$$->push_front($1);
			}
;

restOfListOfExp:
			/* Empty list of numeric expressions */
			{
			    // Create a new list STL
				$$ = new std::list<lp::ExpNode *>(); 
			}

		|	COMMA exp restOfListOfExp
			{
				// Get the list of expressions
				$$ = $3;

				// Insert the expression in the list of expressions
				$$->push_front($2);
			}
;



%%



