#pragma once

#include <iostream>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shape.hpp>

class CShapeDecorator : public sf::Shape
{
public:
    CShapeDecorator(std::shared_ptr<sf::Shape> shape);

    std::size_t getPointCount() const override;
    sf::Vector2f getPoint(std::size_t index) const override;;

    virtual float GetArea() const = 0;
    virtual float GetPerimeter() const = 0;
    virtual std::string ToString() const = 0;

    virtual void Draw(sf::RenderWindow& window) const = 0;

private:
    std::shared_ptr<sf::Shape> m_shape;
};
