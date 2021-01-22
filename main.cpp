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

	env::init(20, 40, 10);

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
 
	return 0;
}
