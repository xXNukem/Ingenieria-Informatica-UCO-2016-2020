%{
  /* Descripción:
	El analizador léxico reconoce y cuenta cadenas delimitadas por comillas simples

        Se muestra el uso de 
		- BEGIN 
		- reglas condicionales controladas por un estado de flex definido por el programador
		- yymore()
	*/

  /* Indica el número de comentario */
 int numero_cadenas=0;

 /* Indica el número de líneas de cada comentario */
 int lineas_cadenas;
%}

/* Definiciones regulares */
letra         [a-zA-Z]
digito        [0-9]
identificador {letra}({letra}|{digito})*

/* Se define un nuevo estado de Flex: ESTADO_CADENA */
%x ESTADO_CADENA

%% 

{identificador}          {printf("identificador = %s\n", yytext);}

"'"			   {
			    /* Se activa el reconocimiento de la cadena */
			    BEGIN ESTADO_CADENA; 
			    numero_cadenas++; 
			    lineas_cadenas=1;
			  }


<ESTADO_CADENA>"'"  { /* Fin de la cadena: se vuelve al estado por defecto */
			         BEGIN 0; 
                     printf("\n nº cadena = %d, lineas_cadenas = %d\n", 
                            numero_cadenas, lineas_cadenas);

			         yytext[yyleng-1]='\0';
					 printf("\t Cadena reconocida = %s\n",yytext);
					}      

<ESTADO_CADENA>"\\\'"     {yymore();}

<ESTADO_CADENA>.          {yymore();}

<ESTADO_CADENA>\n         {lineas_cadenas++; yymore();}

.                         {ECHO;}
%%  


