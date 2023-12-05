#include "CChangeShapeOutlineColorVisitor.h"

CChangeShapeOutlineColorVisitor::CChangeShapeOutlineColorVisitor(sf::Color color)
    :m_color(color)
{
}

void CChangeShapeOutlineColorVisitor::VisitShape(CShapeDecorator* shape) const
{
    shape->SetOutlineColor(m_color);
}
