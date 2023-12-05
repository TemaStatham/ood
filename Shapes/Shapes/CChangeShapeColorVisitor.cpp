#include "CChangeShapeColorVisitor.h"

CChangeShapeColorVisitor::CChangeShapeColorVisitor(sf::Color color)
    :m_color(color)
{
}

void CChangeShapeColorVisitor::VisitShape(CShapeDecorator* shape) const
{
    shape->SetFillColor(m_color);
}
