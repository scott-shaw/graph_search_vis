#include <SFML/Graphics.hpp>
#include <iostream>
#include "viz.h"
#include "graph.h"
#include "sidebar.h"

/* TODO
 * Implement more algorithms (IDS, A*, etc)
 * Fix clear operations (they are slow currently -- i.e., cant do anything for a few secs after)
 * Add edge weights based on length
 *
 */

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 800), "Graph Search Viz");
    window.setFramerateLimit(60);
    sf::Clock clock;
    
    sf::Font ubuntu_reg;
    ubuntu_reg.loadFromFile("./data/Ubuntu-R.ttf");
    
    int radius = 20;
    GUI::Viz gs_viz(radius, ubuntu_reg);
    
    std::string algo = "BFS";
    GUI::Sidebar sidebar(ubuntu_reg, algo);

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::MouseButtonPressed:
                    if(!sidebar.mouseNearSidebar(window, radius*2)) {
                        if (event.mouseButton.button == sf::Mouse::Left)
                            gs_viz.addNode(event);
                        else
                            gs_viz.selectNode(event);
                    }
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Enter) {
                        std::cout << "\nRunning search using " << algo << std::endl;
                        if(algo == "BFS")
                            gs_viz.runSearch(&Graph::BFS);
                        else if(algo == "DFS")
                            gs_viz.runSearch(&Graph::DFS);
                        else if(algo == "IDS")
                            gs_viz.runSearch(&Graph::IDS);
                        else if(algo == "A*")
                            gs_viz.runSearch(&Graph::A_STAR);
                        else if(algo == "Greedy")
                            gs_viz.runSearch(&Graph::GREEDY);
                        else if(algo == "UCS")
                            gs_viz.runSearch(&Graph::UCS);
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

        algo = sidebar.update(gs_viz, event, window);

        // draw objects
        window.clear(sf::Color(20,20,20));
        window.draw(sidebar);
        window.draw(gs_viz);
        window.display();
    }
}

