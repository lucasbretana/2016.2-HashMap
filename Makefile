TARGET = VoltaQuerida
#
CC = gcc
C_FLAGS = -Wall
# Basic directories
LIB = lib
SRC = src
BIN = bin

OBJECT = $(LIB)/*.o

all: $(LIB).o
	$(CC) $(C_FLAGS) $(OBJECT) -o $(TARGET).out

$(LIB).o: main.o
	@echo "Done in libs.o"

main.o: $(SRC)/main.c 
	$(CC) $(C_FLAGS) -c $(SRC)/main.c -o $(LIB)/main.o
