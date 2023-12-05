#include "CTriangleBuilder.h"

CTriangleBuilder::CTriangleBuilder(const std::vector<float>& params)
    :CBuilder(params[0], params[1], params[2]),
    m_vertex1(params[3], params[4]),
    m_vertex2(params[5], params[6]),
    m_vertex3(params[6], params[8])
{

}

void CTriangleBuilder::SetShape()
{
    auto triangleShape = std::make_shared<sf::ConvexShape>();

    triangleShape->setPointCount(3);
    triangleShape->setPoint(0, m_vertex1);
    triangleShape->setPoint(1, m_vertex2);
    triangleShape->setPoint(2, m_vertex3);

    CTriangleDecorator triangle(triangleShape, m_vertex1, m_vertex2, m_vertex3);

    CBuilder::SetShape(std::make_shared<CTriangleDecorator>(triangle));

    /*CBuilder::SetShape(std::make_shared<CCircleDecorator>(
        new CTriangleDecorator(
            std::make_shared<sf::ConvexShape>(sf::ConvexShape()),
            m_vertex1,
            m_vertex2,
            m_vertex3
        )
    ));*/
}

void CTriangleBuilder::SetPosition()
{
    CBuilder::SetPosition(m_vertex1.x, m_vertex1.y);
}
