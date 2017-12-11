#include "graph.h"
#include <QDebug>

Graph::Graph(std::vector<QString> stadiums)
{
    this->stadiums = stadiums;
    this->SIZE = stadiums.size();
    this->adj = new edgeVec[SIZE];
    createMap();
    createAdjList();
}

void Graph::createMap() {
    for(uint i = 0; i < this->stadiums.size(); ++i) {
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
//        qDebug() << "Vertex " << stadiums[i] << "\n";
//        for(int j = 0; j < adj[i].size(); j++) {
//            qDebug() << stadiums[adj[i][j].first] << "\t(" << adj[i][j].second << ")\n";
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
    return -1; // error
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


int Graph::MST(std::vector<intPair> *route) {
    int totalDistance = 0;
    int start = 0;

    // min heap
    std::priority_queue<intPair, std::vector<intPair>, std::greater<intPair> > pq;

    // init all keys to oo
    std::vector<int> key(this->SIZE, this->oo);

    // init all parent to -1
    std::vector<int> parent(this->SIZE, -1);

    // keep track of vertices in MST
    std::vector<bool> inMST(this->SIZE, false);

    // insert start into pq and set init key to 0
    pq.push(std::make_pair(0, start));
    key[start] = 0;

    int u;
    while(!pq.empty()) {
        u = pq.top().second;	// min key vertex label
        pq.pop();

        inMST[u] = true;

        std::vector< intPair >::iterator i;
        int v, weight;
        for(i = adj[u].begin(); i != adj[u].end(); ++i) {
            // get vertex label and weight of current adjacent vertex
            v = i->first;
            weight = i->second;

            // if v is not in MST and weight of (u,v) is smaller
            // than the current key of v
            if(inMST[v] == false && key[v] > weight) {
                // update key of v
                key[v] = weight;
                pq.push(std::make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }

    // Build MST edges using parent array and calc total distance
    // std::vector< intPair >::iterator pos;
    for (int i = 1; i < this->SIZE; ++i) {
        for(auto pos = adj[i].begin(); pos != adj[i].end(); ++pos) {
            if(pos->first == parent[i]) {
                totalDistance += pos->second;
                break;
            }
        }

        route->push_back(std::make_pair(parent[i], i));
    }
    return totalDistance;
}

int Graph::BFS(QString startV, std::vector<QString> *route) {
    int totalDistance = 0;
    int start = stadiumToInt[startV];

    // return vector
    std::vector<int> bfs_order;

    // array for visted vertices
    bool *visted = new bool[this->SIZE];
    // set all vertices to not-visted
    for(int i = 0; i < this->SIZE; i++) {
        visted[i] = false;
    }

    // create queue
    std::list<int> queue;

    // starting node is visted and enqueued
    visted[start] = true;
    queue.push_back(start);

    // iterator to visit adjacent vertices
    std::vector< std::pair<int, int> >::iterator i;
    while(!queue.empty()) {
        // print when dequeing
        start = queue.front();
        bfs_order.push_back(start);
        queue.pop_front();

        // visit all adjacent nodes of vertex start.
        // mark visited, and enqueue.
        for(i = this->adj[start].begin(); i != this->adj[start].end(); ++i) {
            if(!visted[i->first])
            {
                // update distance
                totalDistance += i->second;
                visted[i->first] = true;
                queue.push_back(i->first);
            }
        }
    }
    for(auto v = bfs_order.begin(); v != bfs_order.end(); ++v) {
        route->push_back(stadiums[*v]);
    }
    return totalDistance;
}

int Graph::DFS(QString startV, std::vector<QString> *route) {
    int start = stadiumToInt[startV];
    int distance = 0;

    // return vec
    std::vector<int> dfs_order;

    // array for visted vertices
    bool *visited = new bool[this->SIZE];
    // set all vertices to not-visted
    for(int i = 0; i < this->SIZE; i++) {
        visited[i] = false;
    }

    this->recurDFS(start, visited, dfs_order, 0, distance);

    for(auto i = dfs_order.begin(); i != dfs_order.end(); ++i) {
        route->push_back(stadiums[*i]);
    }
    return distance;
}

void Graph::recurDFS(int start, bool *visited, std::vector<int> &order, int dist, int &totalDistance) {
    visited[start] = true;
    order.push_back(start);
    totalDistance += dist;

    // Recur for all the vertices adjacent
    // to this vertex
    std::vector< std::pair<int, int> >::iterator i;
    for (i = this->adj[start].begin(); i != this->adj[start].end(); ++i)
        if (!visited[i->first])
            this->recurDFS(i->first, visited, order, i->second, totalDistance);
}
















