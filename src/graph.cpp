#include "graph.hpp"

/*Graph::~Graph() {
    for(auto it : vehicles) {
        std::cout << "Deleting vehicles" << std::endl;
        it.reset();
    }
}*/

void Graph::addVehicle(Pos p) {

    //chooose random building for destination
    std::vector<Pos> destinations = {};
    for(auto row : vertices){
        for(auto vertex : row) {
            if(vertex.getType() == building){
                destinations.push_back(vertex.getPos());
            }
        }
    }
    if (destinations.empty()) return; // No destinations or destination is self, don't add car

    int i = rand() % destinations.size();
    //std::cout << "DEBUG dest: " << destinations[i].x << ", " << destinations[i].y << std::endl;
    //std::cout << "DEBUG p: " << p.x << ", " << p.y << std::endl;
    if (destinations[i] == p) return; // Destination is same as self, don't add car

    int j = rand() % 3;
    std::shared_ptr<Vehicle> c;
    
    if (j == 0) {
        c = std::make_shared<Car>();
    }
    else if (j == 1) {
        c = std::make_shared<Truck>();
    }
    else {
        c = std::make_shared<Bike>();
    }
    //std::shared_ptr<Vehicle> c = std::make_shared<Car>();
    //Vehicle* c = new Car;
    c->setPosition(p);
    c->setNextPosition(p);
    c->setDestination( destinations[i] );

    int sourceX = p.x / 64;
    int sourceY = p.y / 64;
    Vertex source = getVertices()[sourceY][sourceX];

    Pos destination = c->getDestination();
    int targetX = destination.x / 64;
    int targetY = destination.y / 64;
    Vertex target = getVertices()[targetY][targetX];

    auto route = getPath(source, target);
    c->setPath(route);

    vehicles.push_back(c);
    //std::cout << "Added car to: (" << p.x << "," << p.y << ")" << std::endl;
    //std::cout << "Vehicles size: " << vehicles.size() << std::endl;

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
            //std::cout << "--- pushing ---" << std::endl;
            vertices[j].push_back(v1);
            //DEBUG:
            //std::cout << "Adding: " << "Grass: " << j << ", " << i << std::endl;
            //std::cout << "x: " << vertices[j][i].getPos().x << std::endl;
            //std::cout << "y: " << vertices[j][i].getPos().y << std::endl;
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

void Graph::sendVehicle(Pos position, int multipler, float rate){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::exponential_distribution<double> distribution(1.0 / 5.0);
    //std::cout << "gen: " << distribution(generator) << std::endl;
    if(distribution(generator) < 0.00665 * multipler * rate){
        //std::cout << "Send vehicle from: " << "(" << position.x/64 << "," << position.y/64 << ")" << std::endl; //96?
        addVehicle(position);
    }

}

bool Graph::saveGraph(std::string filename) {
    if (filename == "-1") {
        std::cout << "Saving cancelled." << std::endl;
        return false;
    }
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
    std::cout << "Save success!" << std::endl;
    return true;
}

bool Graph::loadGraph(std::string filename) {
    if (filename == "-1") {
        std::cout << "Loading cancelled." << std::endl;
        return false;
    }
    std::string extension = ".txt";
    std::ifstream file;

    file.open(filename+extension);
    if (!file.is_open()) {
        std::cerr << "Load failed." << std::endl;
        return false;
    }
    vehicles.clear();
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
    std::cout << "Load success!" << std::endl;
    return true;
}

std::vector<Edge> Graph::getPath(Vertex source, Vertex target) {
    class CompareWeight
    {
    public:
        bool operator()(std::pair<Vertex,int> n1,std::pair<Vertex,int> n2) { // (pair: vertex, int)
            return n1.second>n2.second;
        }
    };

    int INF = std::numeric_limits<int>::max();
    int Y = getSizeY();
    int X = getSizeX();
    std::vector<std::vector<int>> visited(Y, std::vector<int>(X, false));
    std::vector<std::vector<int>> dist(Y, std::vector<int>(X, INF)); //set all dist values to INF
    std::vector<std::vector<std::pair<int,int>>> prev(Y, std::vector<std::pair<int,int>>(X, std::make_pair(-1, -1)));
    Pos s = source.getIndex();
    dist[s.y][s.x] = 0;
    Vertex start = getVertices()[s.y][s.x];

    std::priority_queue<std::pair<Vertex,int>,std::vector<std::pair<Vertex,int>>,CompareWeight> Q;

    Q.push(std::make_pair(start, dist[source.getIndex().y][source.getIndex().x]));
    
    while (!Q.empty()) {
        Vertex u = Q.top().first;
        visited[u.getIndex().y][u.getIndex().x] = true;

        Q.pop();

        ///If we find the target
        if (u == target) {

            auto route = std::vector<std::pair<int,int>>();
            auto routeEdges = std::vector<Edge>();
            std::pair<int,int> u = std::make_pair(target.getIndex().y, target.getIndex().x);

            while (prev[u.first][u.second] != std::pair<int,int>(-1,-1)) {

                Vertex temp = getVertices()[u.first][u.second];
                Edge tempEdge = temp.getSingleEdge(prev[u.first][u.second]);
                route.push_back(u);
                routeEdges.push_back(tempEdge);
                u = prev[u.first][u.second];

            }
            route.push_back(u);
            //std::cout << "Route last: " << u.first << ", " << u.second << std::endl;
            std::reverse(std::begin(route),std::end(route));
            std::reverse(std::begin(routeEdges),std::end(routeEdges));
            //return route;
            for (auto& e : routeEdges) {
                e.swapVertices();
            }
            return routeEdges;
        }

        std::vector<Edge> neighbors = u.getEdgesTo();

        for (Edge &edge : neighbors) {
            auto v_pos = edge.getVertices().second.getIndex(); ///Bug here?
            Vertex v = getVertices()[v_pos.y][v_pos.x];
            if (!visited[v.getIndex().y][v.getIndex().x]) {
                int alt = dist[u.getIndex().y][u.getIndex().x] + edge.getWeight();
                if (alt < dist[v.getIndex().y][v.getIndex().x]) {
                    dist[v.getIndex().y][v.getIndex().x] = alt;
                    prev[v.getIndex().y][v.getIndex().x] = std::make_pair(u.getIndex().y,u.getIndex().x);
                }
                Q.push(std::make_pair(v, dist[v.getIndex().y][v.getIndex().x]));
            }

        }
    }

    ///No suitable route has been found, returning empty route
    return std::vector<Edge>();
}
void Graph::setRoutes() {
    for(auto it = vehicles.begin(); it != vehicles.end(); it++) {

        Pos CurrentPosition = (*it)->getPosition();

        int sourceX = CurrentPosition.x / 64;
        int sourceY = CurrentPosition.y / 64;
        Vertex source = getVertices()[sourceY][sourceX];

        Pos destination = (*it)->getDestination();
        int targetX = destination.x / 64;
        int targetY = destination.y / 64;
        Vertex target = getVertices()[targetY][targetX];

        auto route = getPath(source, target);
        (*it)->setPath(route);

    }
}

void Graph::update() {
    for(auto it = vehicles.begin(); it != vehicles.end(); ) {

    //for(auto vehicle : vehicles) {
        //std::cout << "Car path: " << std::endl;
        Pos CurrentPosition = (*it)->getPosition();

        int sourceX = CurrentPosition.x / 64;
        int sourceY = CurrentPosition.y / 64;
        Vertex source = getVertices()[sourceY][sourceX];

        Pos destination = (*it)->getDestination();
        int targetX = destination.x / 64;
        int targetY = destination.y / 64;
        Vertex target = getVertices()[targetY][targetX];

        auto route = (*it)->getPath();
        if ((*it)->atDestination()) {
            it = vehicles.erase(it);
        } else {
            ++it;
        }

    }
}

void Graph::updateAfterSetVertex() {
    for(auto it = vehicles.begin(); it != vehicles.end(); ) {

    //for(auto vehicle : vehicles) {
        //std::cout << "Car path: " << std::endl;
        Pos CurrentPosition = (*it)->getPosition();

        int sourceX = CurrentPosition.x / 64;
        int sourceY = CurrentPosition.y / 64;
        Vertex source = getVertices()[sourceY][sourceX];

        Pos destination = (*it)->getDestination();
        int targetX = destination.x / 64;
        int targetY = destination.y / 64;
        Vertex target = getVertices()[targetY][targetX];

        auto route = (*it)->getPath();
        if (route.empty()) {
            it = vehicles.erase(it);
        } else {
            ++it;
        }

    }
}
