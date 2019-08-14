CC = gcc
AR = ar
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
LIB = ../go/go.a
BIN = test

%.o: %.c
	$(CC) -g -c $< -o $@

$(BIN): $(OBJ)
	$(CC) $(OBJ) $(LIB) -o $(BIN)

all: clean
clean: $(LIB)
	@rm $(OBJ) $(BIN)
