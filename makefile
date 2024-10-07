# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -I/usr/include/SFML -I.

# SFML libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRCS = \
    MonopolyGame.cpp \
    Board.cpp \
    Player.cpp \
    Square.cpp \
    GUI_Manager.cpp \
    GameManager.cpp \
    SquareFactory.cpp

# Object files corresponding to the source files
OBJS = $(SRCS:.cpp=.o)

# Output executable name
TARGET = MonopolyGame

# Build target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
    $(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

# Rule for creating object files
%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

# Explicit dependencies
MonopolyGame.o: MonopolyGame.hpp Board.hpp Player.hpp GUI_Manager.hpp GameManager.hpp SquareFactory.hpp
Board.o: Board.hpp Square.hpp
Player.o: Player.hpp Square.hpp
Square.o: Square.hpp
GUI_Manager.o: GUI_Manager.hpp Board.hpp Player.hpp
GameManager.o: GameManager.hpp Board.hpp Player.hpp GUI_Manager.hpp
SquareFactory.o: SquareFactory.hpp Square.hpp

# Clean up build files
.PHONY: clean
clean:
    rm -f $(TARGET) $(OBJS)
