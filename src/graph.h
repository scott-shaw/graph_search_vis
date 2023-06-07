#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <SFML/Graphics.hpp>

class Graph {
public:
    Graph(const std::vector<std::vector<int>> & adj, const std::vector<sf::CircleShape*> &nodes, const std::vector<std::vector<int>> &w_adj);
    std::vector<std::vector<int>> BFS(const int &s, const int &g) const;
    std::vector<std::vector<int>> DFS(const int &s, const int &g) const;
    std::vector<std::vector<int>> IDS(const int &s, const int &g) const;
    std::vector<std::vector<int>> A_STAR(const int &s, const int &g) const;

private:
    std::vector<std::vector<int>> DLS(const int &s, const int &g, const int &depth) const;

    std::vector<std::vector<int>> m_adj;
    std::vector<sf::CircleShape*> m_nodes;
    std::vector<std::vector<int>> m_weight_adj;
};

#endif

