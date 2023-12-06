#include "CShapeDecorator.h"

CShapeDecorator::CShapeDecorator()
    : m_shape()
{
}

CShapeDecorator::CShapeDecorator(std::shared_ptr<sf::Shape> shape)
    : m_shape(shape)
{
}

std::size_t CShapeDecorator::getPointCount() const
{
    return std::size_t();
}

sf::Vector2f CShapeDecorator::getPoint(std::size_t index) const
{
    return sf::Vector2f();
}

float CShapeDecorator::GetPerimeter() const
{
    return 0.0f;
}

float CShapeDecorator::GetArea() const
{
    return 0.0f;
}

std::string CShapeDecorator::ToString() const
{
    return std::string();
}

void CShapeDecorator::Draw(sf::RenderWindow& window)
{
    if (IsSelected()) {
        sf::FloatRect globalBounds = GetGlobalBounds();
        sf::RectangleShape frame;
        frame.setSize(sf::Vector2f(globalBounds.width, globalBounds.height));
        frame.setPosition(sf::Vector2f(globalBounds.left, globalBounds.top));
        frame.setFillColor(sf::Color(0, 0, 0, 0));
        frame.setOutlineThickness(1);
        frame.setOutlineColor(sf::Color::White);
        window.draw(frame);
    }
    window.draw(*m_shape);
}

void CShapeDecorator::SetPosition(float x, float y)
{
    m_shape->setPosition(x, y);
}

void CShapeDecorator::SetFillColor(sf::Color color)
{
    m_shape->setFillColor(color);
}

void CShapeDecorator::SetOutlineColor(sf::Color color)
{
    m_shape->setOutlineColor(color);
}

void CShapeDecorator::SetOutlineThickness(float thickness)
{
    m_shape->setOutlineThickness(thickness);
}

sf::FloatRect CShapeDecorator::GetGlobalBounds() const
{
    return m_shape->getGlobalBounds();
}

sf::Vector2f CShapeDecorator::GetPosition() const
{
    return m_shape->getPosition();
}

void CShapeDecorator::SetSelected(bool flag)
{
    if (this == nullptr) {
        return;
    }
    m_selected = flag;
}

bool CShapeDecorator::IsSelected() const
{
    return m_selected;
}
