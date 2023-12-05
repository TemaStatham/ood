#pragma once

#include "IVisitor.h"
#include "CShapeDecorator.h"

class CChangeShapeColorVisitor : public IVisitor
{
public:
    CChangeShapeColorVisitor(sf::Color color);

    void VisitShape(CShapeDecorator* shape) const override;

private:
    sf::Color m_color;
};
