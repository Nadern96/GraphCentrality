#include "Graph.h"
#include <queue>
#include <stack>
#include <functional>
#include<numeric>

#define INF 1e9

Graph::Graph(int num_nodes,int num_edges)
{
    this->num_nodes = num_nodes;
    adj_list.resize(num_nodes);

    this->num_edges = num_edges;
}


Graph::~Graph(void)
{
}

vector<vector<pair<int, int>>> Graph ::  Get_AdjList (void){
    return adj_list;
}

int Graph :: Get_numNodes(void){
    return num_nodes;
}

vector<float> Graph :: Degree_Centrality(void){
    vector <float> Degrees (this->num_nodes);

    for(int i=0 ; i<Degrees.size() ; i++){
        Degrees[i] = this->adj_list[i].size();
    }

    return Degrees;
}

vector<int> Graph :: Dijkstra(int src,vector<vector<pair<int,int> > > adj_list){

    // Create queue
    priority_queue<pair<int, pair<int, int> >,
                   vector<pair<int, pair<int, int>> >,
                   greater<pair<int, pair<int, int> > > >nodes_q;

    // Create d and p arrays
    int n = adj_list.size();
    vector<int> d(n, INF);
    vector<int> p(n, -1);

    nodes_q.push(make_pair(0, make_pair(src, src)));

    while(!nodes_q.empty()){
        pair<int,pair<int, int> > cur_p = nodes_q.top();
        nodes_q.pop();
        int cur_node = cur_p.second.first;
        int cur_prev_node = cur_p.second.second;
        int cur_dis = cur_p.first;

        if (d[cur_node] != INF)
            continue;

        d[cur_node] = cur_dis;
        p[cur_node] = cur_prev_node;

        // Add the nodes connected to current one
        for (int i=0; i< adj_list[cur_node].size();i++)
        {
            int next_node = adj_list[cur_node][i].first;
            int weight = adj_list[cur_node][i].second;
            if (d[next_node] !=INF)
                continue;
            nodes_q.push(make_pair(cur_dis + weight,
                          make_pair(next_node, cur_node)));
        }
    }

    return d;
}

vector<float> Graph :: Closeness_Centrality(void){

    vector <float> CC (this->num_nodes);
    vector<int> d (this->num_nodes);

    for(int i=0 ; i<this->adj_list.size();i++){
        d = Dijkstra(i,this->adj_list);
        CC[i] = float(this->num_nodes - 1)/accumulate(d.begin(),d.end(),0);

    }

    return CC;
}
pair<vector<int>, vector<vector<int>> > Graph :: shortest_distance(int src,
    vector<vector<pair<int,int> > > adj_list){

    // Create queue
    priority_queue<pair<int, pair<int, int> >,
                   vector<pair<int, pair<int, int>> >,
                   greater<pair<int, pair<int, int> > > >nodes_q;

    // Create d and p arrays
    int n = adj_list.size();
    vector<int> d(n, INF);
    vector<vector<int>> p(n,vector<int>(1, -1));

    nodes_q.push(make_pair(0, make_pair(src, src)));

    while(!nodes_q.empty()){
        pair<int,pair<int, int> > cur_p = nodes_q.top();
        nodes_q.pop();
        int cur_node = cur_p.second.first;
        int cur_prev_node = cur_p.second.second;
        int cur_dis = cur_p.first;

        if (d[cur_node] != INF && cur_dis > d[cur_node])
            continue;
        else if (d[cur_node] == INF){
            d[cur_node] = cur_dis;
            p[cur_node][0] = cur_prev_node;
        }
        else{
            p[cur_node].push_back(cur_prev_node);
        }
        // Add the nodes connected to current one
        for (int i=0;
             i< adj_list[cur_node].size();
             i++)
        {
            int next_node = adj_list[cur_node][i].first;
            int weight = adj_list[cur_node][i].second;
            if (d[next_node] != INF && cur_dis > d[next_node])
                continue;
            nodes_q.push(make_pair(cur_dis + weight,
                          make_pair(next_node, cur_node)));
        }
    }

    return make_pair(d, p);
}
vector<vector<int>> Graph :: get_PathS(int src, int des, vector<vector<int>> p){
    int num_paths = p[des].size();
    vector<vector<int>> path_nodes(num_paths);
    int node = des;

    //pushing destination node in the stacksss
    for(int i=0 ; i < num_paths ; i++){
        path_nodes[i].push_back(node);
    }
    int j=0;
    for(int i=0 ; i < num_paths ; i++){
        j=i;
            while(true){
                if(j>=p[node].size()){
                    j--;
                    continue;
                }
                else if(p[node][j] == src || p[node][j] == node){
                    break;
                }
                    node = p[node][j];

                path_nodes[i].push_back(node);
            }

        path_nodes[i].push_back(src);
        node = des;
    }

    return path_nodes;
}

float Graph :: Betweenness_Node  (int node , vector<vector<pair<int,int> > > adj_list){

    pair<vector<int>, vector<vector<int>> > p ;
    vector<vector<int>> previous_node;
    vector<vector<int>> paths ;

    float BC_val=0;
    int found_cnt =0;
    for(int i=0; i<adj_list.size(); i++){

        p = shortest_distance(i, adj_list);
        previous_node = p.second;

        for(int j=i+1 ; j< adj_list.size() ; j++){
            paths = get_PathS(i, j, previous_node);

            for(int k=0 ; k< paths.size(); k++){
                for(int l=1; l<paths[k].size()-1;l++){
                    if(paths[k][l] == node){
                        found_cnt += 1;
                        break;
                    }
                }
            }
            BC_val += found_cnt / float(paths.size());
            found_cnt = 0;
        }

    }
    return BC_val;
}
vector<float> Graph :: Betweenness_Centrality (void){
    vector <float> BC_arr (this->num_nodes);

    for(int i=0 ; i<this->adj_list.size();i++){
        BC_arr[i] = Betweenness_Node(i,adj_list);
    }

    return BC_arr;
}
