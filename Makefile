CC = clang

CFLAGS = -Werror=implicit-function-declaration -Wno-int-conversion -Wno-format

LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm


SRC_DIR = src
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.c)

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJ_NAME = game

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

all: $(OBJ_DIR) $(OBJ_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(OBJ_NAME)

clean:
	rm -rf $(OBJ_DIR) $(OBJ_NAME)

rebuild: clean all
