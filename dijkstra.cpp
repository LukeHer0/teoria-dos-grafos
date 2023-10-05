/* Lista de adjacencia de um grafo G com 6 vértice e 8 arestas (3a coluna é o peso da aresta)
6 8
1 2 5
1 3 4
1 4 2
1 6 6
2 4 1
2 5 7
3 5 6
4 6 1
*/

#include <iostream>
#include <list>

using namespace std;

class Graph{
private:
    int V;

    list<pair<int, int>> *adj;

public:
    Graph(int v);

    void addEdge(int v, int w, int p);

    void dijkstra(int s);
};

Graph::Graph(int v){
    V = v;

    adj = new list<pair<int, int>>[v];
}

void Graph::addEdge(int v, int w, int p)
{
    adj[v].push_back(make_pair(w, p));
}

int main()
{
    Graph g(6);

    g.addEdge(1, 2, 5);
    g.addEdge(1, 3, 4);
    g.addEdge(1, 4, 2);
    g.addEdge(1, 6, 6);

    g.addEdge(2, 4, 1);
    g.addEdge(2, 5, 7);

    g.addEdge(3, 5, 6);

    g.addEdge(4, 6, 1);
}