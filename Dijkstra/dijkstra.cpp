#include <bits/stdc++.h>

using namespace std;

struct compare_paths 
{
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) 
    {
        return a.second > b.second; // Compara o peso dos caminhos
    }
};

vector<int> dijkstra(int source, int n, vector<vector<pair<int, int>>> &adj, vector<int> &visited);
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

    if (input_file == "")
    {
        cerr << "Arquivo de entrada não especificado. Use -f <arquivo> ou digite -h para exibir o help" << endl;
        return 1;
    }

    ifstream fin(input_file);

    if (not fin)
    {
        cerr << "Não foi possível abrir o arquivo de entrada: " << input_file << endl;
        return 1;
    }

    int N, m;
    fin >> N >> m;

    int a, b, cost;
    vector<vector<pair<int, int>>> adj(N + 1);
    vector<int> visited(N + 1, 0);

    for (int i = 0; i < m; i++)
    {
        fin >> a >> b >> cost;
        adj[b].push_back({a, cost});
        adj[a].push_back({b, cost});
    }

    fin.close();

    vector<int> distances = dijkstra(source, N, adj, visited);

    if (output_file != "")
    {
        ofstream fout(output_file);
        
        if (not fout)
        {
            cerr << "Não foi possível abrir o arquivo de saída: " << output_file << endl;
            return 1;
        }
        
        for (int i = 1; i <= N; ++i) 
        {
            fout << i << ":" << distances[i] << " ";
        }
        
        fout << endl;

        fout.close();
    }

    for (int i = 1; i <= N; ++i) 
    {
        int short_distance = visited[i] == 1 ? distances[i] : -1;
        
        cout << i << ":" << short_distance << " ";
    }
    cout << endl;

    return 0;
}

vector<int> dijkstra(int source, int n, vector<vector<pair<int, int>>> &adj, vector<int> &visited)
{
    vector<int> distance(n + 1, INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, compare_paths> paths;

    distance[source] = 0;
    paths.push(make_pair(source, distance[source]));

    while(!paths.empty())
    {
        pair<int, int> u = paths.top();
        paths.pop();
        visited[u.first] = 1;

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

void print_command(string command, string description)
{
    cout << left << setw(14) << command << ':' << description << endl;
}