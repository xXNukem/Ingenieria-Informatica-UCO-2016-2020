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
                      escribir_cadena('Escribe el número por el que la suma de los catetos debe ser divisible: ');
                      escribir_cadena('N = ');
                      leer(N);
                      _lugar(7,22);
                      escribir_cadena(' Escribe el valor máximo que pueden tener los catetos: ');
                      escribir_cadena('K = ');
                      leer(K);
                      _borrar;

                      si(N > 0)

                        _lugar(5,5);
                        escribir_cadena(' Trigangulos encontrados: \n');

                        entonces
                            para i
                            desde 1
                            hasta K
                            hacer

                              para j
                              desde 1
                              hasta K
                              hacer

                                sumC:=i+j;

                                  si(sumC _mod N = 0)
                                    entonces

                                      c1:=i**2;
                                      c2:=j**2;
                                      h:=sqrt(c1+c2);  
                                      
                                      escribir_cadena(' Lado A: ');
                                      escribir(i);
                                      escribir_cadena(' Lado B: ');
                                      escribir(j);
                                      escribir_cadena(' Hipotenusa: ');
                                      escribir(h);
                                      escribir_cadena('\n');

                                    fin_si;

                              fin_para;

                            fin_para;
                        
                      fin_si;
