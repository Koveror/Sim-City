#include "graph.hpp"

Graph::~Graph() {
    /*for(auto it : vehicles) {
        std::cout << "Deleting vehicles" << std::endl;
        delete it;
    }*/
}

void Graph::addCar(Pos p) {

    std::shared_ptr<Vehicle> c = std::make_shared<Car>();
    //Vehicle* c = new Car;
    c->setPosition(p);
    c->setNextPosition(p);
	vehicles.push_back(c);
    std::cout << "Added car to: (" << p.x << "," << p.y << ")" << std::endl;
}

std::list<std::shared_ptr<Vehicle>>& Graph::getVehicles() {
	return vehicles;
}

int Graph::getSize()
{
    auto size = longitude * latitude;
    return size;
}

int Graph::getSizeX()
{
    return longitude;
}

int Graph::getSizeY()
{
    return latitude;
}

void Graph::addVertices()
{
    for (int j = 0; j < latitude; j++) {
        std::vector<Vertex> row = {};
        vertices.push_back(row);
        for (int i = 0; i < longitude; i++) {
            Vertex v1(i,j, grass);
            std::cout << "--- pushing ---" << std::endl;
            vertices[j].push_back(v1);
            //DEBUG:
            std::cout << "Adding: " << "Grass: " << j << ", " << i << std::endl;
            std::cout << "x: " << vertices[j][i].getPos().x << std::endl;
            std::cout << "y: " << vertices[j][i].getPos().y << std::endl;
        }
    }
    return;
}


void Graph::setVertex(int x, int y, tileType type)
{
    Graph& graph = *this;
    if(y < latitude){
        if(x < longitude){
            vertices[y][x].setType(type);
            if(type == road){

                Pos position1(x,y);
                vertices[y][x].removeEdge(position1);

                if(y > 0 && vertices[y-1][x].getType() == road){
                    Pos position2(x,y-1);
                    vertices[y-1][x].removeEdgesTo(position1);
                    vertices[y-1][x].addEdge(position1, graph, 1);
                    vertices[y][x].addEdge(position2, graph, 1);
                }
                if(y > 0 && vertices[y-1][x].getType() == building){
                    Pos position2(x,y-1);
                    vertices[y-1][x].removeEdgesTo(position1);
                    vertices[y-1][x].addEdge(position1, graph, 1000);
                    vertices[y][x].addEdge(position2, graph, 1000);
                }
                if(y < latitude-1 && vertices[y+1][x].getType() == road){
                    Pos position2(x,y+1);
                    vertices[y+1][x].removeEdgesTo(position1);
                    vertices[y+1][x].addEdge(position1, graph, 1);
                    vertices[y][x].addEdge(position2, graph, 1);
                }
                if(y < latitude-1 && vertices[y+1][x].getType() == building){
                    Pos position2(x,y+1);
                    vertices[y+1][x].removeEdgesTo(position1);
                    vertices[y+1][x].addEdge(position1, graph, 1000);
                    vertices[y][x].addEdge(position2, graph, 1000);
                }
                if(x > 0 && vertices[y][x-1].getType() == road){
                    Pos position2(x-1,y);
                    vertices[y][x-1].removeEdgesTo(position1);
                    vertices[y][x-1].addEdge(position1, graph, 1);
                    vertices[y][x].addEdge(position2, graph, 1);
                }
                if(x > 0 && vertices[y][x-1].getType() == building){
                    Pos position2(x-1,y);
                    vertices[y][x-1].removeEdgesTo(position1);
                    vertices[y][x-1].addEdge(position1, graph, 1000);
                    vertices[y][x].addEdge(position2, graph, 1000);
                }
                if(x < longitude-1 && vertices[y][x+1].getType() == road){
                    Pos position2(x+1,y);
                    vertices[y][x+1].removeEdgesTo(position1);
                    vertices[y][x+1].addEdge(position1, graph, 1);
                    vertices[y][x].addEdge(position2, graph, 1);
                }
                if(x < longitude-1 && vertices[y][x+1].getType() == building){
                    Pos position2(x+1,y);
                    vertices[y][x+1].removeEdgesTo(position1);
                    vertices[y][x+1].addEdge(position1, graph, 1000);
                    vertices[y][x].addEdge(position2, graph, 1000);
                }

                //std::cout << "type is road, check lights..." << std::endl;
                if (vertices[y][x].getEdgesTo().size() >= 3) {
                    vertices[y][x].passable_from[0] = false;
                    vertices[y][x].passable_from[1] = false;
                    vertices[y][x].passable_from[2] = false;
                    vertices[y][x].passable_from[3] = false;
                }

                for (auto neighbor : vertices[y][x].getEdgesTo() ) {
                    auto loc = neighbor.getVertices().second.getIndex();
                    //std::cout << loc.x << ", " << loc.y << std::endl;
                    //std::cout << "check neighbor passable_from... " << ( vertices[loc.y][loc.x].getEdgesTo().size() ) << std::endl;
                    if (vertices[loc.y][loc.x].getEdgesTo().size() >= 3) {
                        //std::cout << "change..." << std::endl;
                        vertices[loc.y][loc.x].passable_from[0] = false;
                        vertices[loc.y][loc.x].passable_from[1] = false;
                        vertices[loc.y][loc.x].passable_from[2] = false;
                        vertices[loc.y][loc.x].passable_from[3] = false;
                    }

                }

            } else if(type == building){
                Pos position1(x,y);
                vertices[y][x].removeEdge(position1);

                if(y > 0 && vertices[y-1][x].getType() == road){
                    Pos position2(x,y-1);
                    vertices[y-1][x].removeEdgesTo(position1);
                    vertices[y-1][x].addEdge(position1, graph, 1000);
                    vertices[y][x].addEdge(position2, graph, 1000);
                }
                if(y > 0 && vertices[y-1][x].getType() == building){
                    Pos position2(x,y-1);
                    vertices[y-1][x].removeEdgesTo(position1);
                }
                if(y < latitude-1 && vertices[y+1][x].getType() == road){
                    Pos position2(x,y+1);
                    vertices[y+1][x].removeEdgesTo(position1);
                    vertices[y+1][x].addEdge(position1, graph, 1000);
                    vertices[y][x].addEdge(position2, graph, 1000);
                }
                if(y < latitude-1 && vertices[y+1][x].getType() == building){
                    Pos position2(x,y+1);
                    vertices[y+1][x].removeEdgesTo(position1);
                }
                if(x > 0 && vertices[y][x-1].getType() == road){
                    Pos position2(x-1,y);
                    vertices[y][x-1].removeEdgesTo(position1);
                    vertices[y][x-1].addEdge(position1, graph, 1000);
                    vertices[y][x].addEdge(position2, graph, 1000);
                }
                if(x > 0 && vertices[y][x-1].getType() == building){
                    Pos position2(x-1,y);
                    vertices[y][x-1].removeEdgesTo(position1);
                }
                if(x < longitude-1 && vertices[y][x+1].getType() == road){
                    Pos position2(x+1,y);
                    vertices[y][x+1].removeEdgesTo(position1);
                    vertices[y][x+1].addEdge(position1, graph, 1000);
                    vertices[y][x].addEdge(position2, graph, 1000);
                }
                if(x < longitude-1 && vertices[y][x+1].getType() == building){
                    Pos position2(x+1,y);
                    vertices[y][x+1].removeEdgesTo(position1);
                }
                vertices[y][x].passable_from[0] = true;
                vertices[y][x].passable_from[1] = true;
                vertices[y][x].passable_from[2] = true;
                vertices[y][x].passable_from[3] = true;

            } else {
                //std::cout << "type is grass, check lights..." << std::endl;
                for (auto neighbor : vertices[y][x].getEdgesTo() ) {
                    auto loc = neighbor.getVertices().second.getIndex();
                    //std::cout << loc.x << ", " << loc.y << std::endl;
                    //std::cout << "check neighbor passable_from... " << ( vertices[loc.y][loc.x].getEdgesTo().size() ) << std::endl;
                    if (vertices[loc.y][loc.x].getEdgesTo().size() == 3) {
                        //std::cout << "change..." << std::endl;
                        vertices[loc.y][loc.x].passable_from[0] = true;
                        vertices[loc.y][loc.x].passable_from[1] = true;
                        vertices[loc.y][loc.x].passable_from[2] = true;
                        vertices[loc.y][loc.x].passable_from[3] = true;
                    }

                }

                Pos position1(x,y);
                vertices[y][x].removeEdge(position1);

                if(y > 0){
                    vertices[y-1][x].removeEdgesTo(position1);
                }
                if(y < latitude-1){
                    vertices[y+1][x].removeEdgesTo(position1);
                }
                if(x > 0){
                    vertices[y][x-1].removeEdgesTo(position1);
                }
                if(x < longitude-1){
                    vertices[y][x+1].removeEdgesTo(position1);
                }
            }
            /*std::cout << "check passable_from... " << ( vertices[y][x].getEdgesTo().size() ) << std::endl;
            if (vertices[y][x].getEdgesTo().size() > 2) {
                vertices[y][x].passable_from[0] = false;
                vertices[y][x].passable_from[1] = false;
                vertices[y][x].passable_from[2] = false;
                vertices[y][x].passable_from[3] = false;
            }*/

            return;
        }
    }
    return;
}

