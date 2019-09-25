CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
#Version del programa minima requerida
PROJECT(practica1)
#nombre del proyecto
#Required for uco thinstation. May not be required in your own pc
SET(CMAKE_CXX_FLAGS " -D_GLIBCXX_USE_CXX11_ABI=0 -m32")
SET(CMAKE_CXX_STANDARD 11)
add_executable(programa auxiliares.cpp entero.cpp funcionesbajonivel.cpp main.cpp)
