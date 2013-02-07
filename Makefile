APP=Trajectory
CPPFLAGS=-Iinc -W -Wall -pedantic
LDFLAGS= -lm

__start__: all
rm -f core.* core; ./

all: 

./: obj/Main.o obj/Controller.o obj/TrajectoryBuilder.o
g++  -o ./ obj/Main.o obj/Controller.o obj/TrajectoryBuilder.o

obj/Main.o: src/Main.cpp inc/Controller.hh inc/TrajectoryBuilder.hh
g++ -c  -o obj/Main.o src/Main.cpp

obj/Controller.o: src/Controller.cpp inc/Controller.hh
g++ -c  -o obj/Controller.o src/Controller.cpp

obj/TrajectoryBuilder.o: src/TrajectoryBuilder.cpp inc/TrajectoryBuilder.hh
g++ -c  -o obj/TrajectoryBuilder.o src/TrajectoryBuilder.cpp

clean:
rm -f obj/*.o ./ core.* core
