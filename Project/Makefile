#
# Les variables d'environnement libG3X, incG3X
# sont definies dans le fichier ~/.bashrc par le script ../install.sh
#
#compilateur
CC = g++

#compil en mode 'debug' ou optmisée (-O2)
DBG = no

ifeq ($(DBG),yes) #en mode debug
  CFLAGS = -g -Wpointer-arith -Wall -ansi
else               #en mode normal
  CFLAGS = -O2 -ansi
endif

# assemblage des infos de lib. et inc.
lib =   $(libG3X)
# fichiers *.c locaux
src = sources/
# fichiers *.h locaux et lib.
inc = -I./include $(incG3X) 

all : main_bastien

# règle générique de création de xxx.o à partir de src/xxx.c
%.o : $(src)%.cpp
	@echo "module $@"
	$(CC) $(CFLAGS) $(inc) -c $< -o $@
	@echo "------------------------"

# règle générique de création de l'executable xxx à partir de src/xxx.c (1 seul module)
% : %.o
	@echo "assemblage [$^]->$@"
	$(CC) $^ $(lib) -o $@
	@echo "------------------------"
	
.PHONY : clean cleanall ?

# informations sur les paramètres de compilation       
? :
	@echo "---------infos de compilation----------"
	@echo "  processeur     : $(PROCBIT)"
	@echo "  compilateur    : $(CC)"
	@echo "  options        : $(CFLAGS)"
	@echo "  lib g3x/OpenGl : $(libG3X)$(COMP)"
	@echo "  headers        : $(incG3X)"
ifeq ($(DBG),yes)
	@echo "  traceur ACTIF  : $(DBG_LIB)"
	@echo "                   $(DBG_FLAG)"
endif

clean : 
	@rm -f *.o
cleanall :
	@rm -f *.o 3Ddemo demo_scene
	
