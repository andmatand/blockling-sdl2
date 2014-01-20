CXX=g++
CXXFLAGS=-std=c++11 -Wall -ggdb
LIBS=`sdl2-config --libs`
TARGET=blockling
SRC_DIR=src/
OBJ=$(SRC_DIR)asset_loader.o $(SRC_DIR)entity.o $(SRC_DIR)entity/brick.o \
    $(SRC_DIR)graphics.o $(SRC_DIR)main.o $(SRC_DIR)system.o \
    $(SRC_DIR)system/render.o $(SRC_DIR)world.o

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $^ $(LIBS) 

clean:
	rm -f $(SRC_DIR)*.o
	rm -f $(SRC_DIR)entity/*.o
	rm -f $(SRC_DIR)system/*.o
	rm -f $(TARGET)
