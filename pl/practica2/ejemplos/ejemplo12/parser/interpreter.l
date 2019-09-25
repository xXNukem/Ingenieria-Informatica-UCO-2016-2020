/*! 
  \file interpreter.l
  \brief Lexical or scanner file
*/

%{
#include <iostream>

/*********************/
/* NEW in example 4 */
/* atof */
#include <stdlib.h>
/*********************/

/* Macros for the screen */
#include "../includes/macros.hpp"

/*  interpreter.tab.h contains the numeric values of the tokens produced by the parser */
#include "interpreter.tab.h"

/********************/
/* NEW in example 3 */
#include "../error/error.hpp"
/********************/


/*********************************************/
/* NEW in example 7 */
/* Table of symbols */
#include "../table/table.hpp"

#include "../table/numericVariable.hpp"

extern lp::Table table; //!< External Table of Symbols
/*********************************************/

extern int lineNumber; //!< External line counter

%}

/*! \name REGULAR DEFINITIONS  */

DIGIT  [0-9] 

LETTER [a-zA-Z]

NUMBER1 {DIGIT}+\.?

NUMBER2 {DIGIT}*\.{DIGIT}+

IDENTIFIER  {LETTER}({LETTER}|{DIGIT})*

/* NEW in example 3 */
/* STATE  */
%x ERROR

/*! \name REGULAR EXPRESSIONS  */
%%

[ \t] 	{ ; }    /* skip white space and tabular */

\n      { 
			/* Line counter */
           	lineNumber++; 
	
			/* MODIFIED in example 3 */
			/* COMMENTED in example 5 */
        	/* return NEWLINE; */
        }

";"		{
			/* NEW in example 5 */
			return SEMICOLON;
		}

{NUMBER1}|{NUMBER2}  {
					  /* MODIFIED in example 4 */
					  /* Conversion of type and sending of the numerical value to the parser */
					   yylval.number = atof(yytext); 

                       return NUMBER; 
                      }

{IDENTIFIER}   	{
					/* NEW in example 7 */
					 std::string identifier(yytext);

					/* 
                         strdup() function returns a pointer to a new string 
                         which  is a duplicate of the string yytext
                    */
					yylval.identifier =  strdup(yytext); 

					/* If the identifier is not in the table of symbols then it is inserted */	
					if (table.lookupSymbol(identifier) == false)
					{
						// The identifier is inserted into the symbol table 
						// as undefined Variable
						lp::Variable *var = new lp::Variable(identifier,VARIABLE,UNDEFINED);

						// A pointer to the new NumericVariable is inserted into the table of symbols
						table.installSymbol(var);

						/* The identifier is returned as VARIABLE */
						return VARIABLE;
					}
					/* MODIFIED in example 11 */
					/* 
					   If the identifier is in the table of symbols 
					   then its token is returned. 
					*/
					else 
					{
						// Get the pointer to the identifier in the table of symbols
						lp::Symbol	*s = table.getSymbol(identifier);

						/*  The token of the identifier is returned  */
						return s->getToken();
					}
				}

"-"		{ return MINUS;  } 			/* NEW in example 3 */
"+"		{ return PLUS;   } 			/* NEW in example 3 */

"*"	    { return MULTIPLICATION; } 	/* NEW in example 3 */
"/"     { return DIVISION; } 		/* NEW in example 3 */

"("     { return LPAREN; } 			/* NEW in example 3 */
")"	    { return RPAREN; } 			/* NEW in example 3 */



"%"     { return MODULO; }			/* NEW in example 5 */

"^"	    { return POWER; }			/* NEW in example 5 */

"=" 	{ return ASSIGNMENT; }		/* NEW in example 7 */


^# { /* The interpreter finishes when the symbol # is written at the beginning of the line */
	// std::cout << CLEAR_SCREEN; 
	 // PLACE(24,10);
  	  std::cout <<  BIYELLOW;
   	  std::cout <<  ">>>>>>> End of program <<<<<<<";
 	  std::cout << std::endl;
   	  std::cout << RESET;
	 // PLACE(25,1);

  	  return 0;
	}

<<EOF>> { /* The interpreter finishes when finds the end of file character */
		 //  PLACE(24,10);
	  	  std::cout <<  BICYAN;
	   	  std::cout <<  ">>>>>>> End of file <<<<<<<";
	 	  std::cout << std::endl;
	   	  std::cout << RESET;
		  // PLACE(25,1);

	  	  return 0;
	}


.								{ 	
									/* Any other character */
									/* MODIFIIED in example 3 */
									/* Change to error state */
									BEGIN(ERROR); 

									/* 
										The current value of yytext 
										will be concatenated with the next character
									*/
									yymore();  
								}

<ERROR>[^0-9+\-*/()\^% \t\n\;a-zA-Z=]	{ /* MODIFIED in examples 5 and 7 */
								  /* NEW in example 3 */
								  /* 
									The current value of yytext 
									will be concatenated with the next character
								  */
									yymore(); 
								}

<ERROR>(.|\n)                { 
								/* NEW in example 3 */
								/* Rewind one position */
								yyless(yyleng-1); 

								/* Display the error message */
								warning("Lexical error", yytext);

								/* Restore the initial state */
   								BEGIN(INITIAL);
							}
%%
