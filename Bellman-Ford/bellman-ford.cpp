#include <bits/stdc++.h>

using namespace std;

typedef pair<pair<int, int>, int> Edge;

int bellman_ford(int source, int n, int m, vector<int> &distance, vector<Edge> &edges);
void print_command(string command, string description);

int main(int argc, char *argv[])
{
    string input_file = "";
    string output_file = "";
    int source = 1;

    if (argc == 1)
    {
        cerr << "Nenhum argumento especificado. Digite -h para exibir o help" << endl;
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        int show_help = strcmp(argv[i], "-h") == 0 && i < argc - 1;
        int input_file_exists = strcmp(argv[i], "-f") == 0 && i < argc - 1;
        int output_file_exists = strcmp(argv[i], "-o") == 0 && i < argc - 1;
        int source_exists = strcmp(argv[i], "-i") == 0 && i < argc - 1;


        if (show_help)
        {
            cout << "Help:" << endl;
            print_command("-h", "mostra o help");
            print_command("-o <arquivo>", "redireciona a saida para o arquivo");
            print_command("-f <arquivo>", "indica o arquivo que contém o grafo de entrada");
            print_command("-i", "vértice inicial");
            
            return 0;
        }
        else if (output_file_exists)
        {
            output_file = argv[++i];
        }
        else if (input_file_exists)
        {
            input_file = argv[++i];
        }
        else if (source_exists)
        {
            source = atoi(argv[++i]);
        }
    }


    if (input_file == ""){
        cerr << "Arquivo de entrada não especificado. Use -f <arquivo> ou digite -h para exibir o help" << endl;
        return 1;
    }

    ifstream fin(input_file);

    if (not fin){
        cerr << "Não foi possível abrir o arquivo de entrada: " << input_file << endl;
        return 1;
    }

    int V, E;
    fin >> V >> E;

    int a, b, cost;
    vector<Edge> arestas(V + 1);
    
    
    for (int i = 0; i < E; i++){
        fin >> a >> b >> cost;
        arestas.push_back({{a, b}, cost});
    }

    fin.close();

    vector<int> distances(V + 1, INT_MAX);

    int success = bellman_ford(source, V, E, distances, arestas);

    if (success == -1) return 0;
    
    if (not (output_file == "")){
        ofstream fout(output_file);

        if (not fout)
        {
            cerr << "Não foi possível abrir o arquivo de saída: " << output_file << endl;
            return 1;
        }
        
        for (int i = 1; i <= V; ++i) 
        {
            int shortest_distance = distances[i] == INT_MAX ? -1 : distances[i];
            fout << i << ":" << shortest_distance << " ";
        }
        
        fout << endl;

        fout.close();
    }
    
    for (int i = 1; i <= V; ++i) 
    {
        int shortest_distance = distances[i] == INT_MAX ? -1 : distances[i];
        
        cout << i << ":" << shortest_distance << " ";
    }
    cout << endl;


    return 0;
}

int bellman_ford(int source, int n, int m, vector<int> &distance, vector<Edge> &edges)
{   

    distance[source] = 0; 
    
    for (int i = 1; i < n; i++)
    {
        bool changed = false;
        
        for (auto e : edges)
        {
            pair<int, int> vertices = e.first;
            int weight = e.second;
            int src = vertices.first;
            int dst = vertices.second;

            if (distance[src] != INT_MAX && distance[dst] > (distance[src] + weight))
            {
                changed = true;
                distance[dst] = distance[src] + weight;
            }
        }

        if (!changed) 
        {
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

void print_command(string command, string description)
{
    cout << left << setw(14) << command << ':' << description << endl;
}
