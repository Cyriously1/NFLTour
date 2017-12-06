#include "graph.h"

Graph::Graph(std::vector<QString> stadiums)
{
    this->stadiums = stadiums;
    this->SIZE = stadiums.size();
    this->adj = new edgeVec[SIZE];
    createMap();
    createAdjList();
}

void Graph::createMap() {
    for(uint i = 0; i < this->stadiums.size(); i++) {
        this->stadiumToInt[this->stadiums.at(i)] = i;
    }
}

void Graph::createAdjList() {
    QSqlQuery query = Database::getInstance()->getAllDistances();

    QString beg, end;
    int dist;
    while(query.next()) {
        beg = query.value(0).toString();
        end = query.value(1).toString();
        dist = query.value(2).toInt();

        if(stadiumToInt.find(beg) != stadiumToInt.end() &&
           stadiumToInt.find(end) != stadiumToInt.end())
        {
            adj[stadiumToInt[beg]].push_back(std::make_pair(stadiumToInt[end], dist));
        }

    }

    sortAdjEdges();

    // uncomment to output adjacency list after its birth

//    for(int i = 0; i < this->SIZE; i++) {
//        qDebug() << "Vertex " << i << "\n";
//        for(int j = 0; j < adj[i].size(); j++) {
//            qDebug() << adj[i][j].first << "\t(" << adj[i][j].second << ")\n";
//        }
//        qDebug() << "---------------";
//    }
}

// Sort adjacent edges by weight
void Graph::sortAdjEdges() {
    for(int i = 0; i < this->SIZE; i++) {
        std::sort(adj[i].begin(), adj[i].end(),
        // sort by second value
         [](auto &a, auto &b) {
            return a.second < b.second;
         });
    }
}

int Graph::dijkstra(QString startV, QString targetV, std::vector<QString> *route) {
    int start, target;

    start = stadiumToInt[startV];
    target = stadiumToInt[targetV];

    // min heap
    std::priority_queue<intPair, std::vector<intPair>, std::greater<intPair> > pq;

    // unknown distances from start to target (initially oo)
    std::vector<int> dist(this->SIZE, this->oo);

    // insert start into pq and set distance to 0
    // -- WARNING --
    // *first is distance
    // *second is label
    // bcuz min heap compares first of pair
    pq.push(std::make_pair(0, start));
    dist[start] = 0;

    // create vertex parent array & init to all 0's
    int parent[this->SIZE];
    for (int i = 0; i < this->SIZE; ++i)
    {
        parent[i] = 0;
    }

    while(!pq.empty()) {
       // second is the label
       int u = pq.top().second;
       pq.pop();

       // reached target
       if(u == target) {
           std::vector<int> *routeNums = new std::vector<int>;
           buildRoute(parent, u, start, routeNums);

           // build route vector
           for(uint i = 0; i < routeNums->size(); i++) {
               route->push_back(stadiums.at(routeNums->at(i)));
           }

           return dist[u];
       }

       //used to get all adj vertices of a vertex
       std::vector< intPair >::iterator i;
       int v, weight;
       for(i = adj[u].begin(); i != adj[u].end(); ++i) {
           // get vertex label and weight of current adjacent vertex
           v = i->first;
           weight = i->second;

           if(dist[v] > dist[u] + weight) {
               // update distance value ( found shorter path )
               dist[v] = dist[u] + weight;
               pq.push(std::make_pair(dist[v], v));
               parent[v] = u;
           }
       }

    }
    return -1;
}

void Graph::buildRoute(int parent[], int vertex, int startVertex, std::vector<int> *route) {
    if(vertex == startVertex) {
        // reached start vertex
        route->push_back(startVertex);
    } else if(parent[vertex] == 0) {
        // current vertex has no parent
        route->push_back(vertex);
    } else {
        // go for current vertex's parent
        buildRoute(parent, parent[vertex], startVertex, route);
        route->push_back(vertex);
    }
}
