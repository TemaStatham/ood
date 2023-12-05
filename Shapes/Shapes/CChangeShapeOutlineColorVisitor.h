#pragma once

#include "IVisitor.h"
#include "CShapeDecorator.h"

class CChangeShapeOutlineColorVisitor : public IVisitor
{
public:
    CChangeShapeOutlineColorVisitor(sf::Color color);

    void VisitShape(CShapeDecorator* shape) const override;

private:
    sf::Color m_color;
};
