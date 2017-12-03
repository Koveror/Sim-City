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
  Graph testGraph(16, 12);
  testGraph.addVertices();
  std::vector<std::vector<Vertex>> v = testGraph.getVertices();
  for(auto j : v){
    for(auto i : j){
        std::cout << "vertex getType: " << i.getType() << std::endl;
    }
  }
  std::cout << "! " << testGraph.addVertex(0,0) << std::endl;
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



    sf::RenderWindow window(sf::VideoMode(1024, 768), "Sim-City");
	window.setVerticalSyncEnabled(true);

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
                if (z == sf::Mouse::Right){
                  testGraph.setVertex(mx, my, building);
                } else if (z == sf::Mouse::Left){
                  testGraph.setVertex(mx, my, road);
                }
                //bool res = testGraph.addVertex(mx, my);
                //std::cout << "(" << mx << ", " << my << ") " << z << ", added: " << res << std::endl;   //Print debugging info

                //TEST: print all curren addVertices
                std::vector<std::vector<Vertex>> v1 = testGraph.getVertices();
                std::cout << "\nCurrent edges:" << std::endl;
                for(auto row : v1){
                    for(auto vertex : row) {
                        Pos a = vertex.getPos();
                        for(auto i : vertex.getEdgesTo()){
                            std::cout << "FROM x:" << a.x << " y: "<< a.y << " TO x: "<< i.x << " y: "<< i.y << std::endl;
                        }
                    }
                }

            }
        }
        //Clear previous
        window.clear();

        //Draw nodes
        std::vector<std::vector<Vertex>> v1 = testGraph.getVertices();
        for(auto row : v1){
            for(auto v : row) {
                Pos a = v.getPos();
                int x = a.x * 64;
                int y = a.y * 64;
				
				sf::CircleShape coord;
				coord.setOrigin(1.5, 1.5);
				coord.setPosition(x, y);
				coord.setRadius(3.0);
				coord.setFillColor(sf::Color::Yellow);
				
				sf::Sprite node;
                node.setTexture(texmanager.getRef(v.getTexture()));

                node.setPosition(x, y);
                window.draw(node);  //Draw all of the nodes to the screen
				window.draw(coord);
				
				std::vector<Pos> neigh = v.getEdgesTo();
				for(Pos p : neigh) {
					sf::CircleShape middle;
					middle.setOrigin(1.5, 1.5);
					middle.setPosition(p.x * 32, p.y * 32);
					middle.setRadius(3.0);
					middle.setFillColor(sf::Color::Red);
					window.draw(middle);
				}
            }
        }


		//Draw a car
		sf::CircleShape model;
		Pos got = c.getPosition();
		model.setOrigin(1.5, 1.5);
		model.setPosition(got.x, got.y);
		model.setRadius(3.0);
		window.draw(model);
		c.moveTowards(p);


        //Show it
        window.display();
    }

    return 0;
}
