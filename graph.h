#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <QSqlQuery>
#include "database.h"


// Edge
typedef std::pair<int, int> intPair;
// Vector of Edges
typedef std::vector< intPair > edgeVec;


/** Graph
 * Undirected Graph implemented using adjacency list
 */
class Graph
{
public:
    /**
     * @brief Graph
     * @param stadiums
     * creates graph based on stadiums passed in
     */
    Graph(std::vector<QString> stadiums);

    /**
     * @brief Add Edge
     * @param vertex 1, vertex 2, edge weight
     * @return void
     * @abstract adds edge from p1 to p2.
     */
    void addEdge(int v1, int v2, int weight);

    /**
     * @brief Dijkstra
     * @param starting vertex, target vertex, empty vector<int>* to
     *        store route.
     * @return total distance traveled
     */
    int dijkstra(int start, int target, std::vector<int> *route);


    /**
     * @brief MST
     * @param empty edge vector
     * @return total cost of Minimum Spanning Tree
     */
    int MST(std::vector< intPair > *route);



private:
    // sorts edges
    void sortAdjEdges();

    // recursively builds shortest path from parent array
    void buildRoute(int parent[],
                    int vertex,
                    int startVertex,
                    std::vector<int> *route);

    // creates stadiumToInt map from stadiums passed into contructor
    void createMap();

    // creates adjacency list by query DB
    void createAdjList();

    // number of vertices
    int SIZE;

    // infinity
    int oo = ((1LL<<31)-1);

    // adjacency list
    edgeVec *adj;

    std::map<QString, int> stadiumToInt;

    std::vector<QString> stadiums;



};

#endif // GRAPH_H
