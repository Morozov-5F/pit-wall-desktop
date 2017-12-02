CC = gcc
LD = gcc

SRC = main.c f1_types.c
OBJ = $(patsubst %.c, %.o, $(SRC))

CFLAGS  = -ansi -Wall -Wpedantic
LDFLAGS =

DEFINES = _GNU_SOURCE

L_FILES = uv

COMPILE_C   = $(CC) $(CFLAGS) $(addprefix -D, $(DEFINES)) -MD -c $< -o $@
LINK_BINARY = $(LD) $(LDFLAGS) $^ $(addprefix -l, $(L_FILES)) -o $@

TARGET = socket_test

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJ)
	@echo "Linking object files: " $<
	$(LINK_BINARY)

%.o: %.c
	@echo "Compiling C file: " $<
	$(COMPILE_C)

clean:
	rm -rf $(patsubst %.c, %.o, $(SRC))
	rm -rf $(patsubst %.c, %.d, $(SRC))
	rm -rf $(addsuffix .dbg,    $(TARGET))
	rm -rf $(TARGET)

info:
	@echo "Source files:             $(SRC)"
	@echo "Object files:             $(OBJ)"
