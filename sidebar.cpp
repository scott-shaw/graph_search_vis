#include "sidebar.h"
#include "start.h"
#include <iostream>

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
    bool algo_sel_state = m_algo_selector.getState();
    if(algo_sel_state != true && algo_sel_state != false)
        algo_sel_state = false;
    if(algo_sel_state) {
        m_algo_selector.setState(false);
        m_algo = chooseAlgo();
        m_curr_algo.setString("Current Algo: "+m_algo);
    }
    m_clear_all.update(e, window);
    bool clear_all_state = m_clear_all.getState();
    if(clear_all_state != true && clear_all_state != false)
        clear_all_state = false;
    if(clear_all_state) {
        gs_viz.clearGraph(); 
    }

    m_clear_edges.update(e, window);
    bool clear_edges_state = m_clear_edges.getState();
    if(clear_edges_state != true && clear_edges_state != false)
        clear_edges_state = false;
    if(clear_edges_state) {
        gs_viz.clearEdges(); 
    }
    
    m_reset_sg_nodes.update(e, window);
    bool reset_sg_state = m_reset_sg_nodes.getState();
    if(reset_sg_state != true && reset_sg_state != false)
        reset_sg_state = false;
    if(reset_sg_state) {
        gs_viz.resetSGNodes(); 
    }

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
