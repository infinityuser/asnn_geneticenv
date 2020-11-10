# $(resources)			- local .so structures
# $(resources)/SFML 	- SFML headers
# $(resources)/kernel 	- kernel headers

logs = ./dumps/log
imprint = ./dumps/imprint
resources = /home/ireoi/.lib

all: build run

build:
	g++ -o ./debug main.cpp -L$(resources) -lkermdl -lsfml-graphics -lsfml-window -lsfml-system -lpthread -I$(resources)/asnn

run:
	./debug 2>$(logs) 1>$(imprint)

runv:
	./debug v 2>$(logs) 1>$(imprint)
