#include "sidebar.h"
#include <iostream>
#include "algoselect.h"

GUI::Sidebar::Sidebar(const sf::Font &font, const std::string &algo, const sf::Vector2f &size, const int &char_size) {
    m_font = font;
    m_algo = algo;

    m_sidebar_background.setSize(size);
    m_sidebar_background.setPosition(sf::Vector2f(0,0));
    m_sidebar_background.setFillColor(sf::Color(50,50,50));

    GUI::Button algo_selector(sf::Vector2f(10,10), m_font, "Algorithm\nSelection", char_size);
    m_algo_selector = algo_selector;
    
    GUI::Button clear_all (sf::Vector2f(10,80), m_font, "CE All", char_size);
    m_clear_all = clear_all;

    GUI::Button clear_edges (sf::Vector2f(10,110), m_font, "CE Edges", char_size);
    m_clear_edges = clear_edges;
    
    GUI::Button reset_sg (sf::Vector2f(10,146), m_font, "CE S/G", char_size);
    m_reset_sg_nodes = reset_sg;

    m_curr_algo.setFont(m_font);
    m_curr_algo.setString("Current Algo: "+m_algo);
    m_curr_algo.setPosition(sf::Vector2f(10,750));
}

bool GUI::Sidebar::mouseNearSidebar(sf::RenderWindow &window, int spacing) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    return m_sidebar_background.getGlobalBounds().contains(sf::Vector2f(mouse_pos.x+spacing, mouse_pos.y+spacing)) ||
            m_sidebar_background.getGlobalBounds().contains(sf::Vector2f(mouse_pos.x+spacing, mouse_pos.y-spacing)) ||
            m_sidebar_background.getGlobalBounds().contains(sf::Vector2f(mouse_pos.x-spacing, mouse_pos.y+spacing)) ||
            m_sidebar_background.getGlobalBounds().contains(sf::Vector2f(mouse_pos.x-spacing, mouse_pos.y-spacing));
}

std::string GUI::Sidebar::update(Viz &gs_viz, sf::Event& e, sf::RenderWindow& window) {
    m_algo_selector.update(e, window);
    if(m_algo_selector.getState()) {
        m_algo_selector.setState(false);
        std::string previous = m_algo;
        AlgoSelect as(m_font, {"BFS", "DFS", "IDS", "A*", "Greedy"}, 2, 40);
        m_algo = as.getAlgo();
        if(m_algo.size() == 0)
            m_algo = previous;
        m_curr_algo.setString("Current Algo: "+m_algo);
    }

    m_clear_all.update(e, window);
    if(m_clear_all.getState())
        gs_viz.clearGraph(); 

    m_clear_edges.update(e, window);
    if(m_clear_edges.getState())
        gs_viz.clearEdges(); 
    
    m_reset_sg_nodes.update(e, window);
    if(m_reset_sg_nodes.getState())
        gs_viz.resetSGNodes(); 

    return m_algo;
}

void GUI::Sidebar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sidebar_background, states);
    target.draw(m_algo_selector, states);
    target.draw(m_clear_all, states);
    target.draw(m_clear_edges, states);
    target.draw(m_reset_sg_nodes, states);

    target.draw(m_curr_algo, states);
}
