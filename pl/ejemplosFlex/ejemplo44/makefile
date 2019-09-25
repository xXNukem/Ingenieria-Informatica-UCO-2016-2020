# Si se desea generar ejemplo44.exe entonces teclear 
#  make
#
# Si se desea generar otro "ejemplo" entonces teclear 
#            make NAME=ejemplo

NAME = ejemplo44

# Directives for the compiler
# -c: the output is an object file, the linking stage is not done.
# -g: debug
# -Wall: all warnings
# -ansi: standard language
# -02: optimization level
# -Wno-unused-function  -Wno-sign-compare -Wno-implicit-function-declaration: disabled error messages
CFLAGS = -c -g -Wall -ansi -O2 -Wno-unused-function  -Wno-sign-compare -Wno-implicit-function-declaration

# Directive for flex's library
LFLAGS = -lfl 

# Predefined macros 
#
# $@: name of the target
# $^: all the dependencies
# $<: first dependency
#
################################################################

##
# MODIFICADO
$(NAME).exe: $(NAME).o p44.o
	@echo "Generating" $@
	@gcc $^ $(LFLAGS) -o $@

# NUEVO
p44.o: p44.c
	@echo "Compiling" $< " and generating" $@
	@gcc $(CFLAGS) $< -o $@ 


$(NAME).o: lex.yy.c
	@echo "Compiling" $< " and generating" $@
	@gcc $(CFLAGS) $< $(LFLAGS) -o $@ 

lex.yy.c: $(NAME).l
	@echo "Generating" $@
	@flex $<

clean:
	@echo Deleting auxiliary files
	@rm -f lex.yy.c *.o  
