#pragma once

#include "CBuilder.h"
#include "CRectangleDecorator.h"

class CRectangleBuilder : public CBuilder
{
public:
    CRectangleBuilder(const std::vector<float>& params);
    void SetShape() override;
    void SetPosition() override;
private:
    sf::Vector2f m_leftTop;
    float m_width;
    float m_height;
};
