#include <SFML/Graphics.hpp>
#include <iostream>
#include "viz.h"
#include "graph.h"
#include "start.h"
#include "button.h"

/* TODO
 * Reset search
 * Fix algo selector window (i.e., not in header)
 * 
 *
 */

bool mouseInRect(sf::RenderWindow &window, sf::RectangleShape &rect, int spacing) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    return rect.getGlobalBounds().contains(sf::Vector2f(mouse_pos.x+spacing, mouse_pos.y+spacing)) ||
            rect.getGlobalBounds().contains(sf::Vector2f(mouse_pos.x+spacing, mouse_pos.y-spacing)) ||
            rect.getGlobalBounds().contains(sf::Vector2f(mouse_pos.x-spacing, mouse_pos.y+spacing)) ||
            rect.getGlobalBounds().contains(sf::Vector2f(mouse_pos.x-spacing, mouse_pos.y-spacing));
}

int main() {
    std::string algo = "BFS";

    sf::RenderWindow window(sf::VideoMode(1280, 800), "Graph Search Viz");
    
    window.setFramerateLimit(60);
    sf::Clock clock;
    int radius = 20;
    Viz gs_viz(radius);
    bool can_edit = true;

    sf::Font dejavu_mono;
    dejavu_mono.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf");
    GUI::Button algo_selector(sf::Vector2f(10,10), dejavu_mono, "Algorithm\nSelection", 20);

    sf::Text curr_algo("Current Algo: "+algo, dejavu_mono);
    curr_algo.setPosition(sf::Vector2f(10,750));

    sf::RectangleShape banned_region(sf::Vector2f(150,500));
    banned_region.setPosition(sf::Vector2f(0,0));
    banned_region.setFillColor(sf::Color(50,50,50));

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::MouseButtonPressed:
                    if(can_edit && !mouseInRect(window, banned_region, radius*2)) {
                        if (event.mouseButton.button == sf::Mouse::Left)
                            gs_viz.addNode(event);
                        else
                            gs_viz.selectNode(event);
                    }
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Enter) {
                        can_edit = false;
                        if(algo == "BFS")
                            gs_viz.runSearch(&Graph::BFS_PATH, &Graph::BFS_EXPLORE);
                        else if(algo == "DFS")
                            gs_viz.runSearch(&Graph::DFS_PATH, &Graph::DFS_EXPLORE);
                    }
                    else if(event.key.code == sf::Keyboard::Space) {
                        gs_viz.setStartGoalNode(window);
                    }
                default:
                    break;
            }   
        }
        gs_viz.addLine();
        gs_viz.updateExploredShapes(500);
        gs_viz.updateClock(dt.asMilliseconds());

        algo_selector.update(event, window);
        bool algo_sel_state = algo_selector.getState();
        if(algo_sel_state) {
            algo_selector.setState(false);
            algo = chooseAlgo();
            curr_algo.setString("Current Algo: "+algo);
            std::cout << "algo: " << algo << std::endl;
        }

        // draw objects
        window.clear();
        for(auto line : gs_viz.getEdges())
            window.draw(line);
        auto nodes = gs_viz.getNodes();
        for(auto it=nodes.begin();it!=nodes.end();it++) {
            window.draw(**it);
        }
        window.draw(banned_region);
        window.draw(algo_selector);
        window.draw(curr_algo);
        window.display();
    }
}

