#include <SFML/Graphics.hpp>
#include "viz.h"
#include "graph.h"
#include "start.h"

int main() {
    std::string algo = chooseAlgo();

    sf::RenderWindow window(sf::VideoMode(1280, 800), "Graph Search Vis");
    
    window.setFramerateLimit(60);
    sf::Clock clock;
    Viz gs_viz(20);
    bool can_edit = true;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::MouseButtonPressed:
                    if(can_edit) {
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
            }   
        }
        gs_viz.addLine();
        gs_viz.updateExploredShapes(500);
        gs_viz.updateClock(dt.asMilliseconds());

        // draw objects
        window.clear();
        for(auto line : gs_viz.getEdges())
            window.draw(line);
        auto nodes = gs_viz.getNodes();
        for(auto it=nodes.begin();it!=nodes.end();it++) {
            window.draw(**it);
        }
        window.display();
    }
}

