#include <SFML/Graphics.hpp>
#include "graph.h"
#include <iostream>

bool checkCircleCollide(double x1, double y1, float r1, double x2, double y2, float r2){ 
    return std::abs((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) < (r1 + r2) * (r1 + r2);
}

// if returns -1: no collision
// if returns anything else: index of node that it collides with
int checkNodeCollision(int x, int y, int new_radius, const std::vector<sf::CircleShape*> & s) {
    bool collides = false;
    int i = 0;
    for(auto node : s) {
        int radius = node->getRadius();
        sf::Vector2f pos = node->getPosition();
        //if(checkCircleCollide(x+new_radius, y+new_radius, new_radius, pos.x+radius, pos.y+radius, radius))
        //    return true;
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
    
    window.setFramerateLimit(50);
    std::vector<sf::CircleShape*> shapes;
    std::vector<sf::Vector2f> selected_line_coords;
    std::vector<int> selected_line_nodes;
    std::vector<std::vector<int>> adj;
    
    std::vector<sf::VertexArray> lines;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        int radius = 20;
                        int collides = checkNodeCollision(event.mouseButton.x, event.mouseButton.y, radius, shapes);
                        if(collides == -1) {
                            sf::CircleShape *shape = new sf::CircleShape(radius);
                            shape->setPosition(event.mouseButton.x-radius,event.mouseButton.y-radius);
                            shape->setFillColor(sf::Color(100, 0, 50));
                            shapes.push_back(shape);
                            adj.push_back({});
                        }
                    }
                    else{
                        int collides = checkNodeCollision(event.mouseButton.x, event.mouseButton.y, 1, shapes);
                        if(collides > -1) {
                            selected_line_coords.push_back(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                            selected_line_nodes.push_back(collides);
                        }
                    }
            }   
        }
        // once two nodes have been selected, add to adj list and draw, then clear selected nodes
        if(selected_line_nodes.size() == 2) {
            adj.at(selected_line_nodes.at(0)).push_back(selected_line_nodes.at(1));
            adj.at(selected_line_nodes.at(1)).push_back(selected_line_nodes.at(0)); 

            sf::VertexArray l(sf::LinesStrip, 2);
            l[0].position = selected_line_coords.at(0);
            l[1].position = selected_line_coords.at(1);
            lines.push_back(l);

            selected_line_nodes.clear();
            selected_line_coords.clear();
        }

        window.clear();
        for(auto line : lines)
            window.draw(line);
        for(auto it=shapes.begin();it!=shapes.end();it++) {
            window.draw(**it);
        }
        window.display();
    }


    //Graph g({{1, 2}, {0, 4, 5}, {0, 3}, {2, 6}, {1}, {1}, {3}}); 
    //g.BFS(0);
    //std::cout << "\n" << std::endl;

    Graph gp({{1, 2}, {0, 4, 5}, {0, 3}, {2, 6}, {1}, {1}, {3}});
    auto path = gp.BFS_PATH(0, 6);
    for(int i : path)
        std::cout << i << " ";
    std::cout << std::endl;
}
