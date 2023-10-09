#include <bits/stdc++.h>

using namespace std;

struct compare_paths {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; // Compara o peso dos caminhos
    }
};

vector<int> dijkstra(int source, int n, vector<vector<pair<int, int>>> &adj)
{
    vector<int> distance(n + 1, INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, compare_paths> paths;

    distance[source] = 0;
    paths.push(make_pair(source, distance[source]));

    while(!paths.empty())
    {
        pair<int, int> u = paths.top();
        paths.pop();

        for(pair<int, int> edge : adj[u.first])
        {
            int neighbor = edge.first;
            int weight = edge.second;
            
            if(distance[neighbor] > distance[u.first] + weight)
            {
                distance[neighbor] = distance[u.first] + weight;
                paths.push(make_pair(neighbor, distance[neighbor]));
            }
        }
    }

    return distance;
}
