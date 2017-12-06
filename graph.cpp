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
