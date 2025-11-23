Dungeon: Entity.o Room.o Game.o main.o
	g++ Entity.o Room.o Game.o main.o -o Dungeon

Entity.o: Entity.cpp Entity.h
	g++ -c Entity.cpp

Game.o: Game.cpp Game.h Entity.h Room.h
	g++ -c Game.cpp

Room.o: Room.cpp Room.h Entity.h
	g++ -c Room.cpp

main.o: main.cpp Game.h Entity.h Room.h
	g++ -c main.cpp

clean:
	rm -f *.o Dungeon
