#include "button.h"

GUI::Button::Button() {}

GUI::Button::~Button() {}

GUI::Button::Button(const sf::Vector2f &position, const sf::Font &font, const std::string &s, const int &char_size) {
    m_position = position;
    m_font = font;
    m_button_color = sf::Color(25, 0, 200);
    m_text_color = sf::Color(255,255,255);
    m_state = false;

    m_text.setString(s);
    m_text.setFont(font);
    m_text.setFillColor(m_text_color);
    m_text.setCharacterSize(char_size);
    
    m_button = sf::RoundedRectangleShape(sf::Vector2f(m_text.getGlobalBounds().width*1.25, m_text.getGlobalBounds().height*1.5),10,10);
    m_button.setPosition(m_position);
    m_button.setFillColor(m_button_color);
    
    // center text within button
    m_text.setOrigin(sf::Vector2f(m_text.getGlobalBounds().width,m_text.getGlobalBounds().height) / 2.f + sf::Vector2f(m_text.getLocalBounds().left, m_text.getLocalBounds().top));
    m_text.setPosition(m_button.getPosition() + (m_button.getSize() / 2.f));   
}

bool GUI::Button::onButton(sf::RenderWindow &window) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    return m_button.getGlobalBounds().contains(sf::Vector2f(mouse_pos));
}

void GUI::Button::update(sf::Event& e, sf::RenderWindow& window) {
    bool mouse_on_button = onButton(window);

    if (e.type == sf::Event::MouseButtonPressed) {
        switch(e.mouseButton.button) {
            case sf::Mouse::Left:
                if(mouse_on_button)
                    m_state = true;
            default:
                break;
        }
    }

    if (e.type == sf::Event::MouseButtonReleased) {
        switch(e.mouseButton.button) {
            case sf::Mouse::Left:
                m_state = false;
            default:
                break;
        }
    }

}

bool GUI::Button::getState() const {
    return m_state;
}

void GUI::Button::setState(const bool &state) {
    m_state = state;
}

void GUI::Button::setButtonColor(const sf::Color &color) {
    m_button_color = color;
    m_button.setFillColor(m_button_color);
}

void GUI::Button::setTextColor(const sf::Color &color) {
    m_text_color = color;
    m_text.setFillColor(m_text_color);
}

void GUI::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_button, states);
    target.draw(m_text, states);
}

sf::RoundedRectangleShape GUI::Button::getRect() const {
    return m_button;
}

std::string GUI::Button::getText() const {
    return m_text.getString();
}
