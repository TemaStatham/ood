#include "CTriangleDecorator.h"
#include "math.h"
#include <sstream>
#include <cstdint>

float GetLineSize(sf::Vector2f startLOfLine, sf::Vector2f endLOfLine)
{
    float dx = startLOfLine.x - endLOfLine.x;
    float dy = startLOfLine.y - endLOfLine.y;
    return std::sqrt(dx * dx + dy * dy);
};

CTriangleDecorator::CTriangleDecorator(std::shared_ptr<sf::ConvexShape> shape,
    sf::Vector2f const& vertex1,
    sf::Vector2f const& vertex2,
    sf::Vector2f const& vertex3) :
    CShapeDecorator(shape),
    m_vertex1(vertex1),
    m_vertex2(vertex2),
    m_vertex3(vertex3)
{
};

float CTriangleDecorator::GetArea() const
{
    float halfOfPerimeter = GetPerimeter() / 2;

    float line1 = GetLineSize(m_vertex1, m_vertex2);
    float line2 = GetLineSize(m_vertex2, m_vertex3);
    float line3 = GetLineSize(m_vertex3, m_vertex1);

    float area = sqrt(halfOfPerimeter * (halfOfPerimeter - line1) * (halfOfPerimeter - line2) * (halfOfPerimeter - line3));

    return area;
};

float CTriangleDecorator::GetPerimeter() const
{
    float line1Size = GetLineSize(m_vertex1, m_vertex2);
    float line2Size = GetLineSize(m_vertex2, m_vertex3);
    float line3Size = GetLineSize(m_vertex3, m_vertex1);

    float perimeter = line1Size + line2Size + line3Size;

    return perimeter;
};

std::string CTriangleDecorator::ToString() const
{
    std::ostringstream strm;
    strm
        << "Triangle:"
        << "  p: " << GetPerimeter() << "  s: " << GetArea() << "\n";

    return strm.str();
};

void CTriangleDecorator::Draw(sf::RenderWindow& window) const
{
    CShapeDecorator::Draw(window);
};

CTriangleDecorator::~CTriangleDecorator()
{
};

sf::Vector2f CTriangleDecorator::GetVertex1() const
{
    return m_vertex1;
};

sf::Vector2f CTriangleDecorator::GetVertex2() const
{
    return m_vertex2;
};

sf::Vector2f CTriangleDecorator::GetVertex3() const
{
    return m_vertex3;
};
