CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
#Version del programa minima requerida
PROJECT(cv_tutorial)
#nombre del proyecto
FIND_PACKAGE(OpenCV 	REQUIRED )
#en el sistema debe estar instalado el paquete CV para que se pueda encontrar
include_directories ("${OpenCV_INCLUDE_DIRS}")
#Required for uco thinstation. May not be required in your own pc
SET(CMAKE_CXX_FLAGS " -D_GLIBCXX_USE_CXX11_ABI=0 -m32")
#Esto se pone para que funcione en esta configuracion particular
LINK_LIBRARIES(${OpenCV_LIBS} )
add_executable(unsharp unsharp.cpp funciones.cpp funciones.hpp)
#Todos los programas que hemos codificado, podemos añadir los que nos salgan de la polla


 
#Para crear los archivos necesarios:
#Crear una carpeta que se llame build
#escribir cmake y la ruta al directorio de configuracion
#escribir make

#para ejecutar los programas:
#entramos en la carpeta build y ejecutamos los programas como se ha echo toda la vida

#Instrucciones practica1
#clacular histograma h
#acumular el histograma
#h/F*C (acumulador normalizado para que esté entre 0 y 1, esto se hace con cada elemento)
# g(x,y)=h''[ImagenEntrada(x,y)]*255
