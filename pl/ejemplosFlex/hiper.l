/*** hiper.l ***/
/*** Zona de las declaraciones o definiciones ***/
%{
   /* Descripción
 
 	Se muestra el uso de yymore()
      
   */
%}

/***** Zona de las reglas *****/
%%
hiper 	 yymore();
texto 	 printf("Token = %s\n",yytext);
mercado  printf("Token = %s\n",yytext);
.|\n	 ;  /* Se descartan el resto de caracteres */
%%


/***** Zona de funciones auxiliares *****/

extern FILE *yyin, *yyout;
int  main(int argc, char *argv[])
{
 
 switch(argc)
  {
   case 2:  yyin=fopen(argv[1],"r"); 
            break;
   case 3:  yyin=fopen(argv[1],"r"); 
            yyout=fopen(argv[2],"w"); 
  }
  yylex();

  return 0;
}
