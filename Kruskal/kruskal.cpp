#include <bits/stdc++.h>

using namespace std;


typedef pair<pair<int, int>, int> Edge;

struct compare_edges 
{
    bool operator()(const Edge& a, const Edge& b) {
        return a.second > b.second; // Compara o peso das arestas
    }
};

typedef priority_queue<Edge, vector<Edge>, compare_edges>  Queue_Edges; 

int find(vector <int> &father, int vertex);
vector<pair<int, int>> kruskal (int n, Queue_Edges &edges, int &total);
void print_command(string command, string description);

int main(int argc, char *argv[])
{
    string input_file = "";
    string output_file = "";
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
        

        if (show_help)
        {
            cout << "Help:" << endl;
            print_command("-h", "mostra o help");
            print_command("-o <arquivo>", "redireciona a saida para o arquivo");
            print_command("-f <arquivo>", "indica o arquivo que contém o grafo de entrada");
            print_command("-s", "mostra a solução");
            
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
    Queue_Edges adj;

    
    for (int i = 1; i <= m; i++)
    {
        int a, b, wt;
        fin >> a >> b >> wt;
        adj.push({{a, b}, wt});
    }

    fin.close();

    int total = 0;
    
    vector<pair<int, int>> vertex = kruskal(N, adj, total);

    if (output_file != ""){
        ofstream fout(output_file);

        if (!fout)
        {
            cerr << "Não foi possível abrir o arquivo de saída: " << output_file << endl;
            return 1;
        }

        if (show_answer)
        {
            for (auto sample : vertex)
                fout << "(" << sample.second << "," << sample.first << ") ";
        }
        
        else
        {
            fout << " " << total<< endl;
        }
        
        fout.close();
    }

    if(show_answer)
    {
        for (auto sample : vertex)
            cout << "(" << sample.second << "," << sample.first << ") ";
    }
    
    else
    {
        cout << " " << total << endl;
    }
        
    return 0;
}

int find(vector <int> &father, int vertex)
{
    if (father[vertex] != vertex)
    {   
        father[vertex] = find(father, father[vertex]);
    } 

    return father[vertex];
}

void union_find(vector<int> &father, vector<int> &rank, int x, int y)
{
    
    if(rank[x] >= rank[y])
    {
    
        father[y] = x;
        if (rank[x] == rank[y])
        {
            rank[x]++;
        }
    }

    else 
    {
        father[x] = y;
    }
}

vector<pair<int, int>> kruskal (int n, Queue_Edges &edges, int &total)
{
    vector<pair<int, int>> tree;
    vector <int> father(n + 1);
    vector <int> rank (n + 1, 0);
    
    for (int i = 1; i <= n; i++) // make-set
    {
        father[i] = i;
    }
    
    while(!edges.empty())
    {
        auto e = edges.top();
        edges.pop();

        auto vertices = e.first; 
        
        int father_x = find(father, vertices.first);
        int father_y = find(father, vertices.second);
        
        if (father_x != father_y)
        {
            tree.push_back({vertices.first, vertices.second});
            total += e.second;
            union_find(father, rank, father_x, father_y);
        }
    }

    return tree;
}


void print_command(string command, string description)
{
    cout << left << setw(14) << command << ':' << description << endl;
}