#pragma once

#include "CShapeDecorator.h"

class CCircleDecorator : public CShapeDecorator
{
public:
    CCircleDecorator(std::shared_ptr<sf::CircleShape> shape,
        sf::Vector2f const& center,
        float const& radius
    );

    float GetArea() const override;
    float GetPerimeter() const override;
    std::string ToString() const override;

    void Draw(sf::RenderWindow& window) override;

    sf::Vector2f GetCenter() const;
    float GetRadius() const;

    std::stringstream GetInfo() const override;

    ~CCircleDecorator();

private:

    sf::Vector2f m_center;
    float m_radius;
};
