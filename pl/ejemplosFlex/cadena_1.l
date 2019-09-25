%{

  /* Descripcion:
	El analizador léxico reconoce cadenas delimitadas por comillas simples

 */

%}

/* Definiciones regulares */
letra          [a-zA-Z]
digito         [0-9]
identificador  {letra}({letra}|{digito})*
cadena	       "'"([^']|"\\\'")*"'"


%% 

{identificador} {printf("identificador = %s\n", yytext);}


{cadena}		{ 
               		/* Se ha reconocido una cadena */
                    printf("\t Cadena reconocida = %s\n",yytext);
				}      

.				{ECHO;}

%%  

