#include <bits/stdc++.h>

using namespace std;

struct compare_edges {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; // Compara o peso das arestas
    }
};

vector<pair<int, int>> prim (int n, vector<vector<pair<int, int>>> &adj, int &total)
{
    int source = 1;
    
    vector<bool> visited (n + 1, false);
    vector<int> cost(n + 1, INT_MAX);
    vector<int> prev(n + 1, -1);
    vector<pair<int,int>> mst;
    priority_queue<pair<int,int>, vector<pair<int,int>>, compare_edges> known_edges;

    cost[source] = 0;
    visited[source] = true;
    known_edges.push(make_pair(source, cost[source]));

    while(!known_edges.empty())
    {
        pair<int, int> v = known_edges.top();
        known_edges.pop();
        visited[v.first] = true;
        for (pair<int, int> edge : adj[v.first])
        {
            int neighbor = edge.first;
            int weight = edge.second;
            
            if(visited[neighbor] == false && weight < cost[neighbor])
            {
                prev[neighbor] = v.first;
                cost[neighbor] = weight;
                known_edges.push({neighbor, weight});
            }
        }

    }
    for(int i = 2; i <= n; i++)
    {
        mst.push_back(make_pair(i, prev[i]));
        total += cost[i];
    }

    return mst;

}

int main()
{
    int n, m;
    int total = 0;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n + 1);

    for(int i = 0; i < m; i++)
    {
        int u, v, weight;
        cin >> u >> v >> weight;
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }
    
    for(auto i : prim(n, adj, total))
    {
        cout<<'('<<i.first<<", "<<i.second<<") ";
    }
    cout<<endl;
    cout<<total<<endl;
    
    return 0;
}
