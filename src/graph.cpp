#include <vector>
#include <queue>
#include <stack>
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

std::vector<int> Graph::BFS_EXPLORE(int s, int g) {
    std::vector<bool> explored(m_adj.size());
    std::queue<Node> frontier;
    std::vector<int> out;
    frontier.push(Node(s,{}));
    while (!frontier.empty()) {
        std::queue<Node> front_cpy = frontier;
        std::vector<int> nodes_in_frontier;
        /*
        while(!front_cpy.empty()) {
            nodes_in_frontier.push_back(front_cpy.front().m_state);
            front_cpy.pop();
        }
        out.push_back(nodes_in_frontier);
        */
        out.push_back(frontier.front().m_state);
        Node curr = frontier.front();
        frontier.pop();
        explored.at(curr.m_state) = true;
        for (int adjacent : m_adj.at(curr.m_state)) {
            if (!explored.at(adjacent)) {
                std::vector<int> n = curr.m_path;
                n.push_back(adjacent);
                frontier.push(Node(adjacent, n));
            }    
        }
    }
    return out;
}

std::vector<int> Graph::DFS_PATH(int s, int g) {
    std::vector<bool> explored(m_adj.size());
    std::stack<Node> frontier; 
    frontier.push(Node(s,{}));
    while (!frontier.empty()) {
        Node curr = frontier.top();
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

std::vector<int> Graph::DFS_EXPLORE(int s, int g) {
    std::vector<bool> explored(m_adj.size());
    std::stack<Node> frontier;
    std::vector<int> out;
    frontier.push(Node(s,{}));
    while (!frontier.empty()) {
        std::stack<Node> front_cpy = frontier;
        std::vector<int> nodes_in_frontier;
        /*
        while(!front_cpy.empty()) {
            nodes_in_frontier.push_back(front_cpy.top().m_state);
            front_cpy.pop();
        }
        out.push_back(nodes_in_frontier);
        */
        out.push_back(frontier.top().m_state);
        Node curr = frontier.top();
        frontier.pop();
        explored.at(curr.m_state) = true;
        for (int adjacent : m_adj.at(curr.m_state)) {
            if (!explored.at(adjacent)) {
                std::vector<int> n = curr.m_path;
                n.push_back(adjacent);
                frontier.push(Node(adjacent, n));
            }    
        }
    }
    return out;
}
