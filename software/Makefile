CC			:= g++
TARGET		:= camera
SOURCES		:= src/*.cpp src/*/*.cpp src/*/*/*.cpp

INCLUDES	:= $(shell pkg-config --cflags libcamera) -I/opt/homebrew/include -I./src/
LIBS		:= -L/opt/homebrew/lib -lSDL3 -lSDL3_ttf $(shell pkg-config --libs libcamera)

all:
	$(CC) $(INCLUDES) -std=c++23 -o $(TARGET) $(SOURCES) $(LIBS) -g
