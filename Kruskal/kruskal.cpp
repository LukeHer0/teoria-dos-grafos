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

int main(int argc, char *argv[])
{
    string input_file = "";
    string output_file = "";
    bool ans = false;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            cout << "-s: mostra a solução (em ordem crescente)" << endl;
            return 0;
        }
        else if (strcmp(argv[i], "-o") == 0 && i < argc - 1)
        {
            output_file = argv[++i];
        }
        else if (strcmp(argv[i], "-f") == 0 && i < argc - 1)
        {
            input_file = argv[++i];
        }
        else if (strcmp(argv[i], "-s") == 0)
        {
            ans = true;
        }
    }

    if (input_file == "")
    {
        cerr << "No input file specified. Use the -f parameter." << endl;
        return 1;
    }

    ifstream fin(input_file);
    if (!fin)
    {
        cerr << "Could not open input file: " << input_file << endl;
        return 1;
    }


    int N, m;
    fin >> N >> m;
    Queue_Edges arestas;

    int a, b, wt;
    for (int i = 1; i <= m; i++)
    {
        fin >> a >> b >> wt;
        arestas.push({{a, b}, wt});
    }

    fin.close();

    int total = 0;
    
    vector<pair<int, int>> vertex = kruskal(N, arestas, total);

    if (!(output_file == "")){
        ofstream fout(output_file);
        if (!fout){
            cerr << "Could not open output file: " << output_file << endl;
            return 1;
        }
        if (ans){
            for (auto sample : vertex)
                fout << "(" << sample.second << "," << sample.first << ") ";
        }
        else{
            fout << " " << total<< endl;
        }
        fout.close();
    }

    if(ans){
        for (auto sample : vertex)
            cout << "(" << sample.second << "," << sample.first << ") ";
    }
    else{
        cout << " " << total << endl;
    }
        
    return 0;
}
