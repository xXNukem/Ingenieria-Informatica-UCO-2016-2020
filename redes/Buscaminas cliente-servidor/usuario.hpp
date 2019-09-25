#ifndef _CLIENTE_HPP_
#define _CLIENTE_HPP_
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
using namespace std;

class usuario
{
private:
	int _id;
	string _nombre;
	string _password;
	int _estado;
	bool _turno;
	string _bandera;
	int _numBanderas;

public:
	usuario()
	{
		_numBanderas = 10;
	};

	inline void setId(int id) {_id = id;}
	inline void setNombre(string name) {_nombre = name;}
	inline void setPassword(string password) {_password = password;}
	inline void setEstado(int status) {_estado = status;}
	inline void setTurno(bool turno) {_turno = turno;}
	inline void setBandera(string x) {_bandera = x;}
	inline void setNumBanderas(int x) {_numBanderas = x;}


	inline int getId()const {return _id;}
	inline string getNombre()const {return _nombre;}
	inline string getPassword()const {return _password;}
	inline int getEstado()const {return _estado;}
	inline bool getTurno()const {return _turno;}
	inline string getBandera()const {return _bandera;}
	inline int getNumBanderas()const {return _numBanderas;}


};




#endif