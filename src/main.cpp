#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include "graph.hpp"
#include "vehicle.hpp"



//Placeholder datastructures for nodes in graph
std::vector<sf::CircleShape> nodes;     //Store shapes directly for drawing?
std::vector<sf::Vector2f> coords;       //Store coordinates and make shapes for drawing on the fly?

//Force coordinates to a grid
int forceToGrid(int a) {
    /*
    int ma;
    if((a % 16) < 8) {
        ma = a - (a % 16);
    } else {
        ma = a - (a % 16) + 16;
    }
    return ma;
    */
    return a / 64 * 64;
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



      //load textures
      sf::Texture grass;
      sf::Texture building;

      if (!grass.loadFromFile("img/grass.png")){
        std::cout << "grass.png not found" << std::endl;
      }
      if (!building.loadFromFile("img/building.png")){
        std::cout << "building.png not found" << std::endl;
      }




      //Testing datastructures
      Graph testGraph(3,3);
      testGraph.addVertices();
      std::vector<Vertex> v = testGraph.getVertice();
      for(Vertex i : v){
          std::cout << i.getType() << std::endl;
      }



    //Testing classes
    Vertex testVertex = Vertex(0, 0, "Grass");
    std::cout << "testVertex coord: " << testVertex.getCoord().first << ", "
    << testVertex.getCoord().second << std::endl;
    std::cout << "testVertex type: " << testVertex.getType() << std::endl;
    Car cr;
    Truck tr;
    std::vector<Vehicle*> vehicles;
    vehicles.push_back(&cr);
    vehicles.push_back(&tr);

    for (auto it : vehicles) {
        std::cout << "vehicle type: " << it->getType() << " and length: " << it->getLength() << std::endl;
    }


    sf::RenderWindow window(sf::VideoMode(1024, 768), "Sim-City");



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
                sf::Vector2f coord = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                int x = coord.x;
                int y = coord.y;
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
            //sf::CircleShape node(radius);
            //node.setOrigin(radius, radius);
            //node.setFillColor(sf::Color::Green);
            //node.setPosition(x, y);
            sf::Sprite node;
            node.setTexture(grass);
            node.setPosition(x, y);
            window.draw(node);  //Draw all of the nodes to the screen
        }

        sf::Sprite g;
        g.setTexture(grass);
        window.draw(g);

        //Show it
        window.display();
    }

    return 0;
}
