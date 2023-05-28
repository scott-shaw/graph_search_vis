#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

namespace GUI {
    class Button : public sf::Drawable {
    public:
        Button();
        Button(const sf::Vector2f &position, const sf::Font &font, const std::string &s, const int &char_size);
        ~Button();
        bool onButton(sf::RenderWindow &window);
        void update(sf::Event &e, sf::RenderWindow &window);
        void setButtonColor(const sf::Color &color);
        void setTextColor(const sf::Color &color);
        bool getState() const;
        void setState(const bool &state);
        sf::RectangleShape getRect() const;
        std::string getText() const;

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::RectangleShape m_button;
        sf::Vector2f m_position;
        sf::Color m_button_color;
        bool m_state;

        sf::Font m_font;
        sf::Text m_text;
        sf::Color m_text_color;
    };
}


#endif
