#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <algorithm>
#include "graph.h"
#include "utils.h"
#include <set>

struct Node {
    int m_state;
    int m_h;
    int m_cost;
    int m_priority;
    std::vector<int> m_path;

    Node(int s, const std::vector<int> &p, int c=0, int h=0) {
        m_state = s;
        m_h = h;
        m_cost = c;
        m_path = p;
        m_priority = m_cost + m_h;
    }
};

struct CompareNode {
    bool operator()(Node const &n1, Node const &n2) const {
        return n1.m_priority < n2.m_priority;
    }
};

Graph::Graph(const std::vector<std::vector<int>> &adj, const std::vector<sf::CircleShape*> &nodes, const std::vector<std::vector<int>> &w_adj) {
    m_adj = adj;
    m_nodes = nodes;
    m_weight_adj = w_adj;
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
    // precompute heuristics
    std::vector<int> h;
    for(int i = 0; i < m_adj.size(); i++)
        h.push_back(utils::man_distance(m_nodes.at(i)->getPosition().x, m_nodes.at(i)->getPosition().y, m_nodes.at(g)->getPosition().x, m_nodes.at(g)->getPosition().y));
    
    std::set<Node, CompareNode> frontier;
    frontier.insert(Node(s, {}, 0, h.at(s)));
    std::vector<bool> explored(m_adj.size());
    std::vector<int> explore_order;
    while(!frontier.empty()) {
        Node curr = *frontier.begin();
        if(std::find(explore_order.begin(), explore_order.end(), curr.m_state) == explore_order.end())
            explore_order.push_back(curr.m_state);
        frontier.erase(frontier.begin());
        explored.at(curr.m_state) = true;
        if(curr.m_state == g)
            return {curr.m_path, explore_order};
        
        // look at neighbors
        for(auto adj : m_adj.at(curr.m_state)) {
            if(!explored.at(adj)) {
                int next_cost = curr.m_cost + m_weight_adj.at(curr.m_state).at(adj);
                std::vector<int> next_path = curr.m_path;
                next_path.push_back(adj);
                int next_priority = next_cost + h.at(adj);
                Node next_node(adj, next_path, next_cost, h.at(adj));
                bool in_frontier = false;
                for(auto n : frontier)
                    if(n.m_state == adj) {
                        in_frontier = true;
                        if(n.m_priority > next_priority)
                            n = next_node;
                        break;
                    }
                if(!in_frontier)
                    frontier.insert(next_node);
            }
        }
    }
    return {};
}

std::vector<std::vector<int>> Graph::GREEDY(const int &s, const int &g) const {
    // precompute heuristics
    std::vector<int> h;
    for(int i = 0; i < m_adj.size(); i++)
        h.push_back(utils::man_distance(m_nodes.at(i)->getPosition().x, m_nodes.at(i)->getPosition().y, m_nodes.at(g)->getPosition().x, m_nodes.at(g)->getPosition().y));

    std::set<Node, CompareNode> frontier;
    frontier.insert(Node(s, {}, 0, h.at(s)));
    std::vector<bool> explored(m_adj.size());
    std::vector<int> explore_order;
    while(!frontier.empty()) {
        Node curr = *frontier.begin();
        if(std::find(explore_order.begin(), explore_order.end(), curr.m_state) == explore_order.end())
            explore_order.push_back(curr.m_state);
        frontier.erase(frontier.begin());
        explored.at(curr.m_state) = true;
        if(curr.m_state == g)
            return {curr.m_path, explore_order};
        
        // look at neighbors
        for(auto adj : m_adj.at(curr.m_state)) {
            if(!explored.at(adj)) {
                std::vector<int> next_path = curr.m_path;
                next_path.push_back(adj);
                Node next_node(adj, next_path, 0, h.at(adj));
                bool in_frontier = false;
                for(auto n : frontier)
                    if(n.m_state == adj) {
                        in_frontier = true;
                        break;
                    }
                if(!in_frontier)
                    frontier.insert(next_node);
            }
        }
    }
    return {};
}

std::vector<std::vector<int>> Graph::UCS(const int &s, const int &g) const {
    std::set<Node, CompareNode> frontier;
    frontier.insert(Node(s, {}));
    std::vector<bool> explored(m_adj.size());
    std::vector<int> explore_order;
    while(!frontier.empty()) {
        Node curr = *frontier.begin();
        if(std::find(explore_order.begin(), explore_order.end(), curr.m_state) == explore_order.end())
            explore_order.push_back(curr.m_state);
        frontier.erase(frontier.begin());
        explored.at(curr.m_state) = true;
        if(curr.m_state == g)
            return {curr.m_path, explore_order};
        
        // look at neighbors
        for(auto adj : m_adj.at(curr.m_state)) {
            if(!explored.at(adj)) {
                int next_cost = curr.m_cost + m_weight_adj.at(curr.m_state).at(adj);
                std::vector<int> next_path = curr.m_path;
                next_path.push_back(adj);
                Node next_node(adj, next_path, next_cost);
                bool in_frontier = false;
                for(auto n : frontier)
                    if(n.m_state == adj) {
                        in_frontier = true;
                        if(n.m_priority > next_cost)
                            n = next_node;
                        break;
                    }
                if(!in_frontier)
                    frontier.insert(next_node);
            }
        }
    }
    return {};
}

