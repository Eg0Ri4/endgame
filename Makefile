CFLAGS :=  -Ilibs/include
LDFLAGS := -Llibs/lib -Wl,-rpath,libs/lib
LIBS := -lGLEW -lglfw -lGLU -lGL
SRC := src/*.c
NAME := endgame

all: $(NAME)

$(NAME):
	clang $(CFLAGS) $(SRC) -o $(NAME) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(NAME)

re: clean all
