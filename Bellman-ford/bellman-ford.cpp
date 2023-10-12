#include <bits/stdc++.h>

using namespace std;

typedef pair<pair<int, int>, int> Edge;

int bellman_ford(int source, int n, int m, vector<int> &distance, vector<Edge> &edges){
    
    // vector<int> visited(n+1, 0);
    

    distance[source] = 0; 
    
    for (int i = 1; i <= n; i++)
    {
        // cout << "Fazendo " << i << " passo" << endl;
        bool changed = false;
        
        for (auto e : edges)
        {
            
            pair<int, int> vertices = e.first;
            int weight = e.second;
            int src = vertices.first;
            int dst = vertices.second;

            if (distance[src] != INT_MAX && distance[dst] > (distance[src] + weight))
            {
                // cout << "O dist do vértice " << dst << "atual é: " << distance[dst] << ' ';
                changed = true;
                distance[dst] = distance[src] + weight;
                // cout << " mudou para: " << distance[dst] << ' ';
                // cout << weight << ' ' << distance[src] << endl;
            }
        }

        if (!changed) 
        {
            // cout << "Nenhuma alteração feita, parando o algoritmo" << endl;
            return 0;
        }   
    }
    for (auto e : edges)
    {
        pair<int, int> vertices = e.first;
        int weight = e.second;
        int src = vertices.first;
        int dst = vertices.second;

        if (distance[src] != INT_MAX && distance[dst] > (distance[src] + weight))
        {
            cout << "Grafo contém ciclo negativo!" << endl;
            return -1;
        }
    }
    
    return 0;
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
    vector<Edge> arestas(V + 1);
    
    
    for (int i = 0; i < E; i++){
        fin >> a >> b >> cost;
        arestas.push_back({{a, b}, cost});
        arestas.push_back({{b, a}, cost});
    }

    fin.close();

    vector<int> distances(V + 1, INT_MAX);

    int success = bellman_ford(initial, V, E, distances, arestas);

    if (success == -1) return 0;
    
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
