#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph {
public:
    Graph(const std::vector<std::vector<int>> & adj);
    void BFS(int s);
    std::vector<std::vector<int>> BFS_EXPLORE(int s, int g);
    std::vector<int> BFS_PATH(int s, int g);

private:
    std::vector<std::vector<int>> m_adj;
};

#endif

