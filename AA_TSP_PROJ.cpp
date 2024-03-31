#include <bits/stdc++.h>
using namespace std;
const int V=5;
int minimum_key(int key[], bool mstSet[]) 
{ 
    int min = INT_MAX, min_index; 
 
    for (int v = 0; v < V; v++) 
        if (mstSet[v] == false && key[v] < min) 
            min = key[v], min_index = v; 
 
    return min_index; 
} 
 
vector<vector<int>> MST(int parent[], int graph[V][V]) 
{ 
    vector<vector<int>> v;
    for (int i = 1; i < V; i++) 
    {
        vector<int> p;
        p.push_back(parent[i]);
        p.push_back(i);
        v.push_back(p);
        p.clear();
    }
    return v;  
} 
 
// getting the Minimum Spanning Tree from the given graph
// using Prim's Algorithm
vector<vector<int>> primMST(int graph[V][V]) 
{ 
    int parent[V]; 
    int key[V];

    // to keep track of vertices already in MST 
    bool mstSet[V]; 

    // initializing key value to INFINITE & false for all mstSet
    for (int i = 0; i < V; i++) 
        key[i] = INT_MAX, mstSet[i] = false; 

    // picking up the first vertex and assigning it to 0
    key[0] = 0; 
    parent[0] = -1; 
    for (int count = 0; count < V - 1; count++)
    { 
        // checking and updating values wrt minimum key
        int u = minimum_key(key, mstSet); 
        mstSet[u] = true; 
        for (int v = 0; v < V; v++) 
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) 
                parent[v] = u, key[v] = graph[u][v]; 
    } 
    vector<vector<int>> v;
    v = MST(parent, graph);
    return v; 
} 
vector<int> final_ans;// Dynamic array to store the final answer
// getting the preorder walk of the MST using DFS
void DFS(int** edges_list,int num_nodes,int starting_vertex,bool* visited_nodes){
    final_ans.push_back(starting_vertex);
    visited_nodes[starting_vertex] = true;
    for(int i=0;i<num_nodes;i++){
        if(i==starting_vertex) continue;
    
        if(edges_list[starting_vertex][i]==1){
            if(visited_nodes[i]) continue;
            DFS(edges_list,num_nodes,i,visited_nodes);
        }
    }
}
int main() {
	cout<<"AA PROJECT: TSP USING 2-APROXIMATION :"<<endl;
	cout<<"OUTPUT :"<<endl;
    int graph[V][V] = { { 0, 10, 15, 40, 20 }, 
                        { 10, 0, 35, 15, 12 }, 
                        { 15, 35, 0, 25, 25 }, 
                        { 40, 15, 25, 0, 30 },
                        { 20, 13, 25, 30, 0 } }; 
 
    vector<vector<int>> v;
    v = primMST(graph);
    int** edges_list = new int*[V];
    for(int i=0;i<V;i++){
        edges_list[i] = new int[V];
        for(int j=0;j<V;j++){
            edges_list[i][j] = 0;
        }
    }
    // setting up MST as adjacency matrix
    for(int i=0;i<v.size();i++){
        int first_node = v[i][0];
        int second_node = v[i][1];
        edges_list[first_node][second_node] = 1;
        edges_list[second_node][first_node] = 1;
    }
    bool* visited_nodes = new bool[V];
    for(int i=0;i<V;i++)
        visited_nodes[i] = false;
    DFS(edges_list,V,0,visited_nodes);
    
    final_ans.push_back(final_ans[0]);
    cout << "TSP Path: ";
    int tsp_cost = 0;
    for(int i=0;i<final_ans.size();i++){
        cout << final_ans[i] << "->";
        tsp_cost += graph[final_ans[i]][final_ans[i+1]];
    }
    cout << endl;
    cout << "TSP Cost: " << tsp_cost << endl;
    return 0; 
} 

