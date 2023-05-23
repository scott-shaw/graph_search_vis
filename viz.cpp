#include <iostream>
#include "viz.h"
#include "graph.h"

Viz::Viz(const int &radius) {
    m_radius = radius;
}

int Viz::checkNodeCollision(int x, int y, int new_radius) {
    bool collides = false;
    int i = 0;
    for(auto node : m_nodes) {
        int radius = node->getRadius();
        sf::Vector2f pos = node->getPosition();
        if(x-new_radius > pos.x+(2*radius) || y-new_radius > pos.y+(2*radius) || x+new_radius < pos.x || y+new_radius < pos.y) {
            i++;
            continue;
        }
        return i;
    } 
    return -1;
}

void Viz::addNode(sf::Event e) {
    int collides = checkNodeCollision(e.mouseButton.x, e.mouseButton.y, m_radius);
    if(collides == -1) {
        sf::CircleShape *shape = new sf::CircleShape(m_radius);
        shape->setPosition(e.mouseButton.x-m_radius, e.mouseButton.y-m_radius);
        shape->setFillColor(sf::Color(100, 0, 50));
        m_nodes.push_back(shape);
        m_adj.push_back({});
    }
}

void Viz::selectNode(sf::Event e) {
    int collides = checkNodeCollision(e.mouseButton.x, e.mouseButton.y, 1);
    if(collides > -1) {
        m_selected_line_coords.push_back(sf::Vector2f(e.mouseButton.x, e.mouseButton.y));
        m_selected_line_nodes.push_back(collides);
    }
}

void Viz::addLine() {
    if(m_selected_line_nodes.size() == 2) {
        // Draw edge and add to adj list if not a self edge
        if(m_selected_line_nodes.at(0) != m_selected_line_nodes.at(1)) {
            m_adj.at(m_selected_line_nodes.at(0)).push_back(m_selected_line_nodes.at(1));
            m_adj.at(m_selected_line_nodes.at(1)).push_back(m_selected_line_nodes.at(0)); 
            sf::VertexArray l(sf::LinesStrip, 2);
            l[0].position = m_selected_line_coords.at(0);
            l[1].position = m_selected_line_coords.at(1);
            m_lines.push_back(l);
        }
        m_selected_line_nodes.clear();
        m_selected_line_coords.clear();
    }
}

void Viz::runSearch() {
    std::cout << "RUNNING BFS" << std::endl;
    Graph g(m_adj);
    std::vector<int> pafh = g.BFS_PATH(m_start_node, m_goal_node);
    std::vector<std::vector<int>> exp = g.BFS_EXPLORE(m_start_node, m_goal_node);
    m_path.insert(m_path.end(), pafh.begin(), pafh.end());
    m_explore.insert(m_explore.end(), exp.begin(), exp.end());
    std::cout << "PATH FOUND: ";
    for(int p : m_path)
        std::cout << p << " ";
    std::cout << std::endl;

}


void Viz::setStartGoalNode(const sf::RenderWindow &window) {
    if(m_start_node == -1) {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        int collides = checkNodeCollision(pos.x, pos.y, 1);
        if(collides > -1) {
            sf::CircleShape *shape = new sf::CircleShape(m_radius);
            shape->setPosition(m_nodes.at(collides)->getPosition().x, m_nodes.at(collides)->getPosition().y);
            shape->setFillColor(sf::Color(0, 0, 255));
            m_nodes.at(collides) = shape;
            m_start_node = collides;
            m_path.push_back(m_start_node);
            m_explore.push_back({m_start_node});
            std::cout << "SET START NODE TO: " << collides << std::endl;
        }
    }
    else if(m_start_node > -1 && m_goal_node == -1) {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        int collides = checkNodeCollision(pos.x, pos.y, 1);
        if(collides > -1 && collides != m_start_node) {
            int radius = 20;
            sf::CircleShape *shape = new sf::CircleShape(radius);
            shape->setPosition(m_nodes.at(collides)->getPosition().x, m_nodes.at(collides)->getPosition().y);
            shape->setFillColor(sf::Color(0, 255, 0));
            m_nodes.at(collides) = shape;
            m_goal_node = collides;
            std::cout << "SET GOAL NODE TO: " << collides << std::endl;
        }
    }
}

void Viz::updateExploredShapes(const int &update_rate) {
    if(m_clock_cnt > update_rate && m_path.size() > 1) {
        if(m_explore_idx < m_explore.size()-1) {
            std::vector<int> layer = m_explore.at(m_explore_idx);
            for(int node : layer) {
                sf::CircleShape *shape = new sf::CircleShape(m_radius);
                shape->setPosition(m_nodes.at(node)->getPosition().x, m_nodes.at(node)->getPosition().y);
                shape->setFillColor(m_nodes.at(node)->getFillColor());
                shape->setOutlineThickness(5.0);
                shape->setOutlineColor(sf::Color(255,255,255));
                m_nodes.at(node) = shape;
            }
            m_explore_idx++;
        }
        else if(m_path_idx <= m_path.size()-1 && m_explore_idx == m_explore.size()-1) {
            int node = m_path.at(m_path_idx);
            sf::CircleShape *shape = new sf::CircleShape(m_radius);
            shape->setPosition(m_nodes.at(node)->getPosition().x, m_nodes.at(node)->getPosition().y);
            shape->setFillColor(m_nodes.at(node)->getFillColor());
            shape->setOutlineThickness(5.0);
            shape->setOutlineColor(sf::Color(255,0,0));
            m_nodes.at(node) = shape;
            m_path_idx++;
        }
        m_clock_cnt = 0;
    }
}

void Viz::updateClock(const double &dt) {
    m_clock_cnt += dt;
}

std::vector<sf::CircleShape*> Viz::getNodes() {
    return m_nodes;
}

std::vector<sf::VertexArray> Viz::getEdges() {
    return m_lines;
}





