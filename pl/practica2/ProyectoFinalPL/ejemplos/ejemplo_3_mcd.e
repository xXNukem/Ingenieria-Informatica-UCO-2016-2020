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

  Fichero de ejemplo nº 3 para el intérprete de pseudocódigo en español: ipe.exe
#
 _lugar(5,5);
                      escribir_cadena('Escribe el numero de terminos de la serie: ');
                      leer(T);

                      si(T > 0)
                        entonces

                          term1:=0;
                          term2:=1;

                          _lugar(6,5);
                          escribir(term1);
                          escribir_cadena(' ');
                          escribir(term2);

                          para i
                          desde 0
                          hasta T
                          hacer

                            term3:=term1+term2;

                              escribir_cadena(' ');
                              escribir(term3);

                            term1:=term2;
                            term2:=term3;

                          fin_para;

                      fin_si;