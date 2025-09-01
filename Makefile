# === Makefile for the compiler project (auto-discovers sources) ===
# Tools
CC ?= gcc
LEX ?= flex
YACC ?= bison

# Paths
BUILD_DIR := ./build
OUTPUT_DIR := ./output
LOG_DIR := $(OUTPUT_DIR)/logs
SRC_DIR := ./src
TEST_DIR := ./tests
TARGET := compiler

# Flags
CFLAGS ?= -O2 -Wall -Wextra -I. -I./include -I$(BUILD_DIR)
LDFLAGS ?=
LIBS ?= -lfl

# Ensure directories exist
$(shell mkdir -p $(BUILD_DIR))
$(shell mkdir -p $(LOG_DIR))

# Auto-discovered C sources in SRC_DIR
C_SRCS := $(wildcard $(SRC_DIR)/*.c)
C_OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(C_SRCS))

# Generated sources/headers/objects (Flex/Bison)
GEN_C := $(BUILD_DIR)/lex.yy.c $(BUILD_DIR)/parser.tab.c
GEN_H := $(BUILD_DIR)/parser.tab.h $(BUILD_DIR)/parser.h
GEN_OBJS := $(BUILD_DIR)/lex.yy.o $(BUILD_DIR)/parser.tab.o

# Default target
.PHONY: all
all: $(TARGET)

# Link all objects into the final binary
$(TARGET): $(GEN_OBJS) $(C_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

# Compile normal C sources
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(wildcard include/*.h) $(GEN_H)
	$(CC) $(CFLAGS) -c $< -o $@

# -------- Bison (parser) --------
# Generate parser code and header
$(BUILD_DIR)/parser.tab.c $(BUILD_DIR)/parser.tab.h: $(SRC_DIR)/parser.y
	$(YACC) -d -v -t -Wcounterexamples -o $(BUILD_DIR)/parser.tab.c $<

# Optional compatibility: copy generated header to parser.h
# (useful if your code includes "parser.h" instead of "parser.tab.h")
$(BUILD_DIR)/parser.h: $(BUILD_DIR)/parser.tab.h
	cp $< $@

$(BUILD_DIR)/parser.tab.o: $(BUILD_DIR)/parser.tab.c
	$(CC) $(CFLAGS) -c $< -o $@

# -------- Flex (lexer) --------
$(BUILD_DIR)/lex.yy.c: $(SRC_DIR)/lexer.l $(BUILD_DIR)/parser.tab.h
	$(LEX) -o $@ $<

$(BUILD_DIR)/lex.yy.o: $(BUILD_DIR)/lex.yy.c
	$(CC) $(CFLAGS) -c $< -o $@

# -------- Convenience targets --------
.PHONY: run test test_all clean clean_output distclean dirs

dirs:
	@mkdir -p $(BUILD_DIR) $(LOG_DIR)

# Run the compiler on a single input file and save output to logs
run: $(TARGET) | dirs
	@if [ -z "$(file)" ]; then \
		echo "Usage: make run file=<path/to/input>"; exit 1; \
	fi
	@log_file_name=$$(basename "$(file)").log; \
	log_file_path=$(LOG_DIR)/$$log_file_name; \
	echo "Running $(TARGET) on $(file) -> $$log_file_path"; \
	./$(TARGET) "$(file)" > "$$log_file_path" || true; \
	echo "Done."

# Alias for backward-compatibility with your example
test: run

# Run the compiler for every file in a directory
test_all: $(TARGET) | dirs
	@if [ -z "$(dir)" ]; then \
		echo "Usage: make test_all dir=<path/to/dir>"; exit 1; \
	fi
	@if [ ! -d "$(dir)" ]; then \
		echo "Error: directory '$(dir)' not found"; exit 1; \
	fi
	@for test_file in $(wildcard $(dir)/*); do \
		if [ -f "$$test_file" ]; then \
			log_file_name=$$(basename "$$test_file").log; \
			log_file_path=$(LOG_DIR)/$$log_file_name; \
			echo "Processing $$test_file -> $$log_file_path"; \
			./$(TARGET) "$$test_file" > "$$log_file_path" || true; \
		fi; \
	done
	@echo "All tests finished."

# -------- Cleaning --------
clean:
	rm -rf $(BUILD_DIR)/*
	rm -f $(TARGET)

clean_output:
	rm -f $(LOG_DIR)/*
	rm -f $(OUTPUT_DIR)/*.txt

distclean: clean clean_output
	rm -rf $(BUILD_DIR) $(OUTPUT_DIR)
