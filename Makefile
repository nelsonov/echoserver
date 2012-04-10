DIR_INCLUDE = ./
DIR_SRC = ./
DIR_BIN = ./
DIR_LIB = ./

AR = ar
AR_FLAGS = rs

CC = g++
CC_FLAGS = -g -Wall -I $(DIR_INCLUDE) -L $(DIR_LIB) 

OBJ_LIB = ConnectHandler.o 
OBJ_LIB_SRC = $(DIR_SRC)/ConnectHandler.cpp 

PROGRAM = $(DIR_BIN)/server
OBJ_PROG = Main.o
OBJ_PROG_SRC = $(DIR_SRC)/Main.cpp

LIB_LINK = -lpthread


$(PROGRAM):$(OBJ_PROG) $(OBJ_LIB)
	$(CC) $(CC_FLAGS) $(OBJ_PROG) $(OBJ_LIB) $(LIB_LINK) -o $(PROGRAM)

$(OBJ_PROG):$(OBJ_PROG_SRC) 
	$(CC) -c $(OBJ_PROG_SRC) $(CC_FLAGS) 

$(OBJ_LIB):$(OBJ_LIB_SRC)  
	$(CC) -c $(OBJ_LIB_SRC) $(CC_FLAGS)

clean:
	rm -f *.o $(PROGRAM)
