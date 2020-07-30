kernel = ../kernel/kermdl.o

build: main.cpp $(kernel)
	g++ -o ./debug main.cpp $(kernel) -lsfml-graphics -lsfml-window -lsfml-system -llapack -lblas -O2

runv:
	./debug v 1>dumps/dumpone 2>dumps/logone

run:
	./debug 1>dumps/dumpone 2>dumps/logone

runt:
	./debug 1>dumps/dumptwo 2>dumps/logtwo

runc:
	./debug v
