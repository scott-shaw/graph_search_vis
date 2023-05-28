#include "algoselect.h"
#include <iostream>

GUI::AlgoSelect::AlgoSelect(const sf::Font &font, const std::vector<std::string> &algos, const int &cols, const int &char_sz) {
    int col_sz = (algos.size()+cols-1)/cols;
    sf::Color background_color(10,10,10);   

    int i = 0;
    for(int c=0; c<cols; c++) {
        for(int j=0; j<col_sz; j++) {
            if(i >= algos.size())
                break;
            GUI::Button btn(sf::Vector2f(char_sz+(char_sz*3*c), char_sz+(j*char_sz*2)), font, algos.at((c*col_sz)+j), char_sz);
            btn.setButtonColor(sf::Color(40,40,40));
            m_buttons.push_back(btn);
            i++;
        }
    }
   
    // make window according to size buttons need
    int x_max = 0;
    int y_max = 0;
    for(auto btn : m_buttons) {
        sf::FloatRect btn_rect = btn.getRect().getGlobalBounds();
        if(btn_rect.left+btn_rect.width > x_max)
            x_max = btn_rect.left+btn_rect.width;
        if(btn_rect.top+btn_rect.height > y_max)
            y_max = btn_rect.top+btn_rect.height;
    }
    sf::RenderWindow m_window(sf::VideoMode(x_max+char_sz, y_max+char_sz), "Search Algorithm Selector");
    m_window.setFramerateLimit(60);

    while(m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    m_window.close();
                case sf::Event::MouseButtonPressed:
                    for(auto btn : m_buttons) {
                        if(btn.getRect().getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                            m_algo = btn.getText();
                            m_window.close();
                        }
                    }
            }
        }
        m_window.clear(background_color);
        for(auto btn : m_buttons)
            m_window.draw(btn);
        m_window.display();
    }
}

std::string GUI::AlgoSelect::getAlgo() const {
    return m_algo;
}
