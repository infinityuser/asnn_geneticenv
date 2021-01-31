#include "build.hpp"

FILE * dump;
void intrsig (int sig) {
	fclose(dump);
	exit(0);
}

int main (int argc, char * argv[]) {
	bool vis = false;
	if (argc != 1 && argv[1][0] == 'v') vis = true;
	dump = fopen(argv[2], "w");
	signal(SIGINT, intrsig);

	env::init(6, 40, 0);

	if (vis) {
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			if (vis) window.clear();
			makeEpoch(dump);
			if (vis) drawAll();
			if (vis) window.display();

			usleep(actionTimer);
		}
	} else {
		window.close();
		while (true)
			makeEpoch(dump);
	}
 
	return 0;
}
