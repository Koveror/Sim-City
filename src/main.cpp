#include <iostream>
#include <vector>
#include <unordered_set>
#include <SFML/Graphics.hpp>

//Placeholder datastructures for nodes in graph
std::vector<sf::CircleShape> nodes;     //Store shapes directly for drawing?
std::vector<sf::Vector2f> coords;       //Store coordinates and make shapes for drawing on the fly?

//Force coordinates to a grid
int forceToGrid(int a) {
    int ma;
    if((a % 16) < 8) {
        ma = a - (a % 16);
    } else {
        ma = a - (a % 16) + 16;
    }
    return ma;
}

//Adds nodes to the vector
int addNode(int x, int y) {
    sf::CircleShape node(10.f);
    node.setOrigin(5, 5);
    node.setFillColor(sf::Color::Green);
    node.setPosition(x, y);
    nodes.push_back(node);
    return 1;
}

int main(void) {
    
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    
    //GUI loop
    while (window.isOpen())
    {
        sf::Event event;
        //Event loop listens for events and reacts
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            //When mouse is clicked, add nodes to vector
            if (event.type == sf::Event::MouseButtonPressed) {
                int z = event.mouseButton.button;
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                int mx = forceToGrid(x);
                int my = forceToGrid(y);
                sf::Vector2f v1(mx, my);
                coords.push_back(v1);       //Store coordinates for drawing
                int res = addNode(mx, my);  //Or store shapes directly
                std::cout << "(" << mx << ", " << my << ") " << z << ", added: " << res << std::endl;   //Print debugging info
            }
        }
        //Clear previous
        window.clear();
        //Draw lines
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(16, 16)),
            sf::Vertex(sf::Vector2f(16, 32))
        };
        window.draw(line, 2, sf::Lines);
        
        sf::Vertex line2[] =
        {
            sf::Vertex(sf::Vector2f(32, 32)),
            sf::Vertex(sf::Vector2f(16, 32))
        };
        window.draw(line2, 2, sf::Lines);
        //Draw nodes
        for(auto vector : coords) {
            int x = vector.x;
            int y = vector.y;
            int radius = 4;
            sf::CircleShape node(radius);
            node.setOrigin(radius, radius);
            node.setFillColor(sf::Color::Green);
            node.setPosition(x, y);
            window.draw(node);  //Draw all of the nodes to the screen
        }
        //Show it
        window.display();
    }

    return 0;
}
