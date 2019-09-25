/*! 
  \file interpreter.y
  \brief Grammar file
*/

%{
#include <iostream>
#include <string>

/* Error recovery functions */
#include "../error/error.hpp"

/* Macros for the screen */
#include "../includes/macros.hpp"


/*! 
	\brief  Lexical or scanner function
	\return int
	\note   C++ requires that yylex returns an int value
	\sa     yyparser
*/
int yylex();

extern int lineNumber; //!<  External line counter

%}

/* In case of a syntactic error, more information is shown */
%error-verbose

//! \name Grammar symbols

/* Initial grammatical symbol */
%start program 

/* Defined token */
%token NUMBER

/* Left associativity  */

/* Minimum precedence */
%left '+' '-'

/* Maximum precedence */
%left '*' '/'

%%
//! \name Grammar rules

program : stmtlist
		 { 
			std::cout << "program --> stmtlist" << std::endl;
		 }
; 

stmtlist:  /* Empty: epsilon rule */
			{
				std::cout << "stmtlist -->  epsilon " << std::endl;
			}

		| stmtlist '\n'  /* Empty line */
			{
				std::cout << "stmtlist -->  '\\n' " << std::endl;
			}

        | stmtlist exp '\n'
            { 
				std::cout << "stmtlist --> stmtlist exp '\\n' " << std::endl;

				std::cout << BIYELLOW; 
				std::cout << "Correct expression " << std::endl << std::endl;
				std::cout << RESET; 
            }

        | stmtlist error '\n' 
			{
				// The function yyerror is called
				// If %error-verbose is used then an error message is displayed

				std::cout << "stmtlist -->  stmtlist error '\\n' " << std::endl;
			}
;

exp:	NUMBER 
       { std::cout << "exp --> NUMBER" << std::endl;}

	|	exp '+' exp 
		{ std::cout << "exp --> exp '+' exp" << std::endl;}

	|	exp '-' exp
		{ std::cout << "exp --> exp '-' exp" << std::endl;}

	|	exp '*' exp 
		{ std::cout << "exp --> exp '*' exp" << std::endl;}

	|	exp '/' exp 
		{ std::cout << "exp --> exp '/' exp" << std::endl;}

	|	'(' exp ')'
		{ std::cout << "exp --> '(' exp ')' " << std::endl;}
;
 
%%

