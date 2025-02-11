CFLAGS := -std=c11 -Wall -Wextra -Werror -pedantic -g -Iinc/raylib/include
LDFLAGS := -Linc/raylib/lib -Wl,-rpath,inc/raylib/lib
LIBS := -lraylib -lm -lpthread -ldl -lrt -lGLEW -lglfw -lGLU -lGL
SRC := src/*.c
NAME := endgame

all: $(NAME)

$(NAME):
	clang $(CFLAGS) $(SRC) -o $(NAME) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(NAME)

re: clean all

