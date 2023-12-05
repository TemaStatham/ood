#include "CCircleDecorator.h"
#include "math.h"
#include <sstream>
#include <cstdint>
#include <cmath>

#define _USE_MATH_DEFINES
#define M_PI           3.14159265358979323846

CCircleDecorator::CCircleDecorator(std::shared_ptr<sf::CircleShape> shape,
    sf::Vector2f const& center, float const& radius)
    : CShapeDecorator(shape),
    m_center(center),
    m_radius(radius)
{
};

float CCircleDecorator::GetArea() const
{
    float area = static_cast<float>(pow(m_radius, 2) * M_PI);
    return area;
};

float CCircleDecorator::GetPerimeter() const
{
    float perimeter = static_cast<float>(M_PI * 2 * m_radius);
    return perimeter;
};

std::string CCircleDecorator::ToString() const
{
    std::ostringstream strm;
    strm
        << "Circle:"
        << "  p: " << GetPerimeter()
        << "  s: " << GetArea() << "\n";

    return strm.str();
}

void CCircleDecorator::Draw(sf::RenderWindow& window)
{
    CShapeDecorator::Draw(window);
}

float CCircleDecorator::GetRadius() const
{
    return m_radius;
}

std::stringstream CCircleDecorator::GetInfo() const
{
    std::stringstream sstream;

    sstream << "CIRCLE: "
        << "C=" << m_center.x << "," << m_center.y << "; "
        << "R=" << m_radius << ";"
        << std::endl;

    return sstream;
}

CCircleDecorator::~CCircleDecorator()
{
}
;

sf::Vector2f CCircleDecorator::GetCenter() const
{
    return m_center;
};
