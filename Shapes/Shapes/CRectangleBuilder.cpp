#include "CRectangleBuilder.h"

CRectangleBuilder::CRectangleBuilder(const std::vector<float>& params)
    : CBuilder(params[0], params[1], params[2]),
    m_leftTop(sf::Vector2f(params[3], params[4])),
    m_height(params[5]),
    m_width(params[6])
{

}

void CRectangleBuilder::SetShape()
{
    auto rectangleShape = std::make_shared<sf::RectangleShape>();

    rectangleShape->setSize(sf::Vector2f(m_width, m_height));
    rectangleShape->setPosition(m_leftTop);

    CRectangleDecorator rectangle(rectangleShape, m_leftTop, m_height, m_width);

    CBuilder::SetShape(std::make_shared<CRectangleDecorator>(rectangle));

    /*CBuilder::SetShape(std::make_shared<CCircleDecorator>(
        new CRectangleDecorator(
            std::make_shared<sf::RectangleShape>(sf::RectangleShape()),
            m_leftTop,
            m_height,
            m_width
        )
    ));*/
}

void CRectangleBuilder::SetPosition()
{
    CBuilder::SetPosition(m_leftTop.x, m_leftTop.y);
}
