#include <bits/stdc++.h>
using namespace std;
const int  V =5;
int travllingSalesmanProblem(int graph[][V], int s){
    vector<int> vertex;
    for (int i = 0; i < V; i++)
        if (i != s)
            vertex.push_back(i);

    int min_path = INT_MAX;
    do {
        int current_pathweight = 0;
        int k = s;
        for (int i = 0; i < vertex.size(); i++) {
            current_pathweight += graph[k][vertex[i]];
            k = vertex[i];
        }
        current_pathweight += graph[k][s];
        min_path = min(min_path, current_pathweight);
    } while (next_permutation(vertex.begin(), vertex.end()));

    return min_path;
}

int main(){
    int graph[][V] = { { 0, 10, 18, 40, 20 }, 
                        { 10, 0, 35, 15, 12 }, 
                        { 18, 35, 0, 25, 25 }, 
                        { 40, 15, 25, 0, 30 },
                        { 20, 13, 25, 30, 0 }};
    int s = 0;
    cout << travllingSalesmanProblem(graph, s) << endl;
    return 0;
}

