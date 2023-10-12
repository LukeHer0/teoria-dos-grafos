// Create a script that generates a directed graph with negative-weight edges and no negative cycles to save in a output file
// The graph is generated randomly
// The number of vertices and edges are given by the user

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[]) {
    int n, m, u, v, w;
    vector<pair<int, int>> edges;
    srand(time(NULL));

    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <number of vertices> <number of edges> <output file>" << endl;
        return 1;
    }

    n = atoi(argv[1]);
    m = atoi(argv[2]);

    if (n < 1 || m < 1) {
        cout << "The number of vertices and edges must be greater than 0" << endl;
        return 1;
    }

    if (m > n * (n - 1)) {
        cout << "The number of edges must be less than " << n * (n - 1) << endl;
        return 1;
    }

    ofstream output(argv[3]);

    if (!output.is_open()) {
        cout << "Error opening output file" << endl;
        return 1;
    }

    output << n << " " << m << endl;

    for (int i = 0; i < m; i++) {
        u = rand() % n;
        v = rand() % n;
        w = rand() % 1000 - 500;

        if (u == v) {
            i--;
            continue;
        }

        if (find(edges.begin(), e dges.end(), make_pair(u, v)) != edges.end()) {
            i--;
            continue;
        }

        edges.push_back(make_pair(u, v));

        output << u << " " << v << " " << w << endl;
    }

    output.close();

    return 0;
}
