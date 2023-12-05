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
    CBuilder::SetShape(std::make_shared<CCircleDecorator>(
        new CRectangleDecorator(std::make_shared<sf::RectangleShape>(
            new sf::RectangleShape()),
            m_leftTop,
            m_height,
            m_width
        )
    ));
}

void CRectangleBuilder::SetPosition()
{
    CBuilder::SetPosition(m_leftTop.x, m_leftTop.y);
}
