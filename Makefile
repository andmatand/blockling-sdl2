CXX=g++
CXXFLAGS=-std=c++11 -Wall -ggdb
LIBS=`sdl2-config --libs`
TARGET=blockling
SRC_DIR=src/
OBJ=$(SRC_DIR)asset_loader.o $(SRC_DIR)graphics.o $(SRC_DIR)main.o

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $^ $(LIBS) 

clean:
	rm -f $(SRC_DIR)*.o
	rm -f $(TARGET)
