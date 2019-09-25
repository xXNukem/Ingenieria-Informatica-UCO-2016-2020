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

extern int lineNumber; //!< External line counter

%}

/*! \name REGULAR DEFINITIONS  */

DIGIT  [0-9]

NUMBER1 {DIGIT}+\.?
NUMBER2 {DIGIT}*\.{DIGIT}+

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
        	return NEWLINE;
        }

{NUMBER1}|{NUMBER2}  {
					  /* MODIFIED in example 4 */
					  /* Conversion of type and sending of the numerical value to the parser */
					   yylval.number = atof(yytext); 

                       return NUMBER; 
                      }

"-"		{ return MINUS;  } 			/* NEW in example 3 */
"+"		{ return PLUS;   } 			/* NEW in example 3 */

"*"	    { return MULTIPLICATION;  } /* NEW in example 3 */
"/"     { return DIVISION; } 		/* NEW in example 3 */

"("     { return LPAREN; } 			/* NEW in example 3 */
")"	    { return RPAREN; } 			/* NEW in example 3 */


^# { /* The interpreter finishes when the symbol # is written at the beginning of the line */
	// std::cout << CLEAR_SCREEN; 
	//  PLACE(24,10);
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

<ERROR>[^0-9+\-*/() \t\n]	{ 
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

