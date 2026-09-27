CC := gcc
WIN_CC := x86_64-w64-mingw32-gcc

CFLAGS := -Wall -Wextra -std=c11 $(shell pkg-config --cflags raylib)
LDFLAGS := $(shell pkg-config --libs raylib) -lm

TARGET := tessel
WIN_TARGET := tessel.exe

SRC := $(wildcard src/*.c)
OBJ := $(SRC:.c=.o)

.PHONY: all clean run windows

# Default: Linux
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

# Optional: Windows
windows:
	$(WIN_CC) -Wall -Wextra -std=c11 $(SRC) \
		-Ivendor/raylib/include \
		-Lvendor/raylib/lib \
		-o $(WIN_TARGET) \
		-lraylib -lopengl32 -lgdi32 -lwinmm

clean:
	rm -f $(OBJ) $(TARGET) $(WIN_TARGET)