TARGET = DilMae
#
CC = gcc
CC_FLAG = -std=c11 -Wall
RM = rm
RM_FLAG = -rf
# Basic directories
LIB = lib
SRC = src
BIN = bin

# Objects
OBJ = main hashmap usefull linkedList hashmapJon

#===================================================================
all: $(addsuffix .o, $(OBJ) )
	$(CC) $(CC_FLAG) $(addprefix $(BIN)/, $(addsuffix .o, $(OBJ) ) ) -o $(TARGET).out -lm

main.o: $(SRC)/main.c usefull.o hashmap.o hashmapJon.o
	$(CC) $(CC_FLAG) -c $(SRC)/main.c -o $(BIN)/main.o

hashmap.o: $(SRC)/hashmap.c $(SRC)/hashmap.h usefull.o linkedList.o
	$(CC) $(CC_FLAG) -c $(SRC)/hashmap.c -o $(BIN)/hashmap.o

hashmapJon.o: $(SRC)/hashmapJon.c $(SRC)/hashmapJon.h hashmap.o usefull.o linkedList.o
	$(CC) $(CC_FLAG) -c $(SRC)/hashmapJon.c -o $(BIN)/hashmapJon.o

usefull.o: $(SRC)/usefull.c $(SRC)/usefull.h
	$(CC) $(CC_FLAG) -c $(SRC)/usefull.c -o $(BIN)/usefull.o

linkedList.o: $(SRC)/linkedList.c $(SRC)/linkedList.h
	$(CC) $(CC_FLAG) -c $(SRC)/linkedList.c -o $(BIN)/linkedList.o

clean:
	$(RM) $(RM_FLAG) $(BIN)/*.o
	$(RM) $(RM_FLAG) $(TARGET).out
