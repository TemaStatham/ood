#pragma once

#include "CBuilder.h"
#include "CCircleDecorator.h"

class CCircleBuilder : public CBuilder
{
public:
    CCircleBuilder(const std::vector<float>& params);
    void SetShape() override;
    void SetPosition() override;
private:
    sf::Vector2f m_center;
    float m_radius;
};
