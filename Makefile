all: compile link

compile:
	g++ -IC:\SFML-2.6.1\include -c main.cpp player.cpp

link:
	g++ main.o player.o -LC:\SFML-2.6.1\lib -lsfml-graphics -lsfml-window -lsfml-system -o main

