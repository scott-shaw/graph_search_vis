#include <iostream>
#include "viz.h"
#include "graph.h"

GUI::Viz::Viz(const int &radius, const sf::Font &font) {
    m_radius = radius;
    m_font = font;
}

int GUI::Viz::checkNodeCollision(int x, int y, int new_radius) {
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

void GUI::Viz::addNode(sf::Event e) {
    int collides = checkNodeCollision(e.mouseButton.x, e.mouseButton.y, m_radius);
    if(collides == -1 && m_can_edit) {
        sf::CircleShape *shape = new sf::CircleShape(m_radius);
        shape->setPosition(e.mouseButton.x-m_radius, e.mouseButton.y-m_radius);
        shape->setFillColor(sf::Color(100, 0, 50));
        m_nodes.push_back(shape);
        m_adj.push_back({});
        sf::Text txt(std::to_string(m_nodes.size()-1), m_font, m_radius*3/4);
        txt.setFillColor(sf::Color(245,164,66));
        txt.setPosition(shape->getPosition()+sf::Vector2f((shape->getGlobalBounds().width/2)-(txt.getLocalBounds().width/2), shape->getGlobalBounds().height/2-(txt.getLocalBounds().height)));
        m_node_txt.push_back(txt);
    }
}

void GUI::Viz::selectNode(sf::Event e) {
    int collides = checkNodeCollision(e.mouseButton.x, e.mouseButton.y, 1);
    if(collides > -1) {
        m_selected_line_coords.push_back(sf::Vector2f(e.mouseButton.x, e.mouseButton.y));
        m_selected_line_nodes.push_back(collides);
    }
}

void GUI::Viz::addLine() {
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

void GUI::Viz::runSearch(std::vector<std::vector<int>> (Graph::*search_path)(const int&, const int&)const) {
    if(m_start_node == -1 || m_goal_node == -1) {
        std::cout << "Start/Goal nodes not specified" << std::endl;
        return;
    }
    resetSearch();
    m_can_edit = false;
    m_path.push_back(m_start_node);
    Graph g(m_adj);
    std::vector<std::vector<int>> path_explore = (g.*search_path)(m_start_node, m_goal_node);
    m_path.insert(m_path.end(), path_explore.at(0).begin(), path_explore.at(0).end());
    m_explore = path_explore.at(1);
    std::cout << "PATH FOUND: ";
    for(int p : m_path)
        std::cout << p << " ";
    std::cout << std::endl;
    std::cout << "EXPLORED IN: ";
    for(int p : m_explore)
        std::cout << p << " ";
    std::cout << std::endl;
}


void GUI::Viz::setStartGoalNode(const sf::RenderWindow &window) {
    if(m_start_node == -1) {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        int collides = checkNodeCollision(pos.x, pos.y, 1);
        if(collides > -1) {
            sf::CircleShape *shape = new sf::CircleShape(m_radius);
            shape->setPosition(m_nodes.at(collides)->getPosition().x, m_nodes.at(collides)->getPosition().y);
            shape->setFillColor(sf::Color(0, 0, 255));
            m_nodes.at(collides) = shape;
            m_start_node = collides;
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
            shape->setFillColor(sf::Color(40, 105, 50));
            m_nodes.at(collides) = shape;
            m_goal_node = collides;
            std::cout << "SET GOAL NODE TO: " << collides << std::endl;
        }
    }
}

void GUI::Viz::updateExploredShapes(const int &update_rate) {
    if(m_clock_cnt > update_rate && m_path.size() > 1) {
        if(m_explore_idx <= m_explore.size()-1) {
            int node = m_explore.at(m_explore_idx);
            sf::CircleShape *shape = new sf::CircleShape(m_radius);
            shape->setPosition(m_nodes.at(node)->getPosition().x, m_nodes.at(node)->getPosition().y);
            shape->setFillColor(m_nodes.at(node)->getFillColor());
            shape->setOutlineThickness(5.0);
            shape->setOutlineColor(sf::Color(255,255,255));
            m_nodes.at(node) = shape;
            m_explore_idx++;
        }
        else if(m_path_idx <= m_path.size()-1 && m_explore_idx == m_explore.size()) {
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

void GUI::Viz::updateClock(const double &dt) {
    m_clock_cnt += dt;
}

std::vector<sf::CircleShape*> GUI::Viz::getNodes() {
    return m_nodes;
}

std::vector<sf::VertexArray> GUI::Viz::getEdges() {
    return m_lines;
}

std::vector<std::vector<int>> GUI::Viz::getAdj() {
    return m_adj;
}

void GUI::Viz::clearGraph() {
    m_adj = {};
    m_nodes = {};
    m_lines = {};
    m_start_node = -1;
    m_goal_node = -1;
    m_can_edit = true;
}

void GUI::Viz::clearEdges() {
    resetSearch(); 
    m_adj.clear();
    for(auto node : m_nodes)
        m_adj.push_back({});
    m_lines.clear();
    m_selected_line_nodes.clear();
    m_selected_line_coords.clear();
    m_can_edit = true;
}

void GUI::Viz::resetSGNodes() {
    resetSearch(); 
    if(m_start_node != -1) {
        sf::CircleShape *shape = new sf::CircleShape(m_radius);
        shape->setPosition(m_nodes.at(m_start_node)->getPosition());
        shape->setFillColor(sf::Color(100, 0, 50));
        m_nodes.at(m_start_node) = shape;
    }
    if(m_goal_node != -1) {
        sf::CircleShape *shape = new sf::CircleShape(m_radius);
        shape->setPosition(m_nodes.at(m_goal_node)->getPosition());
        shape->setFillColor(sf::Color(100, 0, 50));
        m_nodes.at(m_goal_node) = shape;
    }

    m_start_node = -1;
    m_goal_node = -1;
    m_can_edit = true;
}

void GUI::Viz::resetSearch() {
    m_path = {};
    m_explore = {};
    m_explore_idx = 0;
    m_path_idx = 0;
    for(auto node : m_nodes) {
        node->setOutlineThickness(0);
    }
}

void GUI::Viz::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for(auto line : m_lines)
        target.draw(line, states);
    for(auto it=m_nodes.begin();it!=m_nodes.end();it++)
        target.draw(**it, states);
    for(auto t : m_node_txt)
        target.draw(t, states);
}
