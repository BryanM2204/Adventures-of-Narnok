CC := g++
#SFML_INCLUDE := -IC:\SFML-2.6.1\include
#SFML_LIB := -LC:\SFML-2.6.1\lib
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS := -Wall -Wextra -g #$(SFML_INCLUDE)
LDFLAGS := $(SMFL_LIBS) #$(SFML_LIB) $(SFML_LIBS)

SRCS := main.cpp player.cpp map.cpp #main-test.cpp player.cpp map.cpp Dungeon-Gen/MazeBuilder.cpp Dungeon-Gen/Tile.cpp
OBJS := $(SRCS:.cpp=.o)
TARGET := main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(SFML_LIBS)

%.o: %.cpp
	$(CC) $^ -c $@ $(CFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)
