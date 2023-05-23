#include <vector>
#include <queue>
#include <iostream>
#include "graph.h"

struct Node {
    int m_state;
    std::vector<int> m_path;

    Node(int s, const std::vector<int> & p){
        m_state = s;
        m_path = p;
    }
};

Graph::Graph(const std::vector<std::vector<int>> & adj) {
    m_adj = adj;
}

void Graph::BFS(int s) {
    std::vector<bool> explored(m_adj.size());
    std::queue<int> frontier; 
    frontier.push(s);
    while (!frontier.empty()) {
        int curr = frontier.front();
        frontier.pop();
        explored.at(curr) = true;
        std::cout << curr << " ";
        for (int adjacent : m_adj.at(curr))
            if (!explored.at(adjacent))
                frontier.push(adjacent);
    }
}

std::vector<int> Graph::BFS_PATH(int s, int g) {
    std::vector<bool> explored(m_adj.size());
    std::queue<Node> frontier; 
    frontier.push(Node(s,{}));
    while (!frontier.empty()) {
        Node curr = frontier.front();
        frontier.pop();
        explored.at(curr.m_state) = true;
        if(curr.m_state == g)
            return curr.m_path;
        for (int adjacent : m_adj.at(curr.m_state)) {
            if (!explored.at(adjacent)) {
                std::vector<int> n = curr.m_path;
                n.push_back(adjacent);
                frontier.push(Node(adjacent, n));
            }    
        }
    }
    return {};
}


