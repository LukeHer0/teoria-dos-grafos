#include <bits/stdc++.h>

using namespace std;

struct compare_edges {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; // Compara o peso das arestas
    }
};

vector<pair<int, int>> prim (int source, int n, vector<vector<pair<int, int>>> &adj, int &total);
void print_command(string command, string description);

int main(int argc, char *argv[])
{
    string input_file = "";
    string output_file = "";
    int source = 1;
    int show_answer = 0;

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
            print_command("-s", "mostra a solução");
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
        else if ( strcmp(argv[i], "-s") == 0) 
        {
            show_answer = 1;
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
    vector<vector<pair<int, int>>> adj(N + 1);

    for (int i = 0; i < m; i++){
        int a, b, wt;
        fin >> a >> b >> wt;
        adj[a].push_back({b, wt});
        adj[b].push_back({a, wt});
    }

    fin.close();

    int minimum_cost = 0;
    vector<pair<int, int>> result = prim(source, N, adj, minimum_cost);

    if (output_file != ""){
        ofstream fout(output_file);
        
        if (!fout)
        {
            cerr << "Não foi possível abrir o arquivo de saída: " << output_file << endl;
            return 1;
        }
        
        if (show_answer)
        {
            for (auto sample : result)
                fout << "(" << sample.second << "," << sample.first << ") ";
        }

        else
        {
            fout << " " << minimum_cost << endl;
        }

        fout.close();
    }

    if(show_answer)
    {
        for (auto sample : result)
            cout << "(" << sample.second << "," << sample.first << ") ";
    }
    
    else
    {
        cout << " " << minimum_cost << endl;
    }

    return 0;
}

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

void print_command(string command, string description)
{
    cout << left << setw(14) << command << ':' << description << endl;
}
