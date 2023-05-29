#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <SFML/Graphics.hpp>
#include "button.h"
#include "viz.h"
#include "rounded_rect.h"

namespace GUI {
    class Sidebar : public sf::Drawable {
    public:
        explicit Sidebar(const sf::Font &font, const std::string &algo, const int &spacing=10, const int &char_size=20);
        bool mouseNearSidebar(sf::RenderWindow &window, int spacing);
        std::string update(Viz &gs_viz, sf::Event &e, sf::RenderWindow &window);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        std::string m_algo; 
        sf::Font m_font;
        sf::RoundedRectangleShape m_sidebar_background;
        std::vector<Button> m_buttons;
        sf::Text m_curr_algo;
    }; 
}

#endif
