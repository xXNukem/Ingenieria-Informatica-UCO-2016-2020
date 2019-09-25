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
#include <time.h>
#include <algorithm>
#include <arpa/inet.h>
#include <boost/algorithm/string.hpp>
using namespace std;

int main(int argc, char const *argv[])
{
	string _mPublica[10][10];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (j == 9) {
				_mPublica[i][j] = "a";
			} else {

				_mPublica[i][j] = "- ";
			}

		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << _mPublica[i][j];

		}
		cout << endl;
	}
	cout << " --------------------------------" << endl;
	string cadena, aux;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			aux = _mPublica[i][j];
			if (j == 9) {
				boost::replace_all(aux, "a", "-;");

			} else {
				replace(aux.begin(), aux.end(), ' ', ',');
			}
			_mPublica[i][j] = aux;
			cadena += _mPublica[i][j];
		}
	}

	cout << "La cadena es --> " << cadena << endl;
}