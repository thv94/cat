CC = gcc
CSTD = c90
OPT_LEVEL = -O2

SRC_DIR = src
INC_DIR = include
OBJ_DIR = .o

CFLAGS = -Wall -Wextra -Werror -Wpedantic -I$(INC_DIR) -std=$(CSTD) $(OPT_LEVEL) -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wcast-qual -Wswitch-default -Wswitch-enum -Wunreachable-code -Wfloat-equal -Wconversion -Wdouble-promotion -Wmissing-prototypes -Wundef -Wunused-macros -Wwrite-strings

TARGET = mycat

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: $(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJ_FILES)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_FILES) $(TARGET)
