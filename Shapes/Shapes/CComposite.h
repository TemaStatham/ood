#pragma once
#include <memory>
#include <string>
#include <list>

#include <SFML/Graphics.hpp>

#include "CShapeDecorator.h"

using namespace std;

class CComposite : public CShapeDecorator
{
public:
    CComposite();

    void Add(std::shared_ptr<CShapeDecorator> shape);
    void Remove(std::shared_ptr<CShapeDecorator> shape);

    void SetPosition(float x, float y) override;
    void SetFillColor(sf::Color color) override;
    void SetOutlineColor(sf::Color color) override;
    void SetOutlineThickness(float thickness) override;
    void Draw(sf::RenderWindow& window) override;

    sf::FloatRect GetGlobalBounds() const override;
    sf::Vector2f GetPosition() const override;

    list<std::shared_ptr<CShapeDecorator>> GetShapes() const;

    std::stringstream GetInfo() const override;

private:
    list<std::shared_ptr<CShapeDecorator>> m_shapes;
};
