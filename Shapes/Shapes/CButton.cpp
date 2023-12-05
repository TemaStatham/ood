#include "CButton.h"

CButton::CButton(
    const std::string& text,
    sf::Color color,
    sf::Vector2f position,
    sf::Vector2f size,
    ICommand* command
) :
    m_command(command)
{
    // Создаем прямоугольник для кнопки
    m_buttonRect.setSize(size);
    m_buttonRect.setPosition(position);
    m_buttonRect.setFillColor(color); // Цвет кнопки

    // Создаем текст на кнопке
    if (m_font.loadFromFile("font.ttf")) {
        m_text.setFont(m_font);
        m_text.setString(text);
        m_text.setFillColor(sf::Color::Black);
        m_text.setCharacterSize(20);
        m_text.setPosition(position);
    }

    // Выравнивание текста по центру кнопки
    sf::FloatRect textBounds = m_buttonRect.getLocalBounds();
    m_text.setOrigin(textBounds.left + textBounds.width / 2.0f,
        textBounds.top + textBounds.height / 2.0f);
    m_text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
}

void CButton::Draw(sf::RenderWindow& window) const
{
    window.draw(m_buttonRect);
    window.draw(m_text);
}

bool CButton::IsPointInButton(sf::Vector2f point) const
{
    return m_buttonRect.getGlobalBounds().contains(point);
}

void CButton::PressButton() const
{
    m_command->Execute();
}
