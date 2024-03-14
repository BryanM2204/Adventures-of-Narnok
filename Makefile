CC := g++
SFML_INCLUDE := -IC:\SFML-2.6.1\include
SFML_LIB := -LC:\SFML-2.6.1\lib
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS := -Wall -Wextra -g $(SFML_INCLUDE)
LDFLAGS := $(SFML_LIB) $(SFML_LIBS)

SRCS := main-test.cpp player.cpp Dungeon-Gen/MazeBuilder.cpp Dungeon-Gen/Tile.cpp
OBJS := $(SRCS:.cpp=.o)
TARGET := main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)