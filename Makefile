kernel = ../kernel/kermdl.o
dump = dumps/dump
log = dumps/log
prog = ./debug

build: 
	g++ -o $(prog) main.cpp $(kernel) -lsfml-graphics -lsfml-window -lsfml-system -O2

# launch with dumps and visual mode
rundv:
	$(prog) v 1>$(dump) 2>$(log)

# launch with dumps
rund:
	$(prog) 1>$(dump) 2>$(log)

# launch in visual mode
runv:
	$(prog) v
