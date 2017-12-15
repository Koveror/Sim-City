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
#include <cassert>
#include <algorithm>
#include <math.h>

///To run tests, uncomment (event.key.code == sf::Keyboard::Z) in the if else block.
int test(void) {
    std::cout << "Begin unit tests..." << std::endl;

    //Init Graph
    Graph testG = Graph(4, 3);
    testG.addVertices();

    //Graph addVertices, getSize, getSizeX, getsizeY
    assert(testG.getSize() == 12);
    std::cout << "Graph addVertices() and getSize() works properly" << std::endl;
    assert(testG.getSizeX() == 4);
    std::cout << "Graph getSizeX() works properly" << std::endl;
    assert(testG.getSizeY() == 3);
    std::cout << "Graph getSizeY() works properly" << std::endl;

    //Graph setVertex, getVertices; Vertex setType, getType
    testG.setVertex(0,1,building);
    auto type = testG.getVertices()[1][0].getType();
    assert(type == building);
    testG.getVertices()[1][0].setType(road);
    type = testG.getVertices()[1][0].getType();
    assert(type == road);
    std::cout << "Graph getVertices() (and setVertex() ) & Vertex getType() and setType() works properly" << std::endl;

    assert(testG.getVehicles().size() == 0);
    std::cout << "Graph getVehicles is: " << testG.getVehicles().size() << std::endl;
    auto position = Pos(0,0);
    assert(position.x == 0 && position.y == 0);
    std::cout << "created Position Pos(0,0). Now testing sendVehicle (and addVehicle)..." << std::endl;

    //Graph getVehicles, sendVehicle
    testG.setVertex(0,0,building);
    testG.setVertex(0,2,building);
    testG.sendVehicle(position, 1, 10000.0); //unusually high rate to ensure that vehicle DEFINITELY spawns
    //testG.addVehicle(position);
    //std::cout << "Graph getVehicles is: " << testG.getVehicles().size() << std::endl;
    assert(testG.getVehicles().size() == 1);
    std::cout << "Graph getVehicles is 1. Both Graph getVehicles() and sendVehicle (and addVehicle) works." << std::endl;

    //Graph getPath, Vertex getPos & getIndex
    assert(testG.getPath(testG.getVertices()[0][0],testG.getVertices()[2][0]).size() == 2);
    std::cout << "Graph getPath works." << std::endl;

    Vertex a = Vertex(1, 1, road);
    assert(a.getPos() == Pos(96,96) && a.getIndex() == Pos(1,1));
    std::cout << "Vertex getPos() and getIndex() works." << std::endl;

    //hasEdgeTo, getEdgesTo (and confirming removeEdge works aswell) & getTexture
    auto u = testG.getVertices()[0][0];
    assert(u.getEdgesTo().size() == 1);
    assert(u.hasEdgeTo(0,1));
    std::cout << "Vertex hasEdgeTo() and getEdgesTo() works." << std::endl;
    testG.setVertex(0,0,grass);
    u = testG.getVertices()[0][0];
    assert(u.getEdgesTo().size() == 0);
    std::cout << "Removing edges works." << std::endl;
    assert(testG.getVertices()[0][0].getTexture() == "grass");
    std::cout << "Vertex getTexture() works." << std::endl;

    Vehicle testVehA = Vehicle(4, 6);
    Vehicle testVehB = Vehicle(6, 8);
    Vehicle copyVehA = Vehicle(testVehA);
    Vehicle copyVehB = testVehB;

    //
    assert(testVehA.getWidth() == copyVehA.getWidth() && testVehA.getHeight() == copyVehA.getHeight());
    assert(testVehB.getWidth() == copyVehB.getWidth() && testVehB.getHeight() == copyVehB.getHeight());
    std::cout << "Copy constructor and assignment works, Vehicle getWidth() and getHeight() also work." << std::endl;

    //
    Vehicle *c = new Car();
    assert(c->getHeight() == 12);
    delete c;
    std::cout << "Derived class Car works." << std::endl;
    Vehicle *t = new Truck();
    assert(t->getHeight() == 16);
    delete t;
    std::cout << "Derived class Truck works." << std::endl;

    return 0;
}