std::vector<std::vector<Vertex>>& Graph::getVertices(){
    return vertices;
}

bool Graph::addVertex(int x, int y)
{
	tileType t = grass;
        Vertex new_vertex(x,y, t);
	vertices[y][x] = new_vertex;
	return true;
}

void Graph::sendVehicle(Pos position){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::exponential_distribution<double> distribution(1.0 / 5.0);
    //std::cout << "gen: " << distribution(generator) << std::endl;
    if(distribution(generator) < 0.00665){
        std::cout << "Send vehicle from: " << "(" << position.x/96 << "," << position.y/96 << ")" << std::endl;
        addCar(position);
    }

//     int summa = 0.0;
//     for(int i = 0; i < 10000000; i++){
//         double number = distribution(generator);
//         if(number < (1.0 / 30.0) ){
//             summa += 1;
//         }
//     }
}

bool Graph::saveGraph(std::string filename) {
    std::string extension = ".txt";
    std::ofstream file;
    file.open(filename+extension);
    for (auto row : vertices) {
        for (auto v : row) {
          file << v.getType();
        }
        file << "\n";
    }
    file.close();
    return true;
}

bool Graph::loadGraph(std::string filename) {
    std::string extension = ".txt";
    std::ifstream file;

    file.open(filename+extension);
    if (!file.is_open()) return false;
    std::string row;

    int y = 0;
    while (!file.eof()) {
        getline(file, row);
        int x = 0;
        for (std::string::iterator c = row.begin(); c != row.end(); ++c) {
            setVertex(x, y, static_cast<tileType>(*c - '0'));
            x++;
        }
        y++;
    }
    file.close();

    return true;
}
