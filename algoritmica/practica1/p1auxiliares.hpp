#ifndef _P1AUXILIARES_HPP_
#define _P1AUXILIARES_HPP_
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string.h>
#include <vector>
#include <unistd.h>
#include "macros.hpp"
#include "medicionMetodo.hpp"


int menu();

void grabarFichero(std::vector<datos> const &t);

#endif