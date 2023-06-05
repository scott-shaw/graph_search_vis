#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <algorithm>
#include "graph.h"
#include "utils.h"

struct Node {
    int m_state;
    std::vector<int> m_path;

    Node(int s, const std::vector<int> & p) {
        m_state = s;
        m_path = p;
    }
};


struct HNode {
    int m_state;
    int m_h;

    HNode(int s, int h) {
        m_state = s;
        m_h = h;
    }
};

struct CompareHNode {
    bool operator()(HNode const & n1, HNode const & n2) {
        return n1.m_h > n2.m_h;
    }
};

Graph::Graph(const std::vector<std::vector<int>> & adj, const std::vector<sf::CircleShape*> &nodes) {
    m_adj = adj;
    m_nodes = nodes;
}

std::vector<std::vector<int>> Graph::BFS(const int &s, const int &g) const {
    std::vector<bool> explored(m_adj.size());
    std::queue<Node> frontier; 
    std::vector<int> explore_order;
    frontier.push(Node(s,{}));
    while (!frontier.empty()) {
        Node curr = frontier.front();
        if(std::find(explore_order.begin(), explore_order.end(), curr.m_state) == explore_order.end())
            explore_order.push_back(curr.m_state);
        frontier.pop();
        explored.at(curr.m_state) = true;
        if(curr.m_state == g)
            return {curr.m_path, explore_order};
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

std::vector<std::vector<int>> Graph::DFS(const int &s, const int &g) const {
    std::vector<bool> explored(m_adj.size());
    std::stack<Node> frontier; 
    std::vector<int> explore_order;
    frontier.push(Node(s,{}));
    while (!frontier.empty()) {
        Node curr = frontier.top();
        if(std::find(explore_order.begin(), explore_order.end(), curr.m_state) == explore_order.end())
            explore_order.push_back(curr.m_state);
        frontier.pop();
        explored.at(curr.m_state) = true;
        if(curr.m_state == g)
            return {curr.m_path, explore_order};
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


std::vector<std::vector<int>> Graph::DLS(const int &s, const int &g, const int &depth) const {
    std::vector<bool> explored(m_adj.size());
    std::stack<Node> frontier; 
    std::vector<int> explore_order;
    frontier.push(Node(s,{}));
    while (!frontier.empty()) {
        Node curr = frontier.top();
        if(std::find(explore_order.begin(), explore_order.end(), curr.m_state) == explore_order.end())
            explore_order.push_back(curr.m_state);
        frontier.pop();
        explored.at(curr.m_state) = true;
        if(curr.m_state == g)
            return {curr.m_path, explore_order};
        if(curr.m_path.size() < depth) {
            for (int adjacent : m_adj.at(curr.m_state)) {
                if (!explored.at(adjacent)) {
                    std::vector<int> n = curr.m_path;
                    n.push_back(adjacent);
                    frontier.push(Node(adjacent, n));
                }    
            }
        }
    }
    return {};
}

std::vector<std::vector<int>> Graph::IDS(const int &s, const int &g) const {
    for(int depth = 0; depth < 100000; depth++) {
        std::vector<std::vector<int>> result = DLS(s, g, depth);
        if(result.size() > 0)
            return result;
    }
    return {};
}

std::vector<std::vector<int>> Graph::A_STAR(const int &s, const int &g) const {
    // precompute heuristics (NEED node positions to calc distances)
    std::vector<HNode> h;
    for(auto node : m_nodes) {
    for(int i = 0; i < m_adj.size(); i++) {
        h.push_back(HNode(i, utils::man_distance(m_nodes.at(i)->getPosition().x, m_nodes.at(i)->getPosition().y, m_nodes.at(g)->getPosition().x, m_nodes.at(g)->getPosition().y)));
    }

    std::priority_queue<HNode, std::vector<HNode>, CompareHNode> frontier(h.begin(), h.end());
    std::vector<bool> explored(m_adj.size());
    frontier.push(h.at(s));
    explored.at(s) = true;
    while(!frontier.empty()) {
        HNode curr = frontier.top();
        frontier.pop();

        for(auto adj : m_adj.at(curr.m_state)) {
            if(!explored.at(adj)) {
                explored.at(adj) = true;
                frontier.push(h.at(adj));
            }
        }


    }
    return {};
}

