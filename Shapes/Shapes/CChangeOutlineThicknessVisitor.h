#pragma once

#include "IVisitor.h"
#include "CShapeDecorator.h"

class CChangeOutlineThicknessVisitor : public IVisitor
{
public:
    CChangeOutlineThicknessVisitor(int thickness);

    void VisitShape(CShapeDecorator* shape) const override;

private:
    int m_thickness;
};
