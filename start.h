#ifndef START_H
#define START_H

#include <SFML/Graphics.hpp>

std::string chooseAlgo() {

    std::string algo;

    sf::RenderWindow start_window(sf::VideoMode(400, 400), "Graph Search Vis");
    start_window.setFramerateLimit(60);
    sf::Font dejavu_mono;
    dejavu_mono.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf");

    sf::RectangleShape bfs_button(sf::Vector2f(100, 50));
    bfs_button.setPosition(50, 50);
    bfs_button.setFillColor(sf::Color(50, 0, 100));
    
    sf::Text bfs_text;
    bfs_text.setFont(dejavu_mono);
    bfs_text.setString("BFS");
    bfs_text.setCharacterSize(25);
    bfs_text.setPosition(75,50);
    bfs_text.setFillColor(sf::Color(255,0,0));

    
    sf::RectangleShape dfs_button(sf::Vector2f(100, 50));
    dfs_button.setPosition(50, 125);
    dfs_button.setFillColor(sf::Color(50, 0, 100));
    
    sf::Text dfs_text;
    dfs_text.setFont(dejavu_mono);
    dfs_text.setString("DFS");
    dfs_text.setCharacterSize(25);
    dfs_text.setPosition(75,125);
    dfs_text.setFillColor(sf::Color(255,0,0));

    while(start_window.isOpen()) {
        sf::Event event;
        while (start_window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    start_window.close();
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.x > 50 && event.mouseButton.x < 150 && event.mouseButton.y > 50 && event.mouseButton.y < 100) {
                        algo = "BFS";
                        start_window.close();
                    }
                    else if(event.mouseButton.x > 50 && event.mouseButton.x < 150 && event.mouseButton.y > 125 && event.mouseButton.y < 175) {
                        algo = "DFS";
                        start_window.close();
                    }       
            }
        }
        start_window.clear();
        start_window.draw(bfs_button);
        start_window.draw(bfs_text);
        start_window.draw(dfs_button);
        start_window.draw(dfs_text);
        start_window.display();
    }

    return algo;
}
#endif

