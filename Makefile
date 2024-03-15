CC := g++
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS := -Wall -Wextra -g
LDFLAGS := $(SFML_LIBS) -lstdc++

SRCS := main.cpp player.cpp map.cpp DungeonGen/Leaf.cpp DungeonGen/Rectangle.cpp
OBJS := $(SRCS:.cpp=.o)
TARGET := main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

DungeonGen/Rectangle.o: DungeonGen/Rectangle.cpp DungeonGen/Rectangle.h
	$(CC) -c $< -o $@ $(CFLAGS)

DungeonGen/Leaf.o: DungeonGen/Leaf.cpp DungeonGen/Leaf.h DungeonGen/Rectangle.h
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)