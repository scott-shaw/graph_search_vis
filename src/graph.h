#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph {
public:
    Graph(const std::vector<std::vector<int>> & adj);
    std::vector<std::vector<int>> BFS(int s, int g);
    std::vector<std::vector<int>> DFS(int s, int g);

private:
    std::vector<std::vector<int>> m_adj;
};

#endif

