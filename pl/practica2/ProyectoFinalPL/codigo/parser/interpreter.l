/*! 
  \file interpreter.l
  \brief Lexical or scanner file
*/
%{
#include <iostream>

/*********************/

/* atof */
#include <stdlib.h>
/*********************/

/* Macros for the screen */
#include "../includes/macros.hpp"

/*********************/

#include "../ast/ast.hpp"
/*********************/

#include "interpreter.tab.h"

/********************/

#include "../error/error.hpp"
/********************/

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

CHARACTER ({DIGIT}|{LETTER})

NUMBER1 {DIGIT}+\.?

NUMBER2 {DIGIT}*\.{DIGIT}+

NUMBER3 {DIGIT}+(\.{DIGIT}+)?(E[+\-]?{DIGIT}+)?

NUMBER ({NUMBER1}|{NUMBER2}|{NUMBER3})

IDENTIFIER  {LETTER}({CHARACTER}|(_{CHARACTER}))*

/* ESTADOS  */
%x ERROR ESTADO_COMENTARIO ESTADO_COMENTARIO_SIMPLE ESTADO_CADENA
/*! \name REGULAR EXPRESSIONS  */
%%
 
"'"			   {
			    /* Se activa el reconocimiento de la cadena */
				yylval.strings = new std::string("");
			    BEGIN ESTADO_CADENA; 
			  }


<ESTADO_CADENA>"'"  { /* Fin de la cadena: se vuelve al estado por defecto */
			         BEGIN 0; 
			         yytext[yyleng-1]='\0';
				     yylval.strings -> append(std::string(yytext));
				     return STRING;
					}      

<ESTADO_CADENA>"\\\'"     {yymore();}

<ESTADO_CADENA>.          {yymore();}

"@"			{	BEGIN ESTADO_COMENTARIO_SIMPLE; }

<ESTADO_COMENTARIO_SIMPLE>[^"\n"]          {;}

<ESTADO_COMENTARIO_SIMPLE>"\n"          {	BEGIN 0;	}

"#"			{	BEGIN ESTADO_COMENTARIO; }

<ESTADO_COMENTARIO>[^#]          {;}

<ESTADO_COMENTARIO>"#"          {	BEGIN 0;	}

[ \t] 	{ ; }    /* se saltan espacios y tabulaciones */

\n      { 
			/* contador de líneas */
           	lineNumber++; 
        }

";"		{ return SEMICOLON; }


","		{ return COMMA; }




{NUMBER}  { 
					  /* Conversion of type and sending of the numerical value to the parser */
					   yylval.number = atof(yytext); 

                       return NUMBER; 
                      }
(?i:_borrar)			 { return ERASE; }
(?i:_lugar)			 { return PLACE; }


{IDENTIFIER}   		 {
						for (int i = 0; i < strlen(yytext); ++i)
						{
							yytext[i]=tolower(yytext[i]);
						}
						 
						 std::string identifier(yytext);

						/* 
							La función strdup () devuelve un puntero a una nueva cadena
                          que es un duplicado de la cadena yytext
                        */
						  yylval.identifier =  strdup(yytext); 

						/* Si el identificador no está en la tabla de símbolos, entonces se inserta */	
						 if (table.lookupSymbol(identifier) == false)
							{
								/* 
									El identificador se inserta en la tabla de símbolos.
									como variable indefinida con valor 0.0
								*/
								lp::NumericVariable *n = new lp::NumericVariable(identifier,VARIABLE,UNDEFINED,0.0);

								/* Un puntero a la nueva NumericVariable se inserta en la tabla de símbolos */
								table.installSymbol(n);

								return VARIABLE;
							}

						
						/* 
							Si el identificador está en la tabla de símbolos, se devuelve su token.
							El identificador puede ser una variable o una constante numérica.
						*/
						else 
							{
								lp::Symbol	*s = table.getSymbol(identifier);

								/*  Si el identificador está en la tabla, se devuelve su token.  */
								return s->getToken();
							}
                     }


"-"		{ return MINUS;  } 			
"+"		{ return PLUS;   } 			

"*"	    { return MULTIPLICATION; } 	
"/"     { return DIVISION; } 		

"("     { return LPAREN; } 			
")"	    { return RPAREN; } 			

"--"		{ return UNARY_MINUS;  }
"++"		{ return UNARY_PLUS;   }

(?i:_div)	{ return DIVISION_INT; }

(?i:_mod)     { return MODULO; }			

"**"	    { return POWER; }			

":=" 	{ return ASSIGNMENT; }		

"="	{ return EQUAL; }			

"<>"	{ return NOT_EQUAL; }		

">="	{ return GREATER_OR_EQUAL; }

"<="	{ return LESS_OR_EQUAL; }	

">"		{ return GREATER_THAN; }	

"<"		{ return LESS_THAN; }		

"||"	{ return CONCATENATION;}

(?i:_no)		{ return NOT; }				

(?i:_o)	{ return OR; }				

(?i:_y)	{ return AND; }				


<<EOF>> {
	  	  return 0;
	}


.								{ 	
									/* Cambiar a estado de error */
									BEGIN(ERROR); 
									/* Se concatenan los caracteres */
									yymore();  
								}

	
{NUMBER}(\.{DIGIT}+)+    {								
								/* Mostrar mensaje de error */
								warning("Error léxico: Formato de número no valido", yytext);

   							}

<ERROR>({DIGIT}+{IDENTIFIER}*|_*{IDENTIFIER}*|{IDENTIFIER}*_+|{CHARACTER}*__+{CHARACTER}*)	{
								
								/* Mostrar mensaje de error */
								warning("Error léxico: Identificador no válido", yytext);

								/* Restaurar al estado inicial */
   								BEGIN(INITIAL);
							}

<ERROR>[^0-9+\-*/()\^% \t\n\;a-zA-Z=<>!&]	{ /* MODIFIED in examples 5, 7, 15 */
								  
								  /* Se concatenan los caracteres */
									yymore(); 
								}		

<ERROR>(.|\n)                { 
								
								/* Si es cualquier caracter se borra, y se continua el análisis */
								yyless(yyleng-1); 

								/* Mostrar mensaje de error */
								warning("Error léxico", yytext);

								/* Restaurar al estado inicial */
   								BEGIN(INITIAL);
							}
%%

