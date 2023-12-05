#include "CShapeDecorator.h"

CShapeDecorator::CShapeDecorator(std::shared_ptr<sf::Shape> shape)
    : m_shape(shape)
{
};

std::size_t CShapeDecorator::getPointCount() const
{
    return 0;
};

sf::Vector2f CShapeDecorator::getPoint(std::size_t index) const
{
    return { 0, 0 };
};

void CShapeDecorator::Draw(sf::RenderWindow& window) const
{
    window.draw(*m_shape);
};
