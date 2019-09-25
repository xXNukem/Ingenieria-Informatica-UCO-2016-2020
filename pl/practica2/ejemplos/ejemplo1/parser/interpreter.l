/*! 
  \file interpreter.l
  \brief Lexical or scanner file
*/

%{
#include <iostream>

/* Macros for the screen */
#include "../includes/macros.hpp"

/*  interpreter.tab.h contains the numeric values of the tokens produced by the parser */
#include "interpreter.tab.h"

extern int lineNumber; //!< External line counter

%}

/*! \name REGULAR DEFINITIONS  */

DIGIT  [0-9]

NUMBER1 {DIGIT}+\.?
NUMBER2 {DIGIT}*\.{DIGIT}+

/*! \name REGULAR EXPRESSIONS  */
%%

[ \t] 	{ ; }    /* skip white space and tabulator */

\n      { 
			/* Line counter */
			lineNumber++; 
			return '\n';
		}

{NUMBER1}|{NUMBER2}  {
                       return NUMBER; 
                      }


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
		 // PLACE(24,10);
	  	  std::cout <<  BICYAN;
	   	  std::cout <<  ">>>>>>> End of file <<<<<<<";
	 	  std::cout << std::endl;
	   	  std::cout << RESET;
		  // PLACE(25,1);

	  	  return 0;
	}

.       { 
			/* Any other character */
          	return yytext[0];
		}
%%
