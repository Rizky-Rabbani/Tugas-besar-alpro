BUILD_DIR := bin
TARGET := $(BUILD_DIR)/alprog1
CC ?= gcc
CFLAGS ?= -std=c99 -Wall -Wextra -Wpedantic -Iheader
SRC := $(shell find src -name "*.c")
CONFIG_FOLDER ?= config/

.PHONY: all build run clean

all: build

build:
	@echo "build dengan gcc..."
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
	@echo "build selesai: $(TARGET)"

run: bin
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)