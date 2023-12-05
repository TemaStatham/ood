#pragma once

#include "CShapeDecorator.h"
#include "CCircleDecorator.h"
#include "IBuilder.h"

class CBuilder : public IBuilder
{
public:
    CBuilder(float fillColor, float outlineColor, float outlineThickness);

    std::shared_ptr<CShapeDecorator> GetResult() const override;

    void SetShape(std::shared_ptr<CShapeDecorator> shape);
    void SetPosition(float x, float y);

private:
    void SetFillColor();
    void SetOutlineColor();
    void SetOutlineThickness();

    std::shared_ptr<CShapeDecorator> m_shape;
    float m_fillColor;
    float m_outlineColor;
    float m_outlineThickness;
};
