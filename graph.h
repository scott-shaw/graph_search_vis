#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph {
public:
    Graph(const std::vector<std::vector<int>> & adj);
    std::vector<std::vector<int>> BFS_EXPLORE(int s, int g);
    std::vector<int> BFS_PATH(int s, int g);
    std::vector<int> DFS_PATH(int s, int g);
    std::vector<std::vector<int>> DFS_EXPLORE(int s, int g);

private:
    std::vector<std::vector<int>> m_adj;
};

#endif

