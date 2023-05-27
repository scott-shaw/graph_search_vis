#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph {
public:
    Graph(const std::vector<std::vector<int>> & adj);
    std::vector<std::vector<int>> BFS(const int &s, const int &g) const;
    std::vector<std::vector<int>> DFS(const int &s, const int &g) const;
    std::vector<std::vector<int>> IDS(const int &s, const int &g) const;

private:
    std::vector<std::vector<int>> DLS(const int &s, const int &g, const int &depth) const;

    std::vector<std::vector<int>> m_adj;
};

#endif

