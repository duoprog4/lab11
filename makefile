CXX = g++
CXXFLAGS = -Wall -Wextra

TARGET = matrix_program

SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
