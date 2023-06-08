#include "sidebar.h"
#include <iostream>
#include "algoselect.h"

GUI::Sidebar::Sidebar(const sf::Font &font, const std::string &algo, const int &spacing, const int &char_size) {
    m_font = font;
    m_algo = algo;

    std::vector<std::string> btn_titles{"Algorithm\nSelection", "CE All", "CE Edges", "CE S/G"};
    int y_pos = spacing;
    for(int i=0; i<btn_titles.size(); i++) {
        GUI::Button b(sf::Vector2f(spacing,y_pos), m_font, btn_titles.at(i), char_size, sf::Color(30, 0, 125));
        y_pos = b.getRect().getGlobalBounds().top + b.getRect().getGlobalBounds().height + spacing;
        m_buttons.push_back(b);
    }
    
    int x_max = 0;
    int y_max = 0;
    for(auto b : m_buttons) {
        sf::FloatRect btn_rect = b.getRect().getGlobalBounds();
        if(btn_rect.left+btn_rect.width > x_max)
            x_max = btn_rect.left+btn_rect.width;
        if(btn_rect.top+btn_rect.height > y_max)
            y_max = btn_rect.top+btn_rect.height;
    }

    m_sidebar_background = sf::RoundedRectangleShape(sf::Vector2f(x_max+spacing, y_max+spacing), 10, 10);
    m_sidebar_background.setPosition(sf::Vector2f(0,0));
    m_sidebar_background.setFillColor(sf::Color(50,50,50));

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
    m_buttons.at(0).update(e, window);
    if(m_buttons.at(0).getState()) {
        m_buttons.at(0).setState(false);
        std::string previous = m_algo;
        AlgoSelect as(m_font, {"BFS", "DFS", "IDS", "A*", "Greedy", "UCS"}, 2, 40);
        m_algo = as.getAlgo();
        if(m_algo.size() == 0)
            m_algo = previous;
        m_curr_algo.setString("Current Algo: "+m_algo);
    }

    m_buttons.at(1).update(e, window);
    if(m_buttons.at(1).getState())
        gs_viz.clearGraph(); 

    m_buttons.at(2).update(e, window);
    if(m_buttons.at(2).getState())
        gs_viz.clearEdges(); 
    
    m_buttons.at(3).update(e, window);
    if(m_buttons.at(3).getState())
        gs_viz.resetSGNodes(); 

    return m_algo;
}

void GUI::Sidebar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sidebar_background, states);
    for(GUI::Button b : m_buttons)
        target.draw(b, states);
    target.draw(m_curr_algo, states);
}
