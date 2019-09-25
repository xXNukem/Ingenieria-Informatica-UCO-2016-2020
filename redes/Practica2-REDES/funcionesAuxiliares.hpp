#ifndef _FUNCIONESAUXILIARES_HPP_
#define _FUNCIONESAUXILIARES_HPP_
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
#include "usuario.hpp"
#include "sala.hpp"
using namespace std;

void manejador(int signum);
void salirCliente(int socket, fd_set * readfds, std::vector<usuario> &v, std::vector<sala> &vsala);
void salirSala(int socket, std::vector<usuario> &v, std::vector<sala> &vsala, int opt);
vector<string> explode(const string& str, const string& delim);
vector<string> explode_user(const string& str, const string& delim);
bool existe_usuario(const string &str);
void generar_usuario(const string &str, const string &pass);
bool comprobar_password(string name, string contrasena);
int buscar_usuario(std::vector<usuario> v, int id, string str = "");
usuario buscar_usuario_objeto(std::vector<usuario> v, int id);
usuario buscar_pareja(std::vector<usuario> v, int id);
int buscar_sala(std::vector<sala> vsalas, int id);
usuario getPareja(std::vector<sala> vsala, int posicion, int id);
int changeToNumber(string value);
void mostrarSalas(std::vector<sala> vsala);
#endif
