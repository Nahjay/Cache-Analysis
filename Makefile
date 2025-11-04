CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O3 -Iinclude
LDFLAGS = 

# If using GCC older than 9, link stdc++fs for filesystem
ifeq ($(shell expr `$(CXX) -dumpversion | cut -f1 -d.` \< 9),1)
    LDFLAGS += -lstdc++fs
endif

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
TARGET = cache_simulator

# Source files
SOURCES = $(SRC_DIR)/main.cpp \
          $(SRC_DIR)/TraceParser.cpp \
          $(SRC_DIR)/LRUCache.cpp \
          $(SRC_DIR)/LFUCache.cpp

# Object files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Default target
all: $(BUILD_DIR) $(TARGET)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link object files
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "Build complete: $(TARGET)"

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
	@echo "Cleaned build artifacts"

# Debug build
debug: CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude
debug: clean all

.PHONY: all clean debug
