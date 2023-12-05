#pragma once

#include <SFML/Graphics.hpp>
#include "CButton.h"
#include "CState.h"
#include "CCanvas.h"
#include "ShapeStyle.h"
#include "CChangeCoordinatesOfShapeCommand.h"
#include "CChangeOutlineThicknessCommand.h"
#include "CChangeShapeColorCommand.h"
#include "CChangeShapeOutlineColorCommand.h"
#include "CSetColorCommand.h"
#include "CSetThicknessCommand.h"
#include "CCircleCreateCommand.h"
#include "CRectangleCreateCommand.h"
#include "CTriangleCreateCommand.h"
#include "CUndoCommand.h"

class CState;

class CToolbar {
public:
    CToolbar(sf::RenderWindow& window, CState* state, CCanvas* canvas);

    void ChangeShapeColor();
    void ChangeShapeOutlineColor();
    void ChangeOutlineThickness();
    void ChangeCoordinatesOfShape();

    void CreateCircle();
    void CreateTriangle();
    void CreateRectangle();

    void TransitionTo(CState* state);

    void Draw();

    bool PressedToButton() const;
    void SetCursorPosition(sf::Vector2i pos);
    void SetSelectedColor(sf::Color color);
    void SetSelectedThickness(float thickness);

    CState* GetState() const;
    sf::Color GetSelectedColor() const;
    float GetSelectedThickness() const;
    vector<CButton*> GetButtons() const;

    void Undo();

private:
    sf::RenderWindow& m_window;
    std::vector<CButton*> m_buttons;
    CState* m_state;
    sf::Vector2i m_cursorPosition;
    CCanvas* m_canvas;
    sf::Color m_selectedColor = sf::Color::Red;
    float m_selectedThickness = 1;
};
