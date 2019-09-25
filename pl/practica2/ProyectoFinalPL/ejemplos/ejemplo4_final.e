_borrar;
_lugar(5,5);
                        escribir_cadena('Introduce un número y sabremos si es perfecto o no: ');
                        leer(V);
                        sumaDiv:=0;
                        _borrar;

                          para i
                          desde 1
                          hasta V-1
				paso 1
                          hacer

				mul:= i _mod V;
                            si(mul = 0)
                              entonces

                                escribir(sumaDiv);
                                sumaDiv:=sumaDiv+i;

                            fin_si;

                          fin_para;

                            si(sumaDiv = V)
                              entonces
				escribir(sumaDiv);
				
                                escribir_cadena(' El número es perfecto');
                              
                             fin_si;
                         
                     

