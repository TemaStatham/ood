#pragma once

#include <iostream>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shape.hpp>

class CShapeDecorator : sf::Shape
{
public:
    CShapeDecorator();
    CShapeDecorator(std::shared_ptr<sf::Shape> shape);

    std::size_t getPointCount() const override;
    sf::Vector2f getPoint(std::size_t index) const override;

    virtual float GetPerimeter() const;
    virtual float GetArea() const;
    virtual std::string ToString() const;

    virtual void Draw(sf::RenderWindow& window);
    virtual void SetPosition(float x, float y);

    virtual void SetFillColor(sf::Color color);
    virtual void SetOutlineColor(sf::Color color);
    virtual void SetOutlineThickness(float thickness);

    virtual sf::FloatRect GetGlobalBounds() const;
    virtual sf::Vector2f GetPosition() const;

    void SetSelected(bool flag);
    bool IsSelected() const;

    virtual ~CShapeDecorator() = default;

private:
    std::shared_ptr<sf::Shape> m_shape;
    bool m_selected = false;
};
