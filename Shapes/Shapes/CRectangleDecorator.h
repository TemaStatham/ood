#pragma once

#include "CShapeDecorator.h"

class CRectangleDecorator : public CShapeDecorator
{
public:
    CRectangleDecorator(std::shared_ptr<sf::RectangleShape> shape,
        sf::Vector2f const& leftTop,
        float heigth,
        float width
    );

    float GetArea() const override;
    float GetPerimeter() const override;
    std::string ToString() const override;

    void Draw(sf::RenderWindow& window) override;

    sf::Vector2f GetLeftTop() const;
    sf::Vector2f GetRightBottom() const;
    float GetHeigth() const;
    float GetWidth() const;

    ~CRectangleDecorator();

private:

    sf::Vector2f m_leftTop;
    float m_heigth;
    float m_width;
};
