#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include "graph.hpp"
#include "vehicle.hpp"
#include "texturemanager.hpp"
#include <cmath>
#include <exception>
//#include "dijkstra.hpp"

int main(void) {

    TextureManager texmanager;

    //Testing data structures
    Graph testGraph = Graph(16, 12);
    testGraph.addVertices();

    //add single cars for testing
    testGraph.addCar(Pos(300, 300));
    testGraph.addCar(Pos(113, 122));
    testGraph.addCar(Pos(300, 400));

    //Variables for GUI loop
    tileType vertex_to_add;
    bool vehicleSendBoolean = false;
    bool autoTrafficLight = false;
    int speedUp = 1;
    float refreshSpeed = 1.0 / 60.0;
    float ticker = 0.0;
    int changeSpeed = 6;
    sf::Clock clock;
    sf::Clock timer;
    sf::Time time = clock.restart() + sf::seconds(4);

    //Make a render window
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Sim-City");
    window.setVerticalSyncEnabled(true);

    //GUI loop
    while (window.isOpen())
    {
        //Automatic traffic light changing

        if (autoTrafficLight && timer.getElapsedTime().asSeconds() > changeSpeed) {
            timer.restart();
            for (auto& row : testGraph.getVertices()) {
                for (Vertex& light : row) {
                    light.togglePassable();
                }
            }
        }
        testGraph.update();

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
                //Pos p = Pos(x, y);
                int mx = x / 64;
                int my = y / 64;
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
                            int weight = edge.getWeight();
                            std::cout << "FROM (" << p1.x << ", " << p1.y << ") TO (" << p2.x << ", " << p2.y << ") - " << "WEIGHT = " << weight << std::endl;
                        }
                    }
                }

                //DEBUG: Dijkstra
                //auto test = getPath(testGraph, v1[1][0], v1[0][1]);

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
                else if(event.key.code == sf::Keyboard::V){
                    vehicleSendBoolean = !vehicleSendBoolean;
                    if(vehicleSendBoolean){
                        std::cout << "Spawning vehicles..." << std::endl;
                    }
                    else {
                        std::cout << "Pausing vehicle spawning" << std::endl;
                    }
                }
                else if(event.key.code == sf::Keyboard::S){ // saveGraph
                    std::string name;
                    std::cout << "Type the full filename to save the map. File-extension not required." << std::endl;
                    std::cin >> name;
                    std::cout << "Saved successfully (1 or 0): " << testGraph.saveGraph(name) << std::endl;
                }
                else if(event.key.code == sf::Keyboard::L){ // loadGraph
                    std::string name;
                    std::cout << "Type the full filename to load the map. File-extension not required." << std::endl;
                    std::cin >> name;
                    std::cout << "Loaded successfully (1 or 0): " << testGraph.loadGraph(name) << std::endl;
                }
                else if(event.key.code == sf::Keyboard::T){
                    autoTrafficLight = !autoTrafficLight;
                    if (autoTrafficLight) {
                        std::cout << "Traffic light control: automatic" << std::endl;
                    }
                    else {
                        std::cout << "Traffic light control: manual (right mouse button, RMB)" << std::endl;
                    }
                }
                else if(event.key.code == sf::Keyboard::Num3){
                    std::cout << "8x speed" << std::endl;
                	speedUp = 8;
                }
                else if(event.key.code == sf::Keyboard::Num2){
                    std::cout << "4x speed" << std::endl;
                    speedUp = 4;
                }
                else if(event.key.code == sf::Keyboard::Num1){
                    std::cout << "Normal speed" << std::endl;
                    speedUp = 1;
                }
                else if(event.key.code == sf::Keyboard::O){
                    int newRate;
                    while (1) {
                        std::cout << "Give an Integer number for how fast traffic lights should automatically change, in seconds (MIN = 4, MAX = 10)" << std::endl;
                        std::cout << "Type -1 to cancel" << std::endl;
                        std::cin >> newRate;
                        try {
                            if(std::cin.fail()){
                                throw "You did not give a valid Integer!";
                            }

                            if (newRate > 10) {
                                throw "Value exceeds maximum!";
                            }
                            else if (newRate < 4 && newRate != -1) {
                                throw "Value falls below minimum!";
                            }
                            else if (newRate == -1) {
                                std::cout << "Input cancelled." << std::endl;
                                break;
                            }
                            else {
                                changeSpeed = newRate;
                            }
                            std::cout << "current changeSpeed is: " << changeSpeed << std::endl;
                            break;
                        } catch (const char* error) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<int>::max(),'\n');
                            std::cerr << "Error! " << error << std::endl;
                        }
                    }
                }
                else if(event.key.code == sf::Keyboard::P){
                    std::cout << "Game paused..." << std::endl;
                    speedUp = 0;
                }
                /*else if(event.key.code == sf::Keyboard::D){             //Testing Dijkstra
                    auto test = getPath(testGraph, testGraph.getVertices()[1][0], testGraph.getVertices()[0][3]);
                    std::cout << "Path from source to target below: " << std::endl;
                    for (auto& v : test)  {
                        std::cout << v.getVertices().first.getPos().x << ", " << v.getVertices().first.getPos().y << " to " << v.getVertices().second.getPos().x << ", " << v.getVertices().second.getPos().y << std::endl;
                    }
                }*/
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

                    //Send vehicles
                    if(vehicleSendBoolean){
                        if(v.getType() == building){
                            testGraph.sendVehicle(a);
                        }
                    }

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
                            sf::RectangleShape light(sf::Vector2f(18, 2));
                            light.setOrigin(-4, 2);

                            direction d = edge.getDirection();

                            if( (v.getType() == road && v.getEdgesTo().size() > 2 /*) || (v.getType() == building && v.getEdgesTo().size() > 2*/ ) ) { // should be 2, now 1 due to debug purposes
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


            //Go through all the vehicles
            for(auto vehicle : testGraph.getVehicles()) {
                sf::RectangleShape model(sf::Vector2f(12.0, 12.0));
                    int i = 0;
                    while(i < speedUp) {
                        //std::cout << "calling move" << std::endl;
                        vehicle -> move(testGraph);
                        i++;
                    }
                Pos got = vehicle -> getPosition();
                model.setOrigin(6.0, 6.0);
                model.setPosition(got.x, got.y);
                window.draw(model);
            }

            //Show everything that has been drawn
            window.display();
            time = clock.restart();
            ticker = ticker + refreshSpeed;
        }

    }

    return 0;
}
