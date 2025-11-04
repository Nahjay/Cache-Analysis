# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O3 -Iinclude
LDFLAGS = 

# Detect platform
ifeq ($(OS),Windows_NT)
    RM = rmdir /S /Q
    MKDIR = mkdir
    SEP = \\
    DETECT_GCC_VER = 0
else
    RM = rm -rf
    MKDIR = mkdir -p
    SEP = /
    DETECT_GCC_VER = $(shell expr `$(CXX) -dumpversion | cut -f1 -d.` \< 9)
endif

# Link filesystem library if using GCC < 9
ifeq ($(DETECT_GCC_VER),1)
    LDFLAGS = -lstdc++fs
endif

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
TARGET = cache_simulator

# Automatically detect all .cpp files in src/
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# Default target
all: $(BUILD_DIR) $(TARGET)

# Create build directory
$(BUILD_DIR):
	$(MKDIR) $(BUILD_DIR)

# Link object files (LDFLAGS now comes AFTER object files)
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "✅ Build complete: $(TARGET)"

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	-$(RM) $(BUILD_DIR)
	-$(RM) $(TARGET)
	@echo "🧹 Cleaned build artifacts"

# Debug build
debug: CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude
debug: clean all

.PHONY: all clean debug
