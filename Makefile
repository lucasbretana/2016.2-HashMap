TARGET = DilMae
#
CC = gcc
CC_FLAG = -std=c11 -Wall $(DEBUG)
RM = rm
RM_FLAG = -rf
# Basic directories
LIB = lib
SRC = src
BIN = bin

# Objects
OBJ = main hashmap usefull

#===================================================================
all: $(addsuffix .o, $(OBJ) )
	$(CC) $(CC_FLAG) $(addprefix $(BIN)/, $(addsuffix .o, $(OBJ) ) ) -o $(TARGET).out -lm

main.o: $(SRC)/main.c
	$(CC) $(CC_FLAG) -c $(SRC)/main.c -o $(BIN)/main.o

hashmap.o: $(SRC)/hashmap.c $(SRC)/hashmap.h 
	$(CC) $(CC_FLAG) -c $(SRC)/hashmap.c -o $(BIN)/hashmap.o

usefull.o: $(SRC)/usefull.c $(SRC)/usefull.h
	$(CC) $(CC_FLAG) -c $(SRC)/usefull.c -o $(BIN)/usefull.o

clean:
	$(RM) $(RM_FLAG) $(BIN)/*.o
	$(RM) $(RM_FLAG) $(TARGET).out
