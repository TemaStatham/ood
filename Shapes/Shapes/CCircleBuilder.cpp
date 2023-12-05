#include "CCircleBuilder.h"

CCircleBuilder::CCircleBuilder(const std::vector<float>& params)
    : CBuilder(params[0], params[1], params[2]), m_center(params[3], params[4]), m_radius(params[5])
{

}

void CCircleBuilder::SetShape()
{
    auto circleShape = std::make_shared<sf::CircleShape>();

    circleShape->setPosition(m_center);
    circleShape->setRadius(m_radius);

    CCircleDecorator circle(circleShape, m_center, m_radius);

    CBuilder::SetShape(std::make_shared<CCircleDecorator>(circle));
    /* CBuilder::SetShape(std::make_shared<CCircleDecorator>(
         new CCircleDecorator(
             std::make_shared<sf::CircleShape>(sf::CircleShape()),
             m_center,
             m_radius
         )
     ));*/
}

void CCircleBuilder::SetPosition()
{
    CBuilder::SetPosition(m_center.x, m_center.y);
}
