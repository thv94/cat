CC = gcc
CSTD = c90
OPT_LEVEL = -O2
CPPCHECK = cppcheck
CPPCHECKFLAGS = -std=c89 --check-level=exhaustive --error-exitcode=1

SRC_DIR = src
INC_DIR = include
OBJ_DIR = .o

CFLAGS = -Wall -Wextra -Werror -Wpedantic -I$(INC_DIR) -std=$(CSTD) $(OPT_LEVEL) -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wcast-qual -Wswitch-default -Wswitch-enum -Wunreachable-code -Wfloat-equal -Wconversion -Wdouble-promotion -Wmissing-prototypes -Wundef -Wunused-macros -Wwrite-strings

TARGET = mycat

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: $(TARGET) cppcheck.out.xml

cppcheck.out.xml: $(SRC_DIR)
	$(CPPCHECK) $(CHECKFLAGS) $^ --xml >$@

$(TARGET): $(OBJ_FILES)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_FILES) $(TARGET)
