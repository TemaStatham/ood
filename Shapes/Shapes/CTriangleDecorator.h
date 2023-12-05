#pragma once

#include "CShapeDecorator.h"

float GetLineSize(sf::Vector2f startLOfLine, sf::Vector2f endLOfLine);

class CTriangleDecorator : public CShapeDecorator
{
public:
    CTriangleDecorator(std::shared_ptr<sf::ConvexShape> shape,
        sf::Vector2f const& vertex1,
        sf::Vector2f const& vertex2,
        sf::Vector2f const& vertex3
    );

    float GetArea() const override;
    float GetPerimeter() const override;
    std::string ToString() const override;

    void Draw(sf::RenderWindow& window) const override;

    sf::Vector2f GetVertex1() const;
    sf::Vector2f GetVertex2() const;
    sf::Vector2f GetVertex3() const;

    ~CTriangleDecorator();
private:

    sf::Vector2f m_vertex1;
    sf::Vector2f m_vertex2;
    sf::Vector2f m_vertex3;

};
