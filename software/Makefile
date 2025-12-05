CC			:= g++
TARGET		:= camera
SOURCES		:= src/*.cpp src/*/*.cpp src/*/*/*.cpp

INCLUDES	:= -I/usr/include/libcamera -I/opt/homebrew/include -I./src/
LIBS		:= -L/opt/homebrew/lib -lSDL3 -lSDL3_ttf -lcamera

all:
	$(CC) $(INCLUDES) -std=c++23 -o $(TARGET) $(SOURCES) $(LIBS) -g
