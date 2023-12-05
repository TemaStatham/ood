#include "CComposite.h"

CComposite::CComposite()
    : CShapeDecorator()
{
}

void CComposite::Add(std::shared_ptr<CShapeDecorator> shape) {
    m_shapes.push_back(shape);
}

void CComposite::Remove(std::shared_ptr<CShapeDecorator> shape) {
    m_shapes.remove(shape);
}

void CComposite::SetPosition(float x, float y) {
    sf::Vector2f targetPosition(x, y);
    sf::Vector2f currentPosition = GetPosition();
    sf::Vector2f offset = targetPosition - currentPosition;

    for (std::shared_ptr<CShapeDecorator> shape : m_shapes) {
        sf::Vector2f shapePosition = shape->GetPosition();
        shape->SetPosition(shapePosition.x + offset.x, shapePosition.y + offset.y);
    }
}

void CComposite::SetFillColor(sf::Color color)
{
    for (auto& shape : m_shapes) {
        shape->SetFillColor(color);
    }
}

void CComposite::SetOutlineColor(sf::Color color)
{
    for (auto& shape : m_shapes) {
        shape->SetOutlineColor(color);
    }
}

void CComposite::SetOutlineThickness(float thickness)
{
    for (auto& shape : m_shapes) {
        shape->SetOutlineThickness(thickness);
    }
}

void CComposite::Draw(sf::RenderWindow& window) {
    if (IsSelected()) {
        sf::FloatRect bounds = GetGlobalBounds();
        sf::RectangleShape frame;
        frame.setSize(sf::Vector2f(bounds.width, bounds.height));
        frame.setPosition(sf::Vector2f(bounds.left, bounds.top));
        frame.setFillColor(sf::Color::Transparent);
        frame.setOutlineThickness(1);
        frame.setOutlineColor(sf::Color::White);
        window.draw(frame);
    }
    for (std::shared_ptr<CShapeDecorator> shape : m_shapes) {
        /*window.draw(*shape);*/
        shape->SetSelected(false);
        shape->Draw(window);
    }
}

sf::FloatRect CComposite::GetGlobalBounds() const {
    auto initialFrame = m_shapes.front()->GetGlobalBounds();
    sf::Vector2f leftTop(initialFrame.left, initialFrame.top);
    sf::Vector2f rightBottom(leftTop.x + initialFrame.width,
        leftTop.y + initialFrame.height);

    for (std::shared_ptr<CShapeDecorator> shape : m_shapes) {
        auto shapeFrame = shape->GetGlobalBounds();

        if (leftTop.x > shapeFrame.left)
            leftTop.x = shapeFrame.left;
        if (leftTop.y > shapeFrame.top)
            leftTop.y = shapeFrame.top;
        if (rightBottom.x < shapeFrame.left + shapeFrame.width)
            rightBottom.x = shapeFrame.left + shapeFrame.width;
        if (rightBottom.y < shapeFrame.top + shapeFrame.height)
            rightBottom.y = shapeFrame.top + shapeFrame.height;
    }

    return sf::FloatRect(leftTop.x, leftTop.y,
        abs(rightBottom.x - leftTop.x),
        abs(rightBottom.y - leftTop.y));
}

sf::Vector2f CComposite::GetPosition() const {
    auto bound = GetGlobalBounds();
    return sf::Vector2f(bound.left, bound.top);
}

list<std::shared_ptr<CShapeDecorator>> CComposite::GetShapes() const {
    return m_shapes;
}

std::stringstream CComposite::GetInfo() const
{
    std::stringstream sstream;

    sstream << "COMPOSIT: " << m_shapes.size() << std::endl;

    for (auto shape : m_shapes)
    {
        auto shapeStream = shape->GetInfo();
        sstream << shapeStream.str();
    }

    return sstream;
}

CComposite::~CComposite()
{
}
