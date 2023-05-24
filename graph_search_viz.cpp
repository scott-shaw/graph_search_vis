#include <SFML/Graphics.hpp>
#include <iostream>
#include "viz.h"
#include "graph.h"
#include "sidebar.h"

/* TODO
 * Fix algo selector window (i.e., not in header)
 * Fix exploration (so dfs looks correct)
 * Implement more algorithms (IDS, A*, etc)
 * Add debug options to sidebar (clear nodes, clear edges, reset start/goal nodes, etc)
 *
 *
 */

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 800), "Graph Search Viz");
    window.setFramerateLimit(60);
    sf::Clock clock;
    
    sf::Font dejavu_mono;
    dejavu_mono.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf");
    
    int radius = 20;
    Viz gs_viz(radius);
    bool can_edit = true;
    
    std::string algo = "BFS";
    GUI::Sidebar sidebar(dejavu_mono, algo);

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::MouseButtonPressed:
                    if(can_edit && !sidebar.mouseNearSidebar(window, radius*2)) {
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

        algo = sidebar.update(event, window);

        // draw objects
        window.clear();
        window.draw(sidebar);
        for(auto line : gs_viz.getEdges())
            window.draw(line);
        auto nodes = gs_viz.getNodes();
        for(auto it=nodes.begin();it!=nodes.end();it++) {
            window.draw(**it);
        }
        window.display();
    }
}

