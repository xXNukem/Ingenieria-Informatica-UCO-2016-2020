/*! 
  \file interpreter.y
  \brief Grammar file
*/


%{
#include <iostream>
#include <string>

/*******************************************/
/* NEW in example 5 */
/* pow */
#include <math.h>
/*******************************************/

/*******************************************/
/* NEW in example 6 */
/* Use for recovery of runtime errors */
#include <setjmp.h>
#include <signal.h>
/*******************************************/

/* Error recovery functions */
#include "../error/error.hpp"

/* Macros for the screen */
#include "../includes/macros.hpp"

/*******************************************/
/* NEW in example 7 */
/* Table of symbol */
#include "../table/table.hpp"

#include "../table/numericVariable.hpp"
/*******************************************/


/*! 
	\brief  Lexical or scanner function
	\return int
	\note   C++ requires that yylex returns an int value
	\sa     yyparser
*/
int yylex();


extern int lineNumber; //!< External line counter


/***********************************************************/
/* NEW in example 2 */
extern std::string progname; //!<  Program name
/***********************************************************/

/*******************************************/
/* NEW in example 6 */
/*
 jhmp_buf
    This is an array type capable of storing the information of a calling environment to be restored later.
   This information is filled by calling macro setjmp and can be restored by calling function longjmp.
*/
jmp_buf begin; //!<  It enables recovery of runtime errors 
/*******************************************/


/*******************************************/
/* NEW in example 7 */
extern lp::Table table; //!< Externa Table of Symbols

%}
/* In case of a syntactic error, more information is shown */
%error-verbose

/* Initial grammar symbol */
%start program

/*******************************************/
/* NEW in example 4 */
/* MODIFIED in example 7: identifier */
/* Data type YYSTYPE  */
%union {
  double number;  
  char * identifier;   /* NEW in example 7 */
}

/* Data type of the non-terminal symbol "exp" */
%type <number> exp

/* NEW in example 7 */
%token <identifier> VARIABLE UNDEFINED 

/* Defined token */

/* Minimum precedence */

/*******************************************/
/* NEW in example 5 */
%token SEMICOLON
/*******************************************/

/* NEW in example 7 */
%right ASSIGNMENT

/*******************************************/
/* MODIFIED in example 4 */
%token <number> NUMBER
/*******************************************/

/* Left associativity */

/*******************************************/
/* MODIFIED in example 3 */
%left PLUS MINUS 

/* NEW in example 5: MODULO */
%left MULTIPLICATION DIVISION MODULO

%left LPAREN RPAREN

%nonassoc  UNARY

/* Maximum precedence  */
/* NEW in example 5 */
%right POWER
/*******************************************/

%%
//! \name Grammar rules

program : stmtlist {  }
;

		/* MODIFIED in example 5: SEMICOLON */ 
stmtlist:  /* empty: epsilon rule */

		| stmtlist SEMICOLON     /* empty line */

		/* MODIFIED in example 4: the result of the expression is displayed  */ 
        | stmtlist exp SEMICOLON
            { 
				std::cout << BIYELLOW; 
				std::cout << "Result: ";
				std::cout << RESET; 
				std::cout << $2 << std::endl << std::endl;
            }

        | stmtlist error SEMICOLON
			{
				// The function yyerror is called
				// If %error-verbose is used then an error message is displayed
			}
;

		/* MODIFIED in example 3: tokens PLUS, MINUS, ... */
		/* NEW in example 3: unary operators */
		/* NEW in example 4: evaluation of the expressions */ 
		/* NEW in example 5: MODULO, POWER */
		/* MODIFIED in example 6: control of runtime errors */ 
		/* NEW in example 7: VARIABLE, ASSIGNMENT */
exp:	NUMBER 
		{ $$ = $1; }

	| 	exp PLUS exp 
		{ $$ = $1 + $3; }

	| 	exp MINUS exp
      	{ $$ = $1 - $3; }

	| 	exp MULTIPLICATION exp 
		{ $$ = $1 * $3; }

	| 	exp DIVISION exp
		{	
			/* MODIFIED in example 6 */ 
	         if ($3 == 0.0) 
  				 execerror("Runtime error in division", "Division by zero");
			 else 
    	         $$ = $1 / $3;
	   }

	| 	LPAREN exp RPAREN
       	{ $$ = $2; }

		/* NEW in example 3 */
  	| 	PLUS exp %prec UNARY
		{ $$ = +$2; }

		/* NEW in example 3 */
	| 	MINUS exp %prec UNARY
		{ $$ = -$2; }

		/* NEW in example 5 */
	|	exp MODULO exp 
		{
			/* MODIFIED in example 6 */ 
	         if ($3 == 0.0) 
  				 execerror("Runtime error in modulo", "Division by zero");
			 else 
    	         $$ = (int) $1 % (int) $3;
       }

		/* NEW in example 5 */
	|	exp POWER exp 
     	{ $$ = pow($1,$3); }


		/* IMPORTANT */
		/* NEW in example 7 and REMOVED in example 8 */
	|  VARIABLE ASSIGNMENT exp 
		{   
			/* Get the identifier in the table of symbols as Variable */
			lp::Variable *var = (lp::Variable *) table.getSymbol($1);

			// Check if the type of the variable is NUMBER
			if (var->getType() == NUMBER)
			{
				/* Get the identifier in the table of symbols as NumericVariable */
				lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol($1);
						
				/* Assignment the value of expression to the identifier */
				n->setValue($3);
			}
			// The type of variable $1 is not NUMBER
			else
			{
				// Delete $1 from the table of symbols as Variable
				table.eraseSymbol($1);

				// Insert $1 in the table of symbols as NumericVariable 
				// with the type NUMBER and the value $3
				lp::NumericVariable *n = new lp::NumericVariable($1,VARIABLE,NUMBER,$3);

				table.installSymbol(n);
			}

			/* Copy the value of the expression to allow multiple assignment: a = b = c = 2; */
			$$ = $3;
		}

		/* NEW in example 7 */
	 | VARIABLE
		{
			/* Get the identifier in the table of symbols as NumericVariable */
			lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol($1);

			// Check if the type of the identifier is NUMBER
			if (n->getType() == NUMBER)
				// Copy the value of the identifier
				$$ = n->getValue();
			else			 
				execerror("The variable is UNDEFINED", n->getName());
		}
;

%%
