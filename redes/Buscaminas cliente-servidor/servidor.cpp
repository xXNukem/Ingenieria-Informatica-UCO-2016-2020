#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "funcionesAuxiliares.hpp"
#include "usuario.hpp"
#include "sala.hpp"
using namespace std;

#define MSG_SIZE 250
#define MAX_CLIENTS 50


/*
 * El servidor ofrece el servicio de un chat
 */


int main()
{

	/*----------------------------------------------------
	    Descriptor del socket y buffer de datos
	-----------------------------------------------------*/
	int sd, new_sd;
	struct sockaddr_in sockname, from;
	char buffer[MSG_SIZE];
	socklen_t from_len;
	fd_set readfds, auxfds;
	int salida;
	int arrayClientes[MAX_CLIENTS];
	int numClientes = 0;
	//contadores
	int i, j, k;
	int recibidos;
	char identificador[MSG_SIZE];

	int on, ret;

	std::vector<usuario> vector_usuarios;
	std::vector<sala> vector_salas;


	/* --------------------------------------------------
	    Se abre el socket
	---------------------------------------------------*/
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1)
	{
		perror("No se puede abrir el socket cliente\n");
		exit(1);
	}

	// Activaremos una propiedad del socket que permitir· que otros
	// sockets puedan reutilizar cualquier puerto al que nos enlacemos.
	// Esto permitir· en protocolos como el TCP, poder ejecutar un
	// mismo programa varias veces seguidas y enlazarlo siempre al
	// mismo puerto. De lo contrario habrÌa que esperar a que el puerto
	// quedase disponible (TIME_WAIT en el caso de TCP)
	on = 1;
	ret = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));



	sockname.sin_family = AF_INET;
	sockname.sin_port = htons(2000);
	sockname.sin_addr.s_addr =  INADDR_ANY;

	if (bind(sd, (struct sockaddr *) &sockname, sizeof(sockname)) == -1)
	{
		perror("Error en la operación bind");
		exit(1);
	}


	/*---------------------------------------------------------------------
	    Del las peticiones que vamos a aceptar sólo necesitamos el
	    tamaño de su estructura, el resto de información (familia, puerto,
	    ip), nos la proporcionará el método que recibe las peticiones.
	----------------------------------------------------------------------*/
	from_len = sizeof(from);


	if (listen(sd, 1) == -1)
	{
		perror("Error en la operación de listen");
		exit(1);
	}

	//Inicializar los conjuntos fd_set
	FD_ZERO(&readfds);
	FD_ZERO(&auxfds);
	FD_SET(sd, &readfds);
	FD_SET(0, &readfds);


	//Capturamos la señal SIGINT (Ctrl+c)
	signal(SIGINT, manejador);

	/*-----------------------------------------------------------------------
	    El servidor acepta una petición
	------------------------------------------------------------------------ */
	while (1)
	{

		//Esperamos recibir mensajes de los clientes (nuevas conexiones o mensajes de los clientes ya conectados)

		auxfds = readfds;

		salida = select(FD_SETSIZE, &auxfds, NULL, NULL, NULL);

		if (salida > 0)
		{


			for (i = 0; i < FD_SETSIZE; i++)
			{

				//Buscamos el socket por el que se ha establecido la comunicación
				if (FD_ISSET(i, &auxfds))
				{

					if (i == sd)
					{

						if ((new_sd = accept(sd, (struct sockaddr *)&from, &from_len)) == -1)
						{
							perror("Error aceptando peticiones");
						}
						else
						{
							if (vector_usuarios.size() < MAX_CLIENTS)
							{
								usuario new_user;
								//El usuario nuevo sera insertado al array con id=i y estado = 0
								new_user.setId(new_sd);
								new_user.setEstado(0);
								vector_usuarios.push_back(new_user);
								int pos = buscar_usuario(vector_usuarios, new_sd);
								//cout << "Nuevo cliente con ID --> " << new_sd << " con posicion --> " << pos << " " << vector_usuarios.size() << endl;;
								FD_SET(new_sd, &readfds);
								strcpy(buffer, "+OK. Usuario Conectado\n");
								send(new_sd, buffer, sizeof(buffer), 0);
							}
							else
							{
								bzero(buffer, sizeof(buffer));
								strcpy(buffer, "-ERR. Demasiados clientes conectados\n");
								send(new_sd, buffer, sizeof(buffer), 0);
								close(new_sd);
							}

						}


					}
					else if (i == 0)
					{
						//Se ha introducido información de teclado
						bzero(buffer, sizeof(buffer));
						fgets(buffer, sizeof(buffer), stdin);

						//Controlar si se ha introducido "SALIR", cerrando todos los sockets y finalmente saliendo del servidor. (implementar)
						if (strcmp(buffer, "SALIR\n") == 0)
						{
							for (int j = 0; j < vector_usuarios.size(); ++j)
							{
								send(vector_usuarios[j].getId(), "-ERR. Desconexion servidor\n", sizeof("-ERR. Desconexion servidor\n"), 0);
								close(vector_usuarios[j].getId());
								FD_CLR(vector_usuarios[j].getId(), &readfds);
							}
							close(sd);
							exit(-1);


						}
						//Mensajes que se quieran mandar a los clientes (implementar)

					}
					else
					{
						bzero(buffer, sizeof(buffer));
						int posicion = buscar_usuario(vector_usuarios, i);

						recibidos = recv(i, buffer, sizeof(buffer), 0);
						string buffer_string(buffer);//Conversion a string
						std::vector<string> v = explode(buffer_string, " ");
						if (recibidos > 0)
						{
							//Busca ocurrencia de " "
							if (buffer_string.find(" ") != string::npos)
							{
								string busqueda = buffer_string.substr(0, buffer_string.find(" "));
								//En caso de encontrar la palabra REGISTRO
								if (busqueda.compare("REGISTRO") == 0)
								{
									//Divide la cadena y la almacena en un array
									//Compruebo los parametros pasados
									if (v[1] == "-u" && v[3] == "-p")
									{
										if (existe_usuario(v[2]))
										{
											//existe usuario
											bzero(buffer, sizeof(buffer));
											strcpy(buffer, "-ERR. Usuario ya existente\n");
											send(i, buffer, sizeof(buffer), 0);
										}
										else
										{
											//El usuario no existe, por tanto hay que generarlo
											generar_usuario(v[2], v[4]);
											bzero(buffer, sizeof(buffer));
											strcpy(buffer, "+OK. Creado Usuario\n");
											send(i, buffer, sizeof(buffer), 0);
										}

									}
									else
									{
										//Los parametros recibidos son incorrectos
										bzero(buffer, sizeof(buffer));
										strcpy(buffer, "-ERR. Parametros incorrectos");
										send(i, buffer, sizeof(buffer), 0);
									}
								}
								else
								{
									//Se ha encontrado la cadena USUARIO
									if (busqueda.compare("USUARIO") == 0)
									{
										//Se comprueba que el array tenga el tam correcto para evitar violaciones
										if (v.size() != 2)
										{
											bzero(buffer, sizeof(buffer));
											strcpy(buffer, "-ERR. Comando insertado no valido\n");
											send(i, buffer, sizeof(buffer), 0);
										}
										else
										{
											//saco la posicion del usuario del array, para poder trabajar con el
											int pos = buscar_usuario(vector_usuarios, i);
											//Si estado es = 0, procedo a operar
											if (vector_usuarios[pos].getEstado() == 0)
											{
												//Compruebo si el usuario no existe y mando error
												if (!existe_usuario(v[1]))
												{
													bzero(buffer, sizeof(buffer));
													strcpy(buffer, "-ERR. Usuario no encontrado\n");
													send(i, buffer, sizeof(buffer), 0);
												}
												else
												{
													//Tiene estado valido y el usuario si existe
													if (existe_usuario(v[1]) && buscar_usuario(vector_usuarios, i, v[1]) == 0)
													{
														//Usuario pasado si existe en file
														bzero(buffer, sizeof(buffer));
														//Saco su posicion
														int posicion = buscar_usuario(vector_usuarios, i);
														//Opero con el usuario
														vector_usuarios[posicion].setNombre(v[1]);
														vector_usuarios[posicion].setEstado(1);
														strcpy(buffer, "+OK. Usuario Correcto\n");
														send(i, buffer, sizeof(buffer), 0);
													}
													else
													{
														//En este caso el user ya esta dentro del sistema
														bzero(buffer, sizeof(buffer));
														strcpy(buffer, "-ERR. Usuario ya logeado\n");
														send(i, buffer, sizeof(buffer), 0);
													}
												}

											}
											else
											{
												bzero(buffer, sizeof(buffer));
												strcpy(buffer, "-ERR. Estado no valido.");
												send(i, buffer, sizeof(buffer), 0);
											}
										}


									}
									else
									{
										//Compruebo si ha introducido elcomando password
										if (busqueda.compare("PASSWORD") == 0)
										{
											//Vuelvo a comprobar el tamaño
											if (v.size() != 2)
											{
												bzero(buffer, sizeof(buffer));
												strcpy(buffer, "-ERR. Comando insertado no valido\n");
												send(i, buffer, sizeof(buffer), 0);
											}
											else
											{
												int pos = buscar_usuario(vector_usuarios, i);
												if (vector_usuarios[pos].getEstado() == 1)
												{
													//Implica que ya ha insertado su nombre
													if (comprobar_password(vector_usuarios[posicion].getNombre(), v[1]))
													{
														//Existe el par usuario-contraseña, asignamos los datos a su posicion
														vector_usuarios[posicion].setEstado(2);
														vector_usuarios[posicion].setPassword(v[1]);
														bzero(buffer, sizeof(buffer));
														strcpy(buffer, "+OK. Usuario validado.\n");
														send(i, buffer, sizeof(buffer), 0);
													}
													else
													{
														bzero(buffer, sizeof(buffer));
														strcpy(buffer, "-ERR. Usuario No coincidente.\n");
														send(i, buffer, sizeof(buffer), 0);
													}
												}
												else
												{
													bzero(buffer, sizeof(buffer));
													strcpy(buffer, "-ERR. Estado no valido.");
													send(i, buffer, sizeof(buffer), 0);
												}
											}

										}
										else
										{
											if (busqueda.compare("DESCUBRIR") == 0)
											{
												string opciones = v[1];
												std::vector<string> vopt = explode_user(opciones, ",");
												if (vopt.size() != 2)
												{
													bzero(buffer, sizeof(buffer));
													strcpy(buffer, "-ERR. Comando no valido (Letra,Numero).");
													send(i, buffer, sizeof(buffer), 0);
												}
												else
												{
													int pos = buscar_usuario(vector_usuarios, i);
													//Tiene estado 4, esta en partida
													if (vector_usuarios[pos].getEstado() == 4)
													{
														//Compruebo que vopt[1] sea letra y vopt[2] un numero
														int opt;
														std::istringstream(vopt[1]) >> opt;
														//Entro aqui, por tanto es turno del jugador
														string letra = vopt[0];
														int col = changeToNumber(letra);
														//Columna
														int fila = opt; //Fila
														//Obtengo la posicion de la sala en el array
														int pos_sala = buscar_sala(vector_salas, vector_usuarios[pos].getId());
														if ((vopt[0] <= "J" && vopt[0] >= "A") && (opt > -1 && opt < 10))
														{

															if (vector_salas[pos_sala].comprobarCasillas(fila, col))
															{
																if (vector_usuarios[pos].getTurno())
																{

																	//Saco el objeto pareja para su posterior uso
																	usuario pareja;
																	pareja = getPareja(vector_salas, pos_sala, vector_usuarios[pos].getId());
																	//Controlo los turnos de quien le toca jugar
																	int pos_pareja = buscar_usuario(vector_usuarios, pareja.getId());
																	vector_usuarios[pos].setTurno(false);
																	vector_usuarios[pos_pareja].setTurno(true);
																	//Fin control de turnos
																	bzero(buffer, sizeof(buffer));
																	//En caso de que comprobar derrota sea == 1 (ha elegido una bomba)

																	int retorno = vector_salas[pos_sala].comprobarDerrota(fila, col, vector_usuarios[pos].getBandera());
																	if (retorno == 0)
																	{
																		//Finaliza la partida habiendo perdido el usuario y ganado el adversario
																		vector_usuarios[pos].setEstado(2);
																		vector_usuarios[pos_pareja].setEstado(2);
																		salirSala(vector_usuarios[pos].getId(), vector_usuarios, vector_salas, 0);
																		//Mensaje para ambos jugadores mostrando el tablero
																		string salida = "+OK.Tablero. " + vector_salas[pos_sala].printMatriz(0);
																		strcpy(buffer,  salida.c_str());
																		send(vector_usuarios[pos].getId(), buffer, sizeof(buffer), 0);
																		send(pareja.getId(), buffer, sizeof(buffer), 0);
																		//Mensaje para el jugador
																		salida = "+OK. " + vector_usuarios[posicion].getNombre() + " ha perdido, vuelve a iniciar una partida para jugar.\n";
																		strcpy(buffer, salida.c_str());
																		send(vector_usuarios[pos].getId(), buffer, sizeof(buffer), 0);
																		//Mensaje para el adversario
																		salida = "+OK. " + vector_usuarios[pos_pareja].getNombre() + " ha ganado, vuelve a iniciar una partida para jugar.\n";
																		strcpy(buffer, salida.c_str());
																		send(pareja.getId(), buffer, sizeof(buffer), 0);
																	}
																	else
																	{
																		if (retorno == 1)
																		{
																			//Finaliza la partida y se modifican los datos con su posterior mensaje de ganado/perdido
																			vector_usuarios[pos].setEstado(2);
																			vector_usuarios[pos_pareja].setEstado(2);
																			salirSala(vector_usuarios[pos].getId(), vector_usuarios, vector_salas, 0);
																			//Mensaje mostrando el tablero
																			string salida = "+OK.Tablero. " + vector_salas[pos_sala].printMatriz(0);
																			strcpy(buffer,  salida.c_str());
																			send(vector_usuarios[pos].getId(), buffer, sizeof(buffer), 0);
																			send(pareja.getId(), buffer, sizeof(buffer), 0);
																			//Mensaje para la pareja del jugador
																			salida = "+OK. " + vector_usuarios[pos_pareja].getNombre() + " ha perdido, vuelve a iniciar una partida para jugar.\n";
																			strcpy(buffer, salida.c_str());
																			send(vector_usuarios[pos_pareja].getId(), buffer, sizeof(buffer), 0);
																			//Mensaje para el jugador
																			salida = "+OK. " + vector_usuarios[posicion].getNombre() + " ha ganado, vuelve a iniciar una partida para jugar.\n";
																			strcpy(buffer, salida.c_str());
																			send(vector_usuarios[posicion].getId(), buffer, sizeof(buffer), 0);
																		}
																		else
																		{
																			//Esta opcion implica que continuan jugando y muestra el tablero a ambos jugadores
																			vector_salas[pos_sala].buscarMinas(fila, col);
																			string salida = "+OK.Tablero. " + vector_salas[pos_sala].printMatriz(0);
																			strcpy(buffer,  salida.c_str());
																			send(vector_usuarios[pos].getId(), buffer, sizeof(buffer), 0);
																			send(pareja.getId(), buffer, sizeof(buffer), 0);
																		}
																	}

																}
																else
																{
																	bzero(buffer, sizeof(buffer));
																	strcpy(buffer, "-ERR. No es tu turno.\n");
																	send(vector_usuarios[posicion].getId(), buffer, sizeof(buffer), 0);
																}
															}
															else
															{
																bzero(buffer, sizeof(buffer));
																strcpy(buffer, "-ERR. Casilla ya explorada.\n");
																send(vector_usuarios[posicion].getId(), buffer, sizeof(buffer), 0);
															}

														}
														else
														{
															bzero(buffer, sizeof(buffer));
															strcpy(buffer, "-ERR. Parametros no válidos (Letra Número).\n");
															send(vector_usuarios[posicion].getId(), buffer, sizeof(buffer), 0);
														}


													}
													else
													{
														bzero(buffer, sizeof(buffer));
														strcpy(buffer, "-ERR. Estado no valido.");
														send(vector_usuarios[posicion].getId(), buffer, sizeof(buffer), 0);
													}
												}


											}
											else
											{
												if (buffer_string.find("PONER-BANDERA") != string::npos)
												{
													//Buscamos la posicion dle usuario en el array
													int posicion = buscar_usuario(vector_usuarios, i);
													//Comprobamos el estado del jugador
													if (vector_usuarios[posicion].getEstado() < 4)
													{
														bzero(buffer, sizeof(buffer));
														strcpy(buffer, "-ERR. Estado no valido.");
														send(vector_usuarios[posicion].getId(), buffer, sizeof(buffer), 0);
													}
													else
													{
														string opciones = v[1];
														//Dividimos ela rray por la coma y comprobamos el tamaño para evitar violaciones
														std::vector<string> vopt = explode_user(opciones, ",");
														if (vopt.size() != 2)
														{
															bzero(buffer, sizeof(buffer));
															strcpy(buffer, "-ERR. El comando no es correcto (Letra,Numero).");
															send(vector_usuarios[posicion].getId(), buffer, sizeof(buffer), 0);
														}
														else
														{
															//Pasamos de string a entero
															int opt;
															std::istringstream(vopt[1]) >> opt;
															//Guardamos la letra que ha insertado el jugador y la cambiamos a entero
															string letra = vopt[0];
															int col = changeToNumber(letra);//Columna
															int fila = opt; //Fila
															//Sacamos la posicion del usuario que juega y buscamos la posicion de la sala para su edicion
															int pos = buscar_usuario(vector_usuarios, i);
															int pos_sala = buscar_sala(vector_salas, vector_usuarios[pos].getId());
															//Saco el objeto pareja para su posterior uso
															usuario pareja;
															pareja = getPareja(vector_salas, pos_sala, vector_usuarios[pos].getId());
															//Controlo los turnos de quien le toca jugar
															int pos_pareja = buscar_usuario(vector_usuarios, pareja.getId());
															if ((vopt[0] <= "J" && vopt[0] >= "A") && (opt > -1 && opt < 10))
															{

																if (vector_salas[pos_sala].comprobarCasillas(fila, col))
																{
																	//Si el jugador tiene banderas disponibles, puede jugar
																	if (vector_usuarios[pos].getNumBanderas() - 1 >= 0)
																	{
																		//Ponermos una bandera en el tablero y decrementamos las banderas del jugador
																		vector_salas[pos_sala].ponerBandera(fila, col, vector_usuarios[pos].getBandera());
																		vector_usuarios[pos].setNumBanderas(vector_usuarios[pos].getNumBanderas() - 1);
																		//Comprobamos las banderas para indicar que ha ganado o perdido (cuando ha gastado alguno sus 10 banderas)
																		if (vector_salas[pos_sala].comprobarBanderas(vector_usuarios[pos].getBandera())
																		        && vector_usuarios[pos].getNumBanderas() == 0)
																		{
																			bzero(buffer, sizeof(buffer));
																			vector_usuarios[posicion].setEstado(3);
																			vector_usuarios[pos_pareja].setEstado(3);
																			//Modificamos sus estados y enviamos un msg a ambos indicando que el j1 ha ganado y j2 perdido
																			strcpy(buffer, "+OK. Has ganado, vuelve a iniciar una partida para jugar.\n");
																			send(vector_usuarios[posicion].getId(), buffer, sizeof(buffer), 0);
																			strcpy(buffer, "+OK. Has perdido, vuelve a iniciar una partida para jugar.\n");
																			send(vector_usuarios[pos_pareja].getId(), buffer, sizeof(buffer), 0);

																		}
																		else
																		{
																			//Implica que ha ganado elj2 y perdido el j1
																			if (!vector_salas[pos_sala].comprobarBanderas(vector_usuarios[pos].getBandera())
																			        && vector_usuarios[pos].getNumBanderas() == 0)
																			{
																				bzero(buffer, sizeof(buffer));
																				strcpy(buffer, "+OK. Has perdido, vuelve a iniciar una partida para jugar.\n");
																				send(vector_usuarios[posicion].getId(), buffer, sizeof(buffer), 0);
																				strcpy(buffer, "+OK. Has ganado, vuelve a iniciar una partida para jugar.\n");
																				send(vector_usuarios[pos_pareja].getId(), buffer, sizeof(buffer), 0);
																			}
																			else
																			{
																				//Si opr el contrario no ha gastado todas las banderas, sigue jugando y modificando turnos
																				usuario pareja = getPareja(vector_salas, pos_sala, vector_usuarios[pos].getId());
																				int pos_pareja = buscar_usuario(vector_usuarios, pareja.getId());
																				vector_usuarios[pos].setTurno(false);
																				vector_usuarios[pos_pareja].setTurno(true);
																				//Msg para ambos players
																				string salida = "+OK.Tablero. " + vector_salas[pos_sala].printMatriz(0);
																				strcpy(buffer,  salida.c_str());
																				send(vector_usuarios[pos].getId(), buffer, sizeof(buffer), 0);
																				send(pareja.getId(), buffer, sizeof(buffer), 0);
																			}
																		}

																	}
																	else
																	{
																		bzero(buffer, sizeof(buffer));
																		strcpy(buffer, "-ERR. Limite de banderas alcanzado.\n");
																		send(vector_usuarios[posicion].getId(), buffer, sizeof(buffer), 0);
																	}
																}
																else
																{
																	bzero(buffer, sizeof(buffer));
																	strcpy(buffer, "-ERR. Casilla ya explorada\n");
																	send(vector_usuarios[posicion].getId(), buffer, sizeof(buffer), 0);
																}
															}
															else
															{
																bzero(buffer, sizeof(buffer));
																strcpy(buffer, "-ERR. Parametros no válidos (Letra Número).\n");
																send(vector_usuarios[posicion].getId(), buffer, sizeof(buffer), 0);
															}
														}

													}
												}
												else
												{
													bzero(buffer, sizeof(buffer));
													strcpy(buffer, "-ERR. Comando no valido.");
													send(vector_usuarios[posicion].getId(), buffer, sizeof(buffer), 0);
												}
											}
										}
									}



								}
							}
							else
							{
								if (buffer_string.find("INICIAR-PARTIDA") != string::npos)
								{

									int posicion = buscar_usuario(vector_usuarios, i);
									if (vector_usuarios[posicion].getEstado() < 2)
									{
										bzero(buffer, sizeof(buffer));
										strcpy(buffer, "-ERR. Estado no valido.");
										send(vector_usuarios[posicion].getId(), buffer, sizeof(buffer), 0);
									}
									else
									{
										if (vector_usuarios[posicion].getEstado() == 2)
										{
											//sacamos la posicion del usuario y le cambiamos el estado
											int pos = buscar_usuario(vector_usuarios, i);
											vector_usuarios[pos].setEstado(3);
											//Buscamos una pareja para el usuario, en caso de que la id sea >-1 (hay pareja)
											usuario pareja;
											pareja = buscar_pareja(vector_usuarios, i);

											if (pareja.getId() > -1)
											{
												//Obtenemos la posicion de la pareja en el array de users y modificamos
												int pos_pareja = buscar_usuario(vector_usuarios, pareja.getId());
												vector_usuarios[pos_pareja].setEstado(4);
												vector_usuarios[pos].setEstado(4);
												//Inicializo la sala y le meto la pareja de usuarios
												if (vector_salas.size() < 10)
												{
													sala new_sala;
													//Siempre inicia el jugador 1 el turno
													vector_usuarios[pos].setTurno(false);
													vector_usuarios[pos_pareja].setTurno(true);
													vector_usuarios[pos].setBandera("B");
													vector_usuarios[pos_pareja].setBandera("A");
													//Inserto los jugadores a la sala
													new_sala.setJugador1(vector_usuarios[pos]);
													new_sala.setJugador2(vector_usuarios[pos_pareja]);
													new_sala.setCapacidad(2);
													vector_salas.push_back(new_sala);
													mostrarSalas(vector_salas);
													//Fin de creacion de la sala
													int pos_sala = buscar_sala(vector_salas, vector_usuarios[pos].getId());
													//cout << vector_salas[pos_sala].printMatriz(1) << endl;
													bzero(buffer, sizeof(buffer));
													//Mando mensaje a los clientes
													string salida = "+OK. Jugador: " + vector_usuarios[pos_pareja].getNombre() + " VS Jugador: " +
													                vector_usuarios[pos].getNombre() + "\n";

													strcpy(buffer, salida.c_str());
													send(vector_usuarios[pos].getId(), buffer, sizeof(buffer), 0);
													send(vector_usuarios[pos_pareja].getId(), buffer, sizeof(buffer), 0);
													salida = "+OK.Tablero. " + vector_salas[pos_sala].printMatriz(0);
													//Les mando el tablero de juego
													strcpy(buffer, salida.c_str());
													send(vector_usuarios[pos].getId(), buffer, sizeof(buffer), 0);
													send(vector_usuarios[pos_pareja].getId(), buffer, sizeof(buffer), 0);
												}
												else
												{
													bzero(buffer, sizeof(buffer));
													strcpy(buffer, "-ERR. Todas las salas de juego estan llenas.\n");
													send(i, buffer, sizeof(buffer), 0);
												}
											}
											else
											{
												bzero(buffer, sizeof(buffer));
												strcpy(buffer, "+OK. Se ha puesto en cola hasta encontrar un rival disponible.\n");
												send(i, buffer, sizeof(buffer), 0);
											}
										}
									}
								}
								else
								{
									if (buffer_string.find("SALIR") != string::npos)
									{
										salirSala(i, vector_usuarios, vector_salas, 1);
										salirCliente(i, &readfds, vector_usuarios, vector_salas);
									}
									else
									{
										bzero(buffer, sizeof(buffer));
										strcpy(buffer, "-ERR. Comando no valido.");
										send(vector_usuarios[posicion].getId(), buffer, sizeof(buffer), 0);
									}
								}
							}


						}
						//Si el cliente introdujo ctrl+c
						if (recibidos == 0)
						{
							printf("El cliente con id --> %d, ha salido.\n", i);
							//Eliminar ese socket
							salirSala(i, vector_usuarios, vector_salas, 1);
							salirCliente(i, &readfds, vector_usuarios, vector_salas);
						}
					}
				}
			}
		}
	}

	close(sd);
	return 0;

}
