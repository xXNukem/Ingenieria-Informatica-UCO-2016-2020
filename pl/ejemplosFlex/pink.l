/**************************** pink.l ***********************************/
/***** Zona de las declaraciones o definiciones *****/
%{
   /* Descripción

    	Se muestra el uso de REJECT
   */

/*  Variables globales */
int n_pink = 0;
int n_ink = 0;
int n_pin = 0;
%}

/***** Zona de las reglas *****/
%%
pink 	{n_pink++; REJECT;}
ink     {n_ink++; REJECT;}
pin 	{n_pin++; REJECT;}
.|\n	;  /* Se descartan el resto de caracteres */
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

  fprintf(yyout,"Contador de argv\n");
  fprintf(yyout,"\t pink = %d\n", n_pink);
  fprintf(yyout,"\t ink = %d\n", n_ink);
  fprintf(yyout,"\t pin = %d\n", n_pin);

  return 0;
}
