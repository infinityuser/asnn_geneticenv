#include "build.hpp"

int main (int argc, char * argv[]) {

	bool vis = false;
    if (argc != 1 && argv[1][0] == 'v') vis = true;

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
        makeEpoch();
        if (vis) drawAll();
        if (vis) window.display();

        usleep(actionTimer);
    }
 
    return 0;
}
