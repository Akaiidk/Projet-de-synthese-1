INCLUDE_DIR = include
OBJ_DIR = obj
SRC_DIR = src
JAVA_DIR = java
SCRIPT_DIR = script

CC = gcc
CFLAGS = -Wall -Wextra -fPIC -c -I$(INCLUDE_DIR)

PROG = intersections
TEST = runtest
# Extension macOS pour les libs dynamiques
LIB = $(JAVA_DIR)/libintersections.dylib
EXPE = $(SCRIPT_DIR)/expe

# Détection automatique du JAVA_HOME sur macOS
JAVA_HOME := $(shell /usr/libexec/java_home)
JAVA_INCLUDES = -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/darwin

_DEPS = util.h rational.h list.h  geometry.h algo.h tree.h
DEPS = $(patsubst %,$(INCLUDE_DIR)/%,$(_DEPS))

_OBJ= util.o rational.o list.o geometry.o algo.o tree.o
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

in = ./data/input
out = ./data/output
algo = 1

.PHONY: all run test jni expe clean delete deletetest deletelib deleteexpe cleanall memorycheck testmemorycheck

all : $(PROG) $(TEST) $(LIB) $(EXPE)

run : $(PROG)
	./$(PROG) $(in) $(out) $(algo)

test : $(TEST)
	./$(TEST)

jni : $(LIB)

expe : $(EXPE)

clean :
	rm -rf $(OBJ_DIR)

delete :
	rm -f $(PROG)

deletetest :
	rm -f $(TEST)

deletelib :
	rm -f $(LIB)

deleteexpe :
	rm -f $(EXPE)

cleanall : clean delete deletetest deletelib deleteexpe

# Utilisation de l'outil natif macOS 'leaks'
memorycheck : $(PROG)
	leaks --atExit -- ./$(PROG) $(in) $(out) $(algo)

# Règle générique avec création automatique du dossier obj
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(DEPS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(OBJ_DIR)/application_Intersections.o : $(SRC_DIR)/application_Intersections.c $(DEPS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(JAVA_INCLUDES) -o $@ $<

$(PROG) : $(OBJ) $(OBJ_DIR)/main.o
	$(CC) -o $@ $^ -lm

$(TEST) : $(OBJ) $(OBJ_DIR)/test.o
	$(CC) -o $@ $^ -lm

$(EXPE) : $(OBJ) $(OBJ_DIR)/expe.o
	$(CC) -o $@ $^ -lm

$(LIB) : $(OBJ) $(OBJ_DIR)/application_Intersections.o
	$(CC) -dynamiclib -o $@ $^ -lm