CFLAGS := -std=c11 -Wall -Wextra -Werror -pedantic -g -Iinc/raylib/include -Ilib/include
LDFLAGS := -Linc/raylib/lib -Llib -Wl,-rpath,inc/raylib/lib -Wl,-rpath,lib 
LIBS := -lraylib -lm -lpthread -ldl -lrt -lGL -lGLU
SRC := src/*.c
NAME := endgame

all: $(NAME)

$(NAME):
	clang $(CFLAGS) $(SRC) -o $(NAME) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(NAME)

re: clean all
