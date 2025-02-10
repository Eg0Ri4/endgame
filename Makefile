CC = clang
CFLAGS = -Wall -Wextra -Iinc
LDFLAGS = -lSDL2

SRC = src/main.c
OBJ = $(SRC:.c=.o)
EXEC = endgame

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
