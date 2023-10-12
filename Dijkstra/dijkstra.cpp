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

int main(int argc, char *argv[])
{
    string in = "";
    string out = "";
    int initial = 1;

    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-h") == 0){
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            cout << "-i: vértice inicial" << endl;
            
            return 0;
        }
        else if (strcmp(argv[i], "-o") == 0 && i < argc - 1){
            out = argv[++i];
        }
        else if (strcmp(argv[i], "-f") == 0 && i < argc - 1){
            in = argv[++i];
        }
        else if (strcmp(argv[i], "-i") == 0 && i < argc - 1){
            initial = atoi(argv[++i]);
        }
    }

    if (in == ""){
        cerr << "No input file specified. Use the -f parameter." << endl;
        return 1;
    }

    ifstream fin(in);

    if (not fin){
        cerr << "Could not open input file: " << in << endl;
        return 1;
    }

    int V, E;
    fin >> V >> E;

    int a, b, cost;
    vector<vector<pair<int, int>>> arestas(V + 1);

    for (int i = 0; i < E; i++){
        fin >> a >> b >> cost;
        arestas[b].push_back({a, cost});
        arestas[a].push_back({b, cost});
    }

    fin.close();

    vector<int> distances = dijkstra(initial, V, arestas);

    if (not (out == "")){
        ofstream fout(out);
        if (not fout){
            cerr << "Could not open output file: " << out << endl;
            return 1;
        }
        
        for (int i = 1; i <= V; ++i) {
            fout << i << ":" << distances[i] << " ";
        }
        fout << endl;

        fout.close();
    }

    for (int i = 1; i <= V; ++i) {
        cout << i << ":" << distances[i] << " ";
    }
    cout << endl;

    return 0;
}

