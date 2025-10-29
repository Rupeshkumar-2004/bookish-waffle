
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Output executable name
TARGET = jobportal

# Source files
SRC = main.cpp JobPortal.cpp

# Object directory
OBJDIR = build

# Convert .cpp → build/*.o
OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)

# Default rule
all: $(TARGET)

# Build executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Build object files inside build/
$(OBJDIR)/%.o: %.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean project
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Rebuild everything
rebuild: clean all
