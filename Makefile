APP=Trajectory
CPPFLAGS=-Iinc -W -Wall -pedantic
LDFLAGS= -lm

__start__: all
	rm -f core.* core; ./${APP}

all: ${APP}

./${APP}: obj/Main.o obj/Controller.o obj/TrajectoryBuilder.o obj/DataStructures.o obj/AStar.o
	g++ ${LDFLAGS} -o ./${APP} obj/Main.o obj/Controller.o obj/TrajectoryBuilder.o obj/DataStructures.o obj/AStar.o

obj/Main.o: src/Main.cpp inc/Controller.hh inc/TrajectoryBuilder.hh inc/AStar.hh
	g++ -c ${CPPFLAGS} -o obj/Main.o src/Main.cpp

obj/Controller.o: src/Controller.cpp inc/Controller.hh
	g++ -c ${CPPFLAGS} -o obj/Controller.o src/Controller.cpp

obj/TrajectoryBuilder.o: src/TrajectoryBuilder.cpp inc/TrajectoryBuilder.hh inc/DataStructures.hh
	g++ -c ${CPPFLAGS} -o obj/TrajectoryBuilder.o src/TrajectoryBuilder.cpp

obj/DataStructures.o: src/DataStructures.cpp inc/DataStructures.hh
	g++ -c ${CPPFLAGS} -o obj/DataStructures.o src/DataStructures.cpp

obj/AStar.o: src/AStar.cpp inc/AStar.hh inc/DataStructures.hh
	g++ -c ${CPPFLAGS} -o obj/AStar.o src/AStar.cpp

clean:
	rm -f obj/*.o ./${APP} core.* core
