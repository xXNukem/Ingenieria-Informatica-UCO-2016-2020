#
  Asignatura:    Procesadores de Lenguajes

  Titulación:    Ingeniería Informática
  Especialidad:  Computación
  Curso:         Tercero
  Cuatrimestre:  Segundo

  Departamento:  Informática y Análisis Numérico
  Centro:        Escuela Politécnica Superior de Córdoba
  Universidad de Córdoba
 
  Curso académico: 2018 - 2019

  Fichero de ejemplo para el proyecto final de Procesadores de Lenguajes
#

@ Bucle para menú


opc:=6;
mientras (opc<>0) hacer

@ Mostrar opciones disponibles

    _borrar;

    _lugar(10,10);
    escribir_cadena(' Ejemplo 1: Progresión (3n+4)*P del rango A-B de números primos ');

    _lugar(11,10);
    escribir_cadena(' Ejemplo 2: Obtener triangulos cuya suma de catetos sea divisible entre un numero ');

    _lugar(12,10);
    escribir_cadena(' Ejemplo 3: Obtener los N primeros términos de la serie de Fibbonacci ');

    _lugar(13,10);
    escribir_cadena(' Ejemplo 4: Determinar si un número es perfecto (Sus divisores suman el mismo) ');

    _lugar(14,10);
    escribir_cadena(' Finalizar ---------------> 0 ');

    _lugar(15,13);
    escribir_cadena(' Elige una opcion ');

    leer(opc);
    _borrar;


    si (opc = 1)
      entonces
	@inicio

		_lugar(5,5);
  	        escribir_cadena('Escribe el rango numerico: ');
  	        escribir_cadena('Desde A = ');
  	        leer(A);
            _lugar(6,32);
  	        escribir_cadena('Hasta B = ');
  	        leer(B);
            _lugar(7,5);
            escribir_cadena(' Escribe el numero de terminos de la progresion: ');
            leer(L);
            _borrar;
            _lugar(5,5);
            escribir_cadena('Obteniendo numeros primos y sus progresiones (3n+4)*P ');
            pos:=6;
  		        si(B > A)
    		        entonces
        					para i 
                  desde A 
                  hasta B 
        					hacer

                    cont:=0;

                        para j
                        desde 1
                        hasta i
                        hacer
                          
                          si (i _mod j = 0)
                          entonces
                            cont:=cont+1;
                          fin_si;
                          
                        fin_para

                      si(cont = 2)
                        entonces

                          _lugar(pos,5);
                          escribir(i);
                          escribir_cadena('->');

                            para k
                            desde 0
                            hasta L-1
                            hacer

                              term1:=3*(K+4);
                              term2:=term1*i;
                              escribir_cadena(' ');
                              escribir(term2);

                            fin_para;

                            escribir_cadena(' \n');

                          pos:=pos+1;
                      fin_si;

        					fin_para;

  				    fin_si;

	@fin
         escribir_cadena('\nEscribe cualquier letra para continuar: ');
          leer_cadena(D);
    

    si_no  
    si (opc = 2)
      entonces
         @inicio

	@fin

             escribir_cadena('\nEscribe cualquier letra para continuar: ');
            leer_cadena(D);
            
    si_no
    si (opc = 3)
      entonces
           @inicio

	@fin

               escribir_cadena('\nEscribe cualquier letra para continuar: ');
              leer_cadena(D);
    si_no
    si (opc = 4)
     entonces
           @inicio

		@fin

                 escribir_cadena('\nEscribe cualquier letra para continuar: ');
                leer_cadena(D);

	sino
	

      fin_si;

fin_si;
fin_si;
fin_si;


fin_mientras;
