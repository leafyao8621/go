CC = gcc
AR = ar
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
LIB = go.a

%.o: %.c
	$(CC) -g -c $< -o $@

$(LIB): $(OBJ)
	@cp src/go.h .
	$(AR) rcs $@ $^

all: clean
clean: $(LIB)
	@rm $(OBJ) $(LIB) go.h
