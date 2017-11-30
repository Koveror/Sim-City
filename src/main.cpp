#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include "graph.hpp"
#include "vehicle.hpp"

//Force coordinates to a grid
int forceToGrid(int a) {
    return a / 64;
}

int main(void) {

	//load textures
	sf::Texture grassTex;
	sf::Texture buildingTex;
  sf::Texture roadTex;

  if (!grassTex.loadFromFile("img/grass.png")){
    std::cout << "grass.png not found" << std::endl;
  }
  if (!buildingTex.loadFromFile("img/building.png")){
    std::cout << "building.png not found" << std::endl;
  }
  if (!roadTex.loadFromFile("img/road.png")){
    std::cout << "road.png not found" << std::endl;
  }

  //Testing datastructures
  Graph testGraph(3, 3);
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
                        std::pair<int,int> coord = vertex.getCoord();
                        for(auto i : vertex.getEdgesTo()){
                            std::cout << "(" << coord.first << ", "<< coord.second << ") to "<< "(" << i.x << ", "<< i.y << ")" << std::endl;
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
            for(auto vector : row) {
                tileType t = vector.getType();
                std::pair<int, int> pos = vector.getCoord();
                int x = pos.first * 64;
                int y = pos.second * 64;
                sf::Sprite node;
                if (t == grass){
                node.setTexture(grassTex);
                }else if (t == building){
                node.setTexture(buildingTex);
                }else if (t == road){
                node.setTexture(roadTex);
                }
                node.setPosition(x, y);
                window.draw(node);  //Draw all of the nodes to the screen
            }
        }
		
		//Draw a car
		sf::CircleShape model;
		Pos got = c.getPosition();
		model.setPosition(got.x, got.y);
		model.setRadius(3.0);
		window.draw(model);
		c.moveTowards(p);
		
        //Show it
        window.display();
    }

    return 0;
}
