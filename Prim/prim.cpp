#include <bits/stdc++.h>

using namespace std;

struct compare_edges {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; // Compara o peso das arestas
    }
};

vector<pair<int, int>> prim (int source, int n, vector<vector<pair<int, int>>> &adj, int &total)
{
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

int main(int argc, char *argv[])
{
    string in = "";
    string out = "";
    bool ans = false;
    int init = 1;

    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-h") == 0){
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            cout << "-s: mostra a solução (em ordem crescente)" << endl;
            cout << "-i: vértice inicial (para o algoritmo de Prim)" << endl;
            return 0;
        }
        else if (strcmp(argv[i], "-o") == 0 && i < argc - 1){
            out = argv[++i];
        }
        else if (strcmp(argv[i], "-f") == 0 && i < argc - 1){
            in = argv[++i];
        }
        else if (strcmp(argv[i], "-s") == 0){
            ans = true;
        }
        else if (strcmp(argv[i], "-i") == 0 && i < argc - 1){
            init = atoi(argv[++i]);
        }
    }

    if (in == ""){
        cerr << "No input file specified. Use the -f parameter." << endl;
        return 1;
    }

    ifstream fin(in);
    if (!fin){
        cerr << "Could not open input file: " << in << endl;
        return 1;
    }

    int N, m;
    fin >> N >> m;
    vector<vector<pair<int, int>>> adj(N + 1);

    for (int i = 0; i < m; i++){
        int a, b, wt;
        fin >> a >> b >> wt;
        adj[a].push_back({b, wt});
        adj[b].push_back({a, wt});
    }

    fin.close();

    int minimum_cost = 0;
    vector<pair<int, int>> result = prim(init, N, adj, minimum_cost);

    if (!(out == "")){
        ofstream fout(out);
        if (!fout){
            cerr << "Could not open output file: " << out << endl;
            return 1;
        }
        if (ans){
            for (auto sample : result)
                fout << "(" << sample.second << "," << sample.first << ") ";
        }
        else{
            fout << " " << minimum_cost << endl;
        }
        fout.close();
    }

    if(ans){
        for (auto sample : result)
            cout << "(" << sample.second << "," << sample.first << ") ";
    }
    else{
        cout << " " << minimum_cost << endl;
    }

    return 0;
}
