#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <regex>
#include <map>
#include <stack>

#include "CShapeDecorator.h"
#include "CShapeDecorator.h"
#include "CCircleDecorator.h"
#include "CRectangleDecorator.h"
#include "CTriangleDecorator.h"
#include "CComposite.h"
#include "ShapeStyle.h"
#include "IVisitor.h"
#include "CChangeOutlineThicknessVisitor.h"
#include "CChangeShapeOutlineColorVisitor.h"
#include "CChangeShapeColorVisitor.h"
#include "CMemento.h"

class CCanvas {
public:
    CCanvas(sf::RenderWindow& window, std::istream& in);

    void CreateShape(const std::string& typeOfFigureAsString);
    void CreateCircle(sf::Vector2f center, float radius, ShapeStyle* style);
    void CreateRectangle(sf::Vector2f leftTop, float width, float height, ShapeStyle* style);
    void CreateTriangle(sf::Vector2f firstPoint, sf::Vector2f secondPoint, sf::Vector2f thirdPoint, ShapeStyle* style);

    void ChangeShapeColor(sf::Color color);
    void ChangeShapeOutlineColor(sf::Color color);
    void ChangeOutlineThickness(float thickness);
    void ChangeCoordinatesOfShape();

    std::vector<std::shared_ptr<CShapeDecorator>> GetShapes() const;
    std::vector<std::shared_ptr<CShapeDecorator>> GetSelectedShapes() const;

    void AddNewSelectedShape();
    void DeleteSelectedShape();
    void ResetSelectedShapes();
    void ResetIndex();

    void GroupShapes();
    void UngroupShapes();

    void SetCursorPosition(sf::Vector2i pos);
    void SetOffsetCoordinates(sf::Vector2f coordinates);

    void Draw();
    void SelectMultipleShape();
    void SelectOneMoreShape();
    void SetChoose();
    void Select();

    void Accept(IVisitor* visitor);

    void Backup();
    void Undo();

    void Reset();
    void AddNewShape(std::shared_ptr<CShapeDecorator> shape);

private:
    using Handler = std::function<void()>;
    using ActionMap = std::map<std::string, Handler>;
    void ConfigureShape(std::shared_ptr<sf::Shape> shape, ShapeStyle* style);

    void ParseInputString(const std::string& input, float& pref, float& num1, float& num2);
    sf::Vector2f ParseCoordinate(const std::string& input);
    float ParseRadius(const std::string& input);

    void ReadCircleProperties();
    void ReadRectangleProperties();
    void ReadTriangleProperties();

    std::vector<std::shared_ptr<CShapeDecorator>> m_shapes;
    std::vector<std::shared_ptr<CShapeDecorator>> m_selectedShapes;

    std::istream& m_in;
    sf::RenderWindow& m_window;

    int m_indexCurrentShape = -1;
    sf::Vector2i m_cursorPosition;
    sf::Vector2f m_offsetCoordinates;

    const ActionMap m_actionMap;

    std::stack<CMemento*> m_history;
};
