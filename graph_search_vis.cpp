#include <SFML/Graphics.hpp>
#include "graph.h"
#include <iostream>

// if returns -1: no collision
// if returns anything else: index of node that it collides with
int checkNodeCollision(int x, int y, int new_radius, const std::vector<sf::CircleShape*> & s) {
    bool collides = false;
    int i = 0;
    for(auto node : s) {
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

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 800), "Graph Search Vis");
    
    window.setFramerateLimit(60);
    sf::Clock clock;

    // contains nodes (circles) to be drawn
    std::vector<sf::CircleShape*> shapes;
    
    // contains line objects to be drawn
    std::vector<sf::VertexArray> lines;

    // x,y coords of points selected to be end points for an edge
    std::vector<sf::Vector2f> selected_line_coords;

    // node index of edge end points
    std::vector<int> selected_line_nodes;

    // adjacency list to be used for graph search
    std::vector<std::vector<int>> adj;
   
    int start_node = -1;
    int goal_node = -1;
    std::vector<int> path;
    std::vector<std::vector<int>> explore;
    int explore_idx = 0;
    int path_idx = 0;
    int clock_cnt = 0;

    bool can_edit = true;

    int radius = 20;
    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::MouseButtonPressed:
                    // Draw nodes on left mouse button press
                    if(can_edit) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            int collides = checkNodeCollision(event.mouseButton.x, event.mouseButton.y, radius, shapes);
                            if(collides == -1) {
                                sf::CircleShape *shape = new sf::CircleShape(radius);
                                shape->setPosition(event.mouseButton.x-radius,event.mouseButton.y-radius);
                                shape->setFillColor(sf::Color(100, 0, 50));
                                shapes.push_back(shape);
                                adj.push_back({});
                            }
                        }
                        // select nodes as endpoints for edges on right mouse button press
                        else{
                            int collides = checkNodeCollision(event.mouseButton.x, event.mouseButton.y, 1, shapes);
                            if(collides > -1) {
                                selected_line_coords.push_back(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                                selected_line_nodes.push_back(collides);
                            }
                        }
                    }
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Enter) {
                        can_edit = false;
                        std::cout << "RUNNING BFS" << std::endl;
                        Graph g(adj);
                        std::vector<int> pafh = g.BFS_PATH(start_node, goal_node);
                        std::vector<std::vector<int>> exp = g.BFS_EXPLORE(start_node, goal_node);
                        path.insert(path.end(), pafh.begin(), pafh.end());
                        explore.insert(explore.end(), exp.begin(), exp.end());
                        std::cout << "PATH FOUND: ";
                        for(int p : path)
                            std::cout << p << " ";
                        std::cout << std::endl;
                    }
                    else if(event.key.code == sf::Keyboard::Space) {
                        if(start_node == -1) {
                            sf::Vector2i pos = sf::Mouse::getPosition(window);
                            int collides = checkNodeCollision(pos.x, pos.y, 1, shapes);
                            if(collides > -1) {
                                sf::CircleShape *shape = new sf::CircleShape(radius);
                                shape->setPosition(shapes.at(collides)->getPosition().x,shapes.at(collides)->getPosition().y);
                                shape->setFillColor(sf::Color(0, 0, 255));
                                shapes.at(collides) = shape;
                                start_node = collides;
                                path.push_back(start_node);
                                explore.push_back({start_node});
                                std::cout << "SET START NODE TO: " << collides << std::endl;
                            }
                        }
                        else if(start_node > -1 && goal_node == -1) {
                            sf::Vector2i pos = sf::Mouse::getPosition(window);
                            int collides = checkNodeCollision(pos.x, pos.y, 1, shapes);
                            if(collides > -1 && collides != start_node) {
                                int radius = 20;
                                sf::CircleShape *shape = new sf::CircleShape(radius);
                                shape->setPosition(shapes.at(collides)->getPosition().x,shapes.at(collides)->getPosition().y);
                                shape->setFillColor(sf::Color(0, 255, 0));
                                shapes.at(collides) = shape;
                                goal_node = collides;
                                std::cout << "SET GOAL NODE TO: " << collides << std::endl;
                            }
                        }
                    }
            }   
        }
        // once two nodes have been selected, add to adj list and draw, then clear selected nodes
        if(selected_line_nodes.size() == 2) {
            // Draw edge and add to adj list if not a self edge
            if(selected_line_nodes.at(0) != selected_line_nodes.at(1)) {
                adj.at(selected_line_nodes.at(0)).push_back(selected_line_nodes.at(1));
                adj.at(selected_line_nodes.at(1)).push_back(selected_line_nodes.at(0)); 
                sf::VertexArray l(sf::LinesStrip, 2);
                l[0].position = selected_line_coords.at(0);
                l[1].position = selected_line_coords.at(1);
                lines.push_back(l);
            }
            selected_line_nodes.clear();
            selected_line_coords.clear();
        }

        if(clock_cnt > 500 && path.size() > 1) {
            if(explore_idx < explore.size()-1) {
                std::vector<int> layer = explore.at(explore_idx);
                for(int node : layer) {
                    sf::CircleShape *shape = new sf::CircleShape(radius);
                    shape->setPosition(shapes.at(node)->getPosition().x,shapes.at(node)->getPosition().y);
                    shape->setFillColor(shapes.at(node)->getFillColor());
                    shape->setOutlineThickness(5.0);
                    shape->setOutlineColor(sf::Color(255,255,255));
                    shapes.at(node) = shape;
                }
                explore_idx++;
            }
            else if(path_idx <= path.size()-1 && explore_idx == explore.size()-1) {
                int node = path.at(path_idx);
                sf::CircleShape *shape = new sf::CircleShape(radius);
                shape->setPosition(shapes.at(node)->getPosition().x,shapes.at(node)->getPosition().y);
                shape->setFillColor(shapes.at(node)->getFillColor());
                shape->setOutlineThickness(5.0);
                shape->setOutlineColor(sf::Color(255,0,0));
                shapes.at(node) = shape;
                path_idx++;
            }
            clock_cnt = 0;
        }
        clock_cnt += dt.asMilliseconds();

        // draw objects
        window.clear();
        for(auto line : lines)
            window.draw(line);
        for(auto it=shapes.begin();it!=shapes.end();it++) {
            window.draw(**it);
        }
        window.display();
    }
    
    adj.erase(adj.end()-1, adj.end());
    std::cout << "Adjacency List: " << std::endl;
    int counter = 0;
    for(auto node : adj) {
        std::cout << counter << ": ";
        for(auto edge : node) {
            std::cout << edge << " ";
        }
        std::cout << std::endl;
        counter++;
    }
}

