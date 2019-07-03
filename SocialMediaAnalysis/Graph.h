#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
using namespace std;

class Graph
{
private:
    vector<vector<pair<int, int> > > adj_list;
    int num_nodes , num_edges;

    vector<int> Dijkstra(int src,vector<vector<pair<int,int> > > adj_list);
    pair<vector<int>, vector<vector<int>> > shortest_distance(int src,vector<vector<pair<int,int> > > adj_list);
    vector<vector<int>> get_PathS(int src, int des, vector<vector<int>> p);
    float Betweenness_Node (int node , vector<vector<pair<int,int> > > adj_list);

public:
    Graph(int num_nodes,int num_edges);
    ~Graph(void);
    int Get_numNodes(void);
    vector<vector<pair<int, int> > > Get_AdjList (void);
    vector<float> Degree_Centrality(void);
    vector<float> Closeness_Centrality(void);
    vector<float>  Betweenness_Centrality(void);
    friend Graph * readFile (string path );

};


#endif // GRAPH_H
