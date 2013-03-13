APP=Trajectory
CPPFLAGS=-Iinc -W -Wall -pedantic
LDFLAGS= -lm

__start__: all
	rm -f core.* core; ./${APP}

all: ${APP}

./${APP}: obj/Main.o obj/Controller.o obj/TrajectoryBuilder.o
	g++ ${LDFLAGS} -o ./${APP} obj/Main.o obj/Controller.o obj/TrajectoryBuilder.o

obj/Main.o: src/Main.cpp inc/Controller.hh inc/TrajectoryBuilder.hh
	g++ -c ${CPPFLAGS} -o obj/Main.o src/Main.cpp

obj/Controller.o: src/Controller.cpp inc/Controller.hh
	g++ -c ${CPPFLAGS} -o obj/Controller.o src/Controller.cpp

obj/TrajectoryBuilder.o: src/TrajectoryBuilder.cpp inc/TrajectoryBuilder.hh
	g++ -c ${CPPFLAGS} -o obj/TrajectoryBuilder.o src/TrajectoryBuilder.cpp

clean:
	rm -f obj/*.o ./${APP} core.* core
