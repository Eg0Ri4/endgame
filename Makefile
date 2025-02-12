CFLAGS := -std=c11 -Wall -Wextra -Werror -pedantic -g -Iresources/libs/raylib/include -Ilib/include -Iinc
LDFLAGS := -Lresources/libs/raylib/lib -Llib -Wl,-rpath,resources/libs/raylib/lib -Wl,-rpath,lib
LIBS := -lraylib -lm -lpthread -ldl -lrt -lGL -lGLU
SRC := src/*.c
NAME := endgame

all: $(NAME)

$(NAME): force
	clang $(CFLAGS) $(SRC) -o $(NAME) $(LDFLAGS) $(LIBS)

force: ;

clean:
	rm -f $(NAME)

re: clean all
