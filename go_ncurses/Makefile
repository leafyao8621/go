CC = gcc
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
LIB =  ../go/go.a
BIN = go

%.o: %.c
	$(CC) -g -c $< -o $@

$(BIN): $(OBJ)
	$(CC) $(OBJ) $(LIB) -o $(BIN) -lncurses

.PHONY: clean
clean: $(BIN)
	@rm $(OBJ) $(BIN)
