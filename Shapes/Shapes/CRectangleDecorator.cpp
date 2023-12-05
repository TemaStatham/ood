#include "CRectangleDecorator.h"
#include "math.h"
#include <sstream>
#include <cstdint>

CRectangleDecorator::CRectangleDecorator(std::shared_ptr<sf::RectangleShape> shape,
    sf::Vector2f const& leftTop, float heigth, float width) : CShapeDecorator(shape),
    m_leftTop(leftTop),
    m_heigth(heigth),
    m_width(width)
{
};

float CRectangleDecorator::GetArea() const
{
    return (m_heigth * m_width);
};

float CRectangleDecorator::GetPerimeter() const
{
    float perimeter = (m_heigth + m_width) * 2;
    return perimeter;
};

std::string CRectangleDecorator::ToString() const
{
    std::ostringstream strm;
    strm
        << "Rectangle:"
        << "  p: " << GetPerimeter()
        << "  s: " << GetArea() << "\n";

    return strm.str();
};

void CRectangleDecorator::Draw(sf::RenderWindow& window) const
{
    CShapeDecorator::Draw(window);
};

sf::Vector2f CRectangleDecorator::GetLeftTop() const
{
    return m_leftTop;
};

sf::Vector2f CRectangleDecorator::GetRightBottom() const
{
    sf::Vector2f rigthBottom(m_leftTop.x + m_width, m_leftTop.y + m_heigth);
    return rigthBottom;
};

float CRectangleDecorator::GetHeigth() const
{
    return m_heigth;
};

float CRectangleDecorator::GetWidth() const
{
    return m_width;
};

CRectangleDecorator::~CRectangleDecorator()
{
};
