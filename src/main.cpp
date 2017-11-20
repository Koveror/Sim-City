#include <iostream>
#include <SFML/Graphics.hpp>
#include "graph.hpp"
#include "graph.cpp"

int main(void) {
	std::cout << "Hello world!" << std::endl;

 	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    Graph worldMap(3,3);
    worldMap.addVertices();
    std::cout << worldMap.getSize() << std::endl;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

	return 0;
}
