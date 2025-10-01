# Project root
CXX = g++
DEBUG ?= 0
ifeq ($(DEBUG),1)
    CXXFLAGS += -g -O0 -DDEBUG
else
    CXXFLAGS += -O2
endif
CXXFLAGS += -std=c++17 -Wall -Wextra $(shell find src -type d | sed 's/^/-I/') -I./tests

SRC_DIR = src
OBJ_DIR = build
RESULT_DIR = result
BIN_DIR = $(RESULT_DIR)/bin
TESTS_DIR = tests
RESULT_TESTS_DIR = $(RESULT_DIR)/tests
SRC_TESTS_DIR = $(SRC_DIR)/tests

# Find all .cpp files in src (excluding tests)
SRCS := $(shell find $(SRC_DIR) -name '*.cpp' ! -path '$(SRC_TESTS_DIR)/*')
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Find all test .cpp files in tests
ifeq ($(wildcard $(TESTS_DIR)),)
TEST_SRCS :=
else
TEST_SRCS := $(shell find $(TESTS_DIR) -name '*.cpp')
endif
TEST_BINS := $(patsubst $(TESTS_DIR)/%.cpp,$(RESULT_TESTS_DIR)/%,$(TEST_SRCS))

# Default target
all: $(TEST_BINS)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build test binaries
$(RESULT_TESTS_DIR)/%: $(TESTS_DIR)/%.cpp $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Run all test binaries
run-tests: $(TEST_BINS)
	@for test in $(TEST_BINS); do \
		echo "Running $$test"; \
		$$test; \
	done

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(RESULT_DIR)

.PHONY: all run-tests clean

