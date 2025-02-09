CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -Iinc
FILE_NAME=way_home

all: $(FILE_NAME)

$(FILE_NAME):
	clang  $(CFLAGS) src/*.c -o $(FILE_NAME)

clean:
	rm -f  $(FILE_NAME)

re: clean all
