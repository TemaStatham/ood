#include "CBuilder.h"

CBuilder::CBuilder(float fillColor, float outlineColor, float outlineThickness)
    : m_shape(nullptr),
    m_fillColor(fillColor),
    m_outlineColor(outlineColor),
    m_outlineThickness(outlineThickness)
{
}

std::shared_ptr<CShapeDecorator> CBuilder::GetResult() const
{
    return m_shape;
}

void CBuilder::SetShape(std::shared_ptr<CShapeDecorator> shape)
{
    m_shape = shape;
    SetFillColor();
    SetOutlineColor();
    SetOutlineThickness();
}

void CBuilder::SetPosition(float x, float y)
{
    m_shape->SetPosition(x, y);
}

void CBuilder::SetFillColor()
{
    m_shape->SetFillColor(sf::Color(m_fillColor));
}

void CBuilder::SetOutlineColor()
{
    m_shape->SetFillColor(sf::Color(m_outlineColor));
}

void CBuilder::SetOutlineThickness()
{
    m_shape->SetOutlineThickness(m_outlineThickness);
}
