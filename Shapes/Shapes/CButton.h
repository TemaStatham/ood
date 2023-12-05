#pragma once

#include <SFML/Graphics.hpp>
#include "ICommand.h"

class CButton {
public:
    CButton(
        const std::string& text,
        sf::Color color,
        sf::Vector2f position,
        sf::Vector2f size,
        ICommand* command
    );

    void Draw(sf::RenderWindow& window) const;
    bool IsPointInButton(sf::Vector2f point) const;
    void PressButton() const;

private:
    sf::RectangleShape m_buttonRect;
    sf::Text m_text;
    sf::Font m_font;

    ICommand* m_command;
};
