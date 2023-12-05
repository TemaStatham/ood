#pragma once

#include "CBuilder.h"
#include "CTriangleDecorator.h"

class CTriangleBuilder : public CBuilder
{
public:
    CTriangleBuilder(const std::vector<float>& params);
    void SetShape() override;
    void SetPosition() override;
private:
    sf::Vector2f m_vertex1;
    sf::Vector2f m_vertex2;
    sf::Vector2f m_vertex3;
};
