# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpragmas -I src/

# Directories
SRC_DIR := src
BUILD_DIR := build

# Find all .cpp source files in src/
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)

# Convert .cpp files to .o object files in build/
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Output executable name
TARGET := main

# Default target
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compile each .cpp file to a .o file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Run the compiled program
run: $(TARGET)
	./$(TARGET)


setup:
	rm -f main
	bear -- make
