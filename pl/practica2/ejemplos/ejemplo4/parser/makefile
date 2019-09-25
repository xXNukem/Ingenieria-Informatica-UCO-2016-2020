# MAKEFILE for parser

NAME=interpreter

# Compiler
CPP = g++

# Directives for the compiler
# -c: the output is an object file, the linking stage is not done.
# -g: debug
# -Wall: all warnings
# -ansi: standard language
# -02: optimization level
CFLAGS = -c -g  -Wall -ansi -O2

# The fast lexical analyser generator
LEX = flex

#GNU Project parser generator (yacc replacement)
YACC= bison 

# Options
# -d: the file y.tab.h is generated
# -y: yacc compatibility --> y.tab.c y.tab.h (OPTIONAL)
# -t: debug
# -g: the file y.dot is generated; 
#     this file can be seen on the screen using 
#       dot -Tx11 y.dot 
#       Alternatives 
#	 	dot -TXXX NAME.dot -o NAME.XXX
#	    where XXX can be: gif, pdf, png, ps, svg
# -v  the file NAME.output is generated (OPTIONAL)
YFLAGS = -d -t -g

# Objects
OBJECTS= $(NAME).tab.o lex.yy.o 

# Includes
INCLUDES = ../error/error.hpp ../includes/macros.hpp

# Predefined macros 
#
# $@: name of the target
# $^: all the dependencies
# $<: first dependency
#
#######################################################

# Main rule

all: $(OBJECTS)


# Subrules 

# Lexical analyzer
# -Wno-unused-function, -Wno-sign-compare: these error messages are not displayed
lex.yy.o:  lex.yy.c $(NAME).tab.h $(INCLUDES)
	@echo "Compiling: " $<
	@$(CPP) $(CFLAGS)  -Wno-unused-function  -Wno-sign-compare $<
	@echo

lex.yy.c: $(NAME).l $(NAME).tab.h $(INCLUDES)
	@echo "Generating:" $@
	@$(LEX) $<
	@echo

# Parser
$(NAME).tab.o: $(NAME).tab.c  $(NAME).tab.h  $(INCLUDES)
	@echo "Compiling: " $<
	@$(CPP) $(CFLAGS) $<
	@echo

$(NAME).tab.c $(NAME).tab.h: $(NAME).y $(INCLUDES)
	@echo "Generating: " $(NAME).tab.c $(NAME).tab.h
	@$(YACC) $(YFLAGS) $< 
	@echo


#######################################################
# Generate the output file to show conflicts, if they exist
$(NAME).output: $(NAME).y $(INCLUDES)
	@echo "Generating: " $@
	@$(YACC) -v $< 
	@echo


#######################################################
# Auxiliary files are deleted
clean: 
	@echo
	@echo "Deleting in subdirectory parser"
	@rm -f $(OBJECTS) $(NAME).tab.[ch] lex.yy.c $(NAME).dot $(NAME).output *~ 
	@echo



