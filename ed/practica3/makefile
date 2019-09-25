NAME=principalMonticulo

#
OBJECTS = $(NAME).o funcionesAuxiliares.o MonticuloMediciones.o Medicion.o Fecha.o

#
CPPFLAGS = -c -g -Wall -ansi -O2

INCLUDES = funcionesAuxiliares.hpp MonticuloMediciones.hpp Medicion.hpp Fecha.hpp macros.hpp

# Macros predefinidas
#
# $@: nombre del objetivo
# $^: todas las dependencias
# $<: primera dependencia
#

objetivo: $(NAME).exe

#Opciones para NO depurar los asertos
ndebug: CPPFLAGS += -DNDEBUG 
ndebug: objetivo

# Primer objetivo 
$(NAME).exe: $(OBJECTS)
			@echo "Generando " $@
			@g++ $^ -o $@
#
$(NAME).o: $(NAME).cpp $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

#
funcionesAuxiliares.o: funcionesAuxiliares.cpp $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

#
Fecha.o: Fecha.cpp Fecha.hpp 
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

#
Medicion.o: Medicion.cpp Medicion.hpp  Fecha.hpp 
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<


#
MonticuloMediciones.o: MonticuloMediciones.cpp MonticuloMediciones.hpp \
						MonticuloMedicionesInterfaz.hpp Medicion.hpp \
						Medicion.hpp Fecha.hpp
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<





# Generación de la documentación
doc: Doxyfile 
	@echo "Generando la documentación con doxygen"
	@doxygen
  
# Borrado
.PHONY: clean  
clean:
	@echo "Borrando los ficheros superfluos"
	@rm -f $(OBJECTS) *~ 

