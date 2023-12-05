#pragma once

#include "CCircleDecorator.h"
#include "CRectangleDecorator.h"
#include "CTriangleDecorator.h"
#include "CShapeDecorator.h"
#include <functional>
#include <map>
#include <memory>
#include <variant>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include <string>
#include <regex>

sf::Vector2f FindTopLeft(const sf::Vector2f& point1, const sf::Vector2f& point2);
void ParseInputString(const std::string& input, float& pref, float& num1, float& num2);
sf::Vector2f ParseCoordinate(const std::string& input);
float ParseRadius(const std::string& input);

class CShapeController
{
public:
    CShapeController(std::vector<std::shared_ptr<CShapeDecorator>>& shapes, std::istream& in, std::ostream& out);

    void Start();

    ~CShapeController() = default;

private:
    using Handler = std::function<std::shared_ptr<CShapeDecorator>()>;

    void PrintToOut();

    std::shared_ptr<CShapeDecorator> CreateShape(const std::string& str) const;

    std::shared_ptr<CTriangleDecorator> CreateTriangle() const;
    std::shared_ptr<CRectangleDecorator> CreateRectangle() const;
    std::shared_ptr<CCircleDecorator> CreateCircle() const;

    using ActionMap = std::map<std::string, Handler>;

    void Help();

    void Draw();

    std::vector<std::shared_ptr<CShapeDecorator>>& m_shapes;
    std::istream& m_in;
    std::ostream& m_out;

    const ActionMap m_actionMap;
};
