#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include "graph.hpp"
#include "vehicle.hpp"
#include "texturemanager.hpp"



//Force coordinates to a grid
int forceToGrid(int a) {
    return a / 64;
}

int main(void) {

  TextureManager texmanager;

  //Testing datastructures
  Graph testGraph = Graph(16, 12);
  testGraph.addVertices();
 
  //testGraph.setVertex(0, 0, building);
	/*
    //Testing classes
    Car cr;
    Truck tr;
    std::vector<Vehicle*> vehicles;
    vehicles.push_back(&cr);
    vehicles.push_back(&tr);

    for (auto it : vehicles) {
        std::cout << "vehicle type: " << it->getType() << " and length: " << it->getLength() << std::endl;
    }
	*/

	Car c;
	Pos p = Pos(15, 18);
	c.setPosition(p);
	c.setNextPosition(p);



    sf::RenderWindow window(sf::VideoMode(1024, 768), "Sim-City");
	window.setVerticalSyncEnabled(true);
    //variables for GUI loop
    tileType vertex_to_add;
    sf::Clock clock;
    sf::Time time = clock.restart() + sf::seconds(4);
    std::cout << time.asSeconds() << std::endl;
    int q = 0;
        
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
				p = Pos(x, y);
                int mx = forceToGrid(x);
                int my = forceToGrid(y);
                if (z == sf::Mouse::Left){
                  testGraph.setVertex(mx, my, vertex_to_add);
                } 

                //TEST: print all current edges
                std::vector<std::vector<Vertex>> v1 = testGraph.getVertices();
                std::cout << "\nCurrent edges:" << std::endl;
                for(auto row : v1){
                    for(auto vertex : row) {
                        for(auto edge : vertex.getEdgesTo()){
							Vertex v1 = edge.getVertices().first;
							Vertex v2 = edge.getVertices().second;
							Pos p1 = v1.getIndex();
							Pos p2 = v2.getIndex();
                            std::cout << "FROM (" << p1.x << ", " << p1.y << ") TO (" << p2.x << ", " << p2.y << ")" << std::endl;
                        }
                    }
                }

            }
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::B){
                    vertex_to_add = building;
                    std::cout << "building" << std::endl;
                }
                else if(event.key.code == sf::Keyboard::R){
                    vertex_to_add = road;
                }
                else if(event.key.code == sf::Keyboard::G){
                    vertex_to_add = grass;
                }
            }
        }
        
        //Update screen
        if(clock.getElapsedTime().asSeconds() > 1/30){
            //Clear previous
            window.clear();

            //Draw nodes
            std::vector<std::vector<Vertex>> v1 = testGraph.getVertices();
            for(auto row : v1){
                for(auto v : row) {
                    Pos a = v.getPos();
                    int x = a.x;
                    int y = a.y;
                                    

                                    //Draw all the sprites
                                    sf::Sprite node;
                    node.setTexture(texmanager.getRef(v.getTexture()));
                                    node.setOrigin(32, 32);
                    node.setPosition(x, y);
                                    window.draw(node);

                                    //Draw middle points of nodes
                                    sf::CircleShape coord;
                                    coord.setOrigin(3.0, 3.0);
                                    coord.setPosition(x, y);
                                    coord.setRadius(3.0);
                                    coord.setFillColor(sf::Color::Yellow);
                                    window.draw(coord);
                                    
                                    //Draw middle points of all edges
                                    for(Edge edge : v.getEdgesTo()) {
                                            Pos p1 = edge.getMiddlePos();
                                            sf::CircleShape middle;
                                            middle.setOrigin(3.0, 3.0);
                                            middle.setPosition(p1.x, p1.y);
                                            middle.setRadius(3.0);
                                            middle.setFillColor(sf::Color::Red);
                                            window.draw(middle);
                                    }
                                    
                }
            }


            //Draw a car
            sf::CircleShape model;
            c.move(testGraph);
            Pos got = c.getPosition();
            model.setOrigin(3.0, 3.0);
            model.setPosition(got.x, got.y);
            model.setRadius(3.0);
            window.draw(model);
            
            //Show it
            window.display();
            std::cout << time.asSeconds() << std::endl;
            time = clock.restart();
        }
        std::cout << time.asSeconds() << std::endl;
        q += 1;
        std::cout << q << std::endl;
        
    }

    return 0;
}
