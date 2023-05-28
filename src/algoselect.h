#ifndef ALGOSELECT_H
#define ALGOSELECT_H

#include <SFML/Graphics.hpp>
#include "button.h"

namespace GUI {
    class AlgoSelect {
    public:
        AlgoSelect(const sf::Font &font, const std::vector<std::string> &algos, const int &cols, const int &char_sz=30);
        std::string getAlgo() const;

    private:
        std::string m_algo;
        sf::Font m_font;
        sf::RenderWindow m_window;
        std::vector<GUI::Button> m_buttons;
    };
}

#endif
