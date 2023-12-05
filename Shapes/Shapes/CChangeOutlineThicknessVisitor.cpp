#include "CChangeOutlineThicknessVisitor.h"

CChangeOutlineThicknessVisitor::CChangeOutlineThicknessVisitor(int thickness)
    :m_thickness(thickness)
{
}

void CChangeOutlineThicknessVisitor::VisitShape(CShapeDecorator* shape) const
{
    shape->SetOutlineThickness(m_thickness);
}
