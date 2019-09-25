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
_borrar; 
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
