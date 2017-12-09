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

    //Single car for testing
    Car c;
    Pos p = Pos(15, 18);
    c.setPosition(p);
    c.setNextPosition(p);

    //Variables for GUI loop
    tileType vertex_to_add;
	int speedUp = 1;
    float refreshSpeed = 1.0 / 60.0;
    float ticker = 0.0;
    sf::Clock clock;
    sf::Time time = clock.restart() + sf::seconds(4);

    //Make a render window
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
            //When mouse is clicked act accordingly
            if (event.type == sf::Event::MouseButtonPressed) {
                int z = event.mouseButton.button;
                sf::Vector2f coord = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                int x = coord.x;
                int y = coord.y;
				p = Pos(x, y);
                int mx = forceToGrid(x);
                int my = forceToGrid(y);
                if (z == sf::Mouse::Left){
                    testGraph.setVertex(mx, my, vertex_to_add);	//Set vertex types with mouse 1
                } else if(z == sf::Mouse::Right) {
                    testGraph.getVertices()[my][mx].togglePassable();	//Toggle traffic lights with mouse 2
                }

                //DEBUG: print all current edges
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

                //DEBUG: Dijkstra
                auto test = getPath(testGraph, v1[1][0], v1[0][1]);

            }
			//Control what kind of vertices to add with keyboard, B: building, R: road, G: grass...
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::B){
                    vertex_to_add = building;
                }
                else if(event.key.code == sf::Keyboard::R){
                    vertex_to_add = road;
                }
                else if(event.key.code == sf::Keyboard::G){
                    vertex_to_add = grass;
                }
                else if(event.key.code == sf::Keyboard::Num3){		//Testing fast forward
                	speedUp = 6;
                }
				else if(event.key.code == sf::Keyboard::Num2){
					speedUp = 3;
				}
				else if(event.key.code == sf::Keyboard::Num1){
					speedUp = 1;
				}
            }
        }

        //Update screen according to refreshSpeed
        if(clock.getElapsedTime().asSeconds() > refreshSpeed){

			//Clear previous
            window.clear();

            //Go through all vertices
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

						//Draw traffic lights
						sf::RectangleShape light(sf::Vector2f(16, 4));
						light.setOrigin(-6, 2);

						direction d = edge.getDirection();

						if(v.getType() == road && v.getEdgesTo().size() > 2) {
							if(v.passable_from[d]) {
								light.setFillColor(sf::Color::Green);
							} else {
								light.setFillColor(sf::Color::Red);
							}
							light.setRotation(-d * 90);
							light.setPosition(p1.x, p1.y);
							window.draw(light);
						}
					}

				}
            }


            //Draw a car
            sf::RectangleShape model(sf::Vector2f(12.0, 12.0));
			int i = 0;			
			while(i < speedUp) {            
				c.move(testGraph);
				i++;
			}
            Pos got = c.getPosition();
            model.setOrigin(6.0, 6.0);
            model.setPosition(got.x, got.y);
            window.draw(model);

            //Test sendVehicle
            std::default_random_engine generator;
            testGraph.getVertices()[4][4].sendVehicle(generator, 5.0);

            //Show everything that has been drawn
            window.display();
            time = clock.restart();
            ticker = ticker + refreshSpeed;
        }

    }

    return 0;
}
