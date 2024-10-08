CC := g++
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS := -Wall -Wextra -g
LDFLAGS := $(SFML_LIBS) -lstdc++

SRCS := main.cpp Player/player.cpp Dungeon/map.cpp Dungeon/DungeonGen/Leaf.cpp Dungeon/DungeonGen/Rectangle.cpp
OBJS := $(SRCS:.cpp=.o)
TARGET := main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

DungeonGen/Rectangle.o: Dungeon/DungeonGen/Rectangle.cpp Dungeon/DungeonGen/Rectangle.h
	$(CC) -c $< -o $@ $(CFLAGS)

DungeonGen/Leaf.o: Dungeon/DungeonGen/Leaf.cpp Dungeon/DungeonGen/Leaf.h Dungeon/DungeonGen/Rectangle.h
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)