int main(void) {

    TextureManager texmanager;

    //Testing data structures
    Graph testGraph = Graph(16, 12);
    testGraph.addVertices();

    //add single cars for testing
    //testGraph.addCar(Pos(300, 300));
    //testGraph.addCar(Pos(113, 122));
    //testGraph.addCar(Pos(300, 400));

    //Variables for GUI loop
    tileType vertex_to_add;
    float waitTime = 1.0;
    bool vehicleSendBoolean = false;
    bool autoTrafficLight = true;
    int speedUp = 1;
    float refreshSpeed = 1.0 / 60.0;
    float ticker = 0.0;
    float rate = 1.0;
    int changeSpeed = 6;
    bool trafficLightsOn = false;
    sf::Clock clock;
    sf::Clock timer;
    sf::Time time = clock.restart() + sf::seconds(4);

    //Make a render window
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Sim-City");
    window.setVerticalSyncEnabled(true);

    //Welcome msg on console
    std::cout << "Welcome to sim-city-1! Press H for help/instructions" << std::endl;
    std::cout << "This simulation is created for the Aalto University C++ programming course ELEC-A7150." << std::endl;

    //GUI loop
    while (window.isOpen())
    {
        //Automatic traffic light changing

        if (trafficLightsOn && autoTrafficLight && timer.getElapsedTime().asSeconds() * speedUp > changeSpeed) {
            timer.restart();
            for (auto& row : testGraph.getVertices()) {
                for (Vertex& light : row) {
                    light.togglePassable(!trafficLightsOn);
                }
            }
            trafficLightsOn = false;
        }
        if (!trafficLightsOn && autoTrafficLight && timer.getElapsedTime().asSeconds() * speedUp > waitTime) {
            timer.restart();
            for (auto& row : testGraph.getVertices()) {
                for (Vertex& light : row) {
                    light.togglePassable(!trafficLightsOn);
                }
            }
            trafficLightsOn = true;
        }

        /*sf::Clock callUpdate;
        if (callUpdate.getElapsedTime().asSeconds() > waitTime) {
            callUpdate.restart();
            testGraph.update();
        }*/

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
                    testGraph.setRoutes();
                    testGraph.updateAfterSetVertex();
                } /*else if(z == sf::Mouse::Right) {
                    testGraph.getVertices()[my][mx].togglePassable();	//Toggle traffic lights with mouse 2
                    sf::Clock wait;
                    //sf::Time waitTime = wait.restart();
                    if (wait.getElapsedTime().asSeconds() * speedUp > waitTime) {
                        testGraph.getVertices()[my][mx].togglePassable();
                    }
                }*/

                /*
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

                */

                //DEBUG: Dijkstra
                //auto test = getPath(testGraph, v1[1][0], v1[0][1]);

            }
                //Control what kind of vertices to add with keyboard, B: building, R: road, G: grass...
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::B){
                    std::cout << "Now selected: Building" << std::endl;
                    vertex_to_add = building;
                }
                else if(event.key.code == sf::Keyboard::R){
                    std::cout << "Now selected: Road" << std::endl;
                    vertex_to_add = road;
                }
                else if(event.key.code == sf::Keyboard::G){
                    std::cout << "Now selected: Grass" << std::endl;
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
                    std::cout << "Type -1 to cancel" << std::endl;
                    std::cin >> name;
                    testGraph.saveGraph(name);
                }
                else if(event.key.code == sf::Keyboard::L){ // loadGraph
                    std::string name;
                    std::cout << "Type the full filename to load the map. File-extension not required." << std::endl;
                    std::cout << "Type -1 to cancel" << std::endl;
                    std::cin >> name;
                    testGraph.loadGraph(name);
                }
                /*else if(event.key.code == sf::Keyboard::T){
                    autoTrafficLight = !autoTrafficLight;
                    if (autoTrafficLight) {
                        std::cout << "Traffic light control: automatic" << std::endl;
                    }
                    else {
                        std::cout << "Traffic light control: manual (right mouse button, RMB)" << std::endl;
                    }
                }*/
                else if(event.key.code == sf::Keyboard::Num3){
                    std::cout << "Now at: 8x speed" << std::endl;
                    speedUp = 8;
                }
                else if(event.key.code == sf::Keyboard::Num2){
                    std::cout << "Now at: 4x speed" << std::endl;
                    speedUp = 4;
                }
                else if(event.key.code == sf::Keyboard::Num1){
                    std::cout << "Now at: Normal speed" << std::endl;
                    speedUp = 1;
                }
                else if(event.key.code == sf::Keyboard::I){
                    float newRate;
                    while (1) {
                        std::cout << "Give a floating point number for how fast buildings should send vehicles (MIN = 0.25, MAX = 4.0)" << std::endl;
                        std::cout << "Type -1 to cancel" << std::endl;
                        std::cin >> newRate;
                        try {
                            if(std::cin.fail()){
                                throw "You did not give a valid floating point number!";
                            }

                            if (newRate > 4.0) {
                                throw "Value exceeds maximum!";
                            }
                            else if (newRate < 0.25 && newRate != -1) {
                                throw "Value falls below minimum!";
                            }
                            else if (newRate == -1) {
                                std::cout << "Input cancelled." << std::endl;
                                break;
                            }
                            else {
                                rate = newRate;
                            }
                            std::cout << "Current rate is: " << rate << std::endl;
                            break;
                        } catch (const char* error) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<int>::max(),'\n');
                            std::cerr << "Error! " << error << std::endl;
                        }
                    }
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
                            std::cout << "Current changeSpeed is: " << changeSpeed << std::endl;
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
                else if(event.key.code == sf::Keyboard::H){ ///TODO
                    std::cout << "Instructions:" << std::endl;
                    std::cout << "- Click Right Mouse Button (RMB) to toggle individual road intersection traffic light" << std::endl;
                    std::cout << "- Press R, G or B to select which kind of tile to add." << std::endl;
                    std::cout << "  Once the tile type has been selected, use left mouse button to add the tile by clicking on the screen." << std::endl;
                    std::cout << "  R = road, G = grass and B = building." << std::endl;
                    std::cout << "- Press S or L to save or load." << std::endl;
                    std::cout << "  Follow further instructions on the console." << std::endl;
                    //std::cout << "- Press T to toggle automatic traffic light control." << std::endl;
                    std::cout << "  Note that even if you're on automatic mode, you can still manually change individual lights." << std::endl;
                    std::cout << "- Press I to change the rate that buildings spawn cars." << std::endl;
                    std::cout << "- Press O (not zero) to change the rate that automatic traffic light control changes lights." << std::endl;
                    std::cout << "  Further instructions will appear on the console." << std::endl;
                    std::cout << "- Press 1, 2 or 3 to change game speed." << std::endl;
                    std::cout << "  1 = normal speed, 2 = 4x speed and 3 = 8x speed" << std::endl;
                    std::cout << "- Press P to pause the game. To resume the game, press 1, 2 or 3." << std::endl;
                }
                /*else if(event.key.code == sf::Keyboard::Z){
                    test();
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
                            testGraph.sendVehicle(a, speedUp, rate);
                        }
                    }

                    //Draw all the sprites
                    sf::Sprite node;
                    node.setTexture(texmanager.getRef(v.getTexture()));
                    node.setOrigin(32, 32);
                    node.setPosition(x, y);
                    window.draw(node);

                    /* DEBUG
                    //Draw middle points of nodes
                    sf::CircleShape coord;
                    coord.setOrigin(3.0, 3.0);
                    coord.setPosition(x, y);
                    coord.setRadius(3.0);
                    coord.setFillColor(sf::Color::Yellow);
                    window.draw(coord);

                    */

                    //Draw middle points of all edges
                    for(Edge edge : v.getEdgesTo()) {
                        Pos p1 = edge.getMiddlePos();
                        /* DEBUG
                        sf::CircleShape middle;
                        middle.setOrigin(3.0, 3.0);
                        middle.setPosition(p1.x, p1.y);
                        middle.setRadius(3.0);
                        middle.setFillColor(sf::Color::Red);
                        window.draw(middle);
                        */

                        //Draw traffic lights
                        sf::RectangleShape light(sf::Vector2f(18, 2));
                        light.setOrigin(-4, 2);

                        direction d = edge.getDirection();

                        if( (v.getType() == road && v.getEdgesTo().size() > 2 /*) || (v.getType() == building && v.getEdgesTo().size() > 2*/ ) ) { // set to 1 if want to debug
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
            testGraph.update();
            for(auto vehicle : testGraph.getVehicles()) {
                sf::RectangleShape model(sf::Vector2f(vehicle->getWidth(), vehicle->getHeight()));
                model.setTexture(&texmanager.getRef(vehicle->getType()));
                    int i = 0;
                    while(i < speedUp) {
                        //std::cout << "calling move" << std::endl;
                        vehicle -> move(testGraph);
                        i++;
                    }

                Pos got = vehicle -> getPosition();
                direction dir = vehicle->getDirection();
                if(dir == east){
                    dir = west;
                } else if(dir == west){
                    dir = east;
                }
                direction coming = vehicle->getTurningFrom();
                if(coming == east){
                    coming = west;
                } else if(coming == west){
                    coming = east;
                }
                Pos nextPos = vehicle->getNextPosition();
                Pos lastPos = vehicle->getLastPosition();
                Pos curPos = vehicle->getPosition();
                model.setOrigin(6.0, 6.0);
                if(vehicle->turningTo() != dir && vehicle->turningTo() != noDir && (curPos.x)/64 == (nextPos.x)/64 && (curPos.y)/64 == (nextPos.y)/64){
                    Pos anglePosition;
                    int distance = 32 - std::max( abs(curPos.x-nextPos.x) ,  abs(curPos.y-nextPos.y) );

                    if(vehicle->nextTurnIsLeft()){
                         if(dir == north){
                            anglePosition = Pos(curPos.x/64*64, curPos.y/64*64 + 64);
                            Pos drawPosition = vehicle->leftTurnBeginning(anglePosition, distance, dir);
                            model.setPosition(drawPosition.x, drawPosition.y);
                            model.setRotation(-45.0*((distance)/32.0));
                        }
                        if(dir == south){
                            anglePosition = Pos(curPos.x/64*64 + 64, curPos.y/64*64);
                            Pos drawPosition = vehicle->leftTurnBeginning(anglePosition, distance, dir);
                            model.setPosition(drawPosition.x, drawPosition.y);
                            model.setRotation(180 - 45.0*((distance)/32.0));
                        }
                        if(dir == west){
                            anglePosition = Pos(curPos.x/64*64 + 64, curPos.y/64*64 + 64);
                            Pos drawPosition = vehicle->leftTurnBeginning(anglePosition, distance, dir);
                            model.setPosition(drawPosition.x, drawPosition.y);
                            model.setRotation(-90 - 45.0*((distance)/32.0));
                        }
                        if(dir == east){
                            anglePosition = Pos(curPos.x/64*64, curPos.y/64*64);
                            Pos drawPosition = vehicle->leftTurnBeginning(anglePosition, distance, dir);
                            model.setPosition(drawPosition.x, drawPosition.y);
                            model.setRotation(90 - 45.0*((distance)/32.0));
                        }
                    }
                    else{
                        if(dir == north){
                            anglePosition = Pos(curPos.x/64*64 + 64, curPos.y/64*64 + 64);
                            Pos drawPosition = vehicle->rightTurnBeginning(anglePosition, distance, dir);
                            model.setPosition(drawPosition.x, drawPosition.y);
                            model.setRotation(45.0*((distance)/32.0));
                        }
                        if(dir == south){
                            anglePosition = Pos(curPos.x/64*64, curPos.y/64*64);
                            Pos drawPosition = vehicle->rightTurnBeginning(anglePosition, distance, dir);
                            model.setPosition(drawPosition.x, drawPosition.y);
                            model.setRotation(180 + 45.0*((distance)/32.0));
                        }
                        if(dir == east){
                            anglePosition = Pos(curPos.x/64*64 , curPos.y/64*64 + 64);
                            Pos drawPosition = vehicle->rightTurnBeginning(anglePosition, distance, dir);
                            model.setPosition(drawPosition.x, drawPosition.y);
                            model.setRotation(90 + 45.0*((distance)/32.0));
                        }
                        if(dir == west){
                            anglePosition = Pos(curPos.x/64*64 + 64, curPos.y/64*64 );
                            Pos drawPosition = vehicle->rightTurnBeginning(anglePosition, distance, dir);
                            model.setPosition(drawPosition.x, drawPosition.y);
                            model.setRotation(-90 + 45.0*((distance)/32.0));
                        }
                    }

                }
                else if(coming != dir && ( (curPos.x)/64 != (nextPos.x)/64 || (curPos.y)/64 != (nextPos.y)/64 ) ){
                    Pos anglePosition;
                    int distance = std::max( abs(lastPos.x-curPos.x) ,  abs(lastPos.y-curPos.y) );

                    if(vehicle->lastTurnWasLeft()){
                        if(dir == west){
                            anglePosition = Pos( (curPos.x)/64*64, (curPos.y)/64*64 + 64 );
                            Pos drawPosition = vehicle->leftTurnEnd(anglePosition, distance, dir);
                            model.setPosition(drawPosition.x, drawPosition.y);
                            model.setRotation(-45.0*((distance)/32.0) - 45);
                        }
                        if(dir == east){
                            anglePosition = Pos( (curPos.x)/64*64 + 64, (curPos.y)/64*64 );
                            Pos drawPosition = vehicle->leftTurnEnd(anglePosition, distance, dir);
                            model.setPosition(drawPosition.x, drawPosition.y);
                            model.setRotation(180 - 45.0*((distance)/32.0) - 45);
                        }
                        if(dir == south){
                            anglePosition = Pos( (curPos.x)/64*64 + 64, (curPos.y)/64*64 + 64 );
                            Pos drawPosition = vehicle->leftTurnEnd(anglePosition, distance, dir);
                            model.setPosition(drawPosition.x, drawPosition.y);
                            model.setRotation(-90 - 45.0*((distance)/32.0) - 45);
                        }
                        if(dir == north){
                            anglePosition = Pos( (curPos.x)/64*64 , (curPos.y)/64*64 );
                            Pos drawPosition = vehicle->leftTurnEnd(anglePosition, distance, dir);
                            model.setPosition(drawPosition.x, drawPosition.y);
                            model.setRotation(90 - 45.0*((distance)/32.0) - 45);
                        }
                    }
                    else{
                        if(dir == east){
                            anglePosition = Pos( (curPos.x)/64*64 + 64, (curPos.y)/64*64 + 64 );
                            Pos drawPosition = vehicle->rightTurnEnd(anglePosition, distance, dir);
                            model.setPosition(drawPosition.x, drawPosition.y);
                            model.setRotation(45.0*((distance)/32.0) + 45);
                        }
                        if(dir == west){
                            anglePosition = Pos( (curPos.x)/64*64, (curPos.y)/64*64 );
                            Pos drawPosition = vehicle->rightTurnEnd(anglePosition, distance, dir);
                            model.setPosition(drawPosition.x, drawPosition.y);
                            model.setRotation(180 + 45.0*((distance)/32.0) + 45);
                        }
                        if(dir == south){
                            anglePosition = Pos( (curPos.x)/64*64, (curPos.y)/64*64 + 64 );
                            Pos drawPosition = vehicle->rightTurnEnd(anglePosition, distance, dir);
                            model.setPosition(drawPosition.x, drawPosition.y);
                            model.setRotation(90 + 45.0*((distance)/32.0) + 45);
                        }
                        if(dir == north){
                            anglePosition = Pos( (curPos.x)/64*64 + 64, (curPos.y)/64*64 );
                            Pos drawPosition = vehicle->rightTurnEnd(anglePosition, distance, dir);
                            model.setPosition(drawPosition.x, drawPosition.y);
                            model.setRotation(-90 + 45.0*((distance)/32.0) + 45);
                        }
                    }

                }
                else{
                    //set position according to direction
                    if(dir == south){
                        model.setPosition(got.x-16, got.y);
                        model.setRotation(180);
                    }
                    else if(dir == north){
                        model.setPosition(got.x+16, got.y);
                        model.setRotation(0);
                    }
                    else if(dir == east){
                        model.setPosition(got.x, got.y+16);
                        model.setRotation(90);
                    }
                    else if(dir == west){
                        model.setPosition(got.x, got.y-16);
                        model.setRotation(-90);
                    }
                }

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
