CC			:= g++
CCFLAGS		:= -std=c++23
TARGET		:= ./camera

SOURCES		:= $(shell find ./ -type f -name "*.cpp")
OBJECTS		:= $(SOURCES:.cpp=.o)
BUILT		:= $(subst src,build,$(OBJECTS))

INCLUDES	:= $(shell pkg-config --cflags libcamera) -I/opt/homebrew/include -I./src/
LIBS		:= -L/opt/homebrew/lib -lSDL3 -lSDL3_ttf $(shell pkg-config --libs libcamera)

.PHONY: all
all: $(TARGET)

$(TARGET): $(BUILT)
	@ echo Linking...
	@ $(CC) $(INCLUDES) $(CCFLAGS) -o $(TARGET) $(BUILT) $(LIBS) -g

build/%.o: src/%.cpp
	@ echo Building $@...
	@ mkdir -p ./build
	@ mkdir -p $(dir $@)
	@ $(CC) $(INCLUDES) $(CCFLAGS) -c $< -o $(subst src,build,$@) -g

clean:
	@ rm -rf ./build
	@ echo Cleaned build files.