# $(resources)			- local .so structures
# $(resources)/SFML 	- SFML headers
# $(resources)/kernel 	- kernel headers

logs = ./dumps/log
resources = /home/ireoi/.lib

all: build run

build:
	g++ -o ./debug main.cpp -L$(resources) -lkermdl -lsfml-graphics -lsfml-window -lsfml-system -lpthread -I$(resources)/asnn

run:
	./debug nv ./dumps/imprint 2>$(logs) 

runv:
	./debug v ./dumps/imprint 2>$(logs) 
