CC     = clang
CFLAGS = -Wall -Wextra -std=c11 -g

SRC    = array.c
OBJ    = $(SRC:.c=.o)
LIB    = libarray.a

TEST_SRC = tests.c
TEST_BIN = tests

.PHONY: all test clean

all: $(LIB)

$(LIB): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(TEST_SRC) $(LIB)
	$(CC) $(CFLAGS) $< -L. -larray -lm -o $@

clean:
	rm -f $(OBJ) $(LIB) $(TEST_BIN)
