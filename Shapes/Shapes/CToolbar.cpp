#include "CToolbar.h"

const float STANDART_THICKNESS = 5;

ShapeStyle CIRCLE_STYLE = ShapeStyle{ STANDART_THICKNESS, sf::Color::Blue, sf::Color::Blue };
const sf::Vector2f CIRCLE_CENTER = sf::Vector2f{ 300, 600 };
const float CIRCLE_RADIUS = 100;

ShapeStyle RECTANGLE_STYLE = ShapeStyle{ STANDART_THICKNESS, sf::Color::Black, sf::Color::Green };
const sf::Vector2f RECTANGLE_LEFT_TOP = sf::Vector2f{ 700, 200 };
const float RECTANGLE_WIDTH = 100;
const float RECTANGLE_HEIGHT = 100;

ShapeStyle TRIANGLE_STYLE = ShapeStyle{ STANDART_THICKNESS, sf::Color::Magenta, sf::Color::Red };
const sf::Vector2f TRIANGLE_FIRST_POINT = sf::Vector2f{ 10, 500 };
const sf::Vector2f TRIANGLE_SECOND_POINT = sf::Vector2f{ 140, 300 };
const sf::Vector2f TRIANGLE_THIRD_POINT = sf::Vector2f{ 40, 190 };

CToolbar::CToolbar(sf::RenderWindow& window, CState* state, CCanvas* canvas)
    : m_window(window),
    m_state(state),
    m_canvas(canvas)
{
    m_buttons.push_back(new CButton(
        "coordinates",
        sf::Color::Yellow,
        sf::Vector2f(10, 10),
        sf::Vector2f(120, 40),
        new CChangeCoordinatesOfShapeCommand(this)
    ));

    m_buttons.push_back(new CButton(
        "thicknes",
        sf::Color::Green,
        sf::Vector2f(150, 10),
        sf::Vector2f(120, 40),
        new CChangeOutlineThicknessCommand(this)
    ));
    m_buttons.push_back(new CButton(
        "1",
        sf::Color::Green,
        sf::Vector2f(150, 60),
        sf::Vector2f(120, 40),
        new CSetThicknessCommand(this, 1)
    ));
    m_buttons.push_back(new CButton(
        "2",
        sf::Color::Green,
        sf::Vector2f(150, 110),
        sf::Vector2f(120, 40),
        new CSetThicknessCommand(this, 2)
    ));
    m_buttons.push_back(new CButton(
        "3",
        sf::Color::Green,
        sf::Vector2f(150, 160),
        sf::Vector2f(120, 40),
        new CSetThicknessCommand(this, 3)
    ));


    m_buttons.push_back(new CButton(
        "color",
        sf::Color::Cyan,
        sf::Vector2f(280, 10),
        sf::Vector2f(120, 40),
        new CChangeShapeColorCommand(this)
    ));
    m_buttons.push_back(new CButton(
        "red",
        sf::Color::Red,
        sf::Vector2f(280, 60),
        sf::Vector2f(120, 40),
        new CSetColorCommand(this, sf::Color::Red)
    ));
    m_buttons.push_back(new CButton(
        "blue",
        sf::Color::Blue,
        sf::Vector2f(280, 110),
        sf::Vector2f(120, 40),
        new CSetColorCommand(this, sf::Color::Blue)
    ));
    m_buttons.push_back(new CButton(
        "magenta",
        sf::Color::Magenta,
        sf::Vector2f(280, 160),
        sf::Vector2f(120, 40),
        new CSetColorCommand(this, sf::Color::Magenta)
    ));

    m_buttons.push_back(new CButton(
        "outline",
        sf::Color::Cyan,
        sf::Vector2f(410, 10),
        sf::Vector2f(120, 40),
        new CChangeShapeOutlineColorCommand(this)
    ));

    m_buttons.push_back(new CButton(
        "circle",
        sf::Color::Magenta,
        sf::Vector2f(540, 10),
        sf::Vector2f(120, 40),
        new CCircleCreateCommand(this)
    ));

    m_buttons.push_back(new CButton(
        "rectangle",
        sf::Color::Blue,
        sf::Vector2f(670, 10),
        sf::Vector2f(120, 40),
        new CRectangleCreateCommand(this)
    ));

    m_buttons.push_back(new CButton(
        "triangle",
        sf::Color::Red,
        sf::Vector2f(800, 10),
        sf::Vector2f(120, 40),
        new CTriangleCreateCommand(this)
    ));
}

void CToolbar::ChangeShapeColor()
{
    m_state->ChangeShapeColor(this);
}

void CToolbar::ChangeShapeOutlineColor()
{
    m_state->ChangeShapeOutlineColor(this);
}

void CToolbar::ChangeOutlineThickness()
{
    m_state->ChangeOutlineThickness(this);
}

void CToolbar::ChangeCoordinatesOfShape()
{
    m_state->ChangeCoordinatesOfShape(this);
}

void CToolbar::CreateCircle()
{
    m_canvas->CreateCircle(CIRCLE_CENTER, CIRCLE_RADIUS, &CIRCLE_STYLE);
}

void CToolbar::CreateTriangle()
{
    m_canvas->CreateTriangle(TRIANGLE_FIRST_POINT, TRIANGLE_SECOND_POINT, TRIANGLE_THIRD_POINT, &TRIANGLE_STYLE);
}

void CToolbar::CreateRectangle()
{
    m_canvas->CreateRectangle(RECTANGLE_LEFT_TOP, RECTANGLE_WIDTH, RECTANGLE_HEIGHT, &RECTANGLE_STYLE);
}

void CToolbar::TransitionTo(CState* state)
{
    if (m_state != nullptr)
    {
        delete m_state;
    }
    m_state = state;
    m_state->SetContext(this);
}

void CToolbar::Draw()
{
    for (auto button : m_buttons) {
        button->Draw(m_window);
    }
}

bool CToolbar::PressedToButton() const {
    for (auto button : m_buttons) {
        if (button->IsPointInButton(static_cast<sf::Vector2f>(m_cursorPosition))) {
            button->PressButton();
            return true;
        }
    }

    return false;
}

void CToolbar::SetCursorPosition(sf::Vector2i pos)
{
    m_cursorPosition = pos;
}

void CToolbar::SetSelectedColor(sf::Color color)
{
    m_selectedColor = color;
}

void CToolbar::SetSelectedThickness(float thickness)
{
    m_selectedThickness = thickness;
}

CState* CToolbar::GetState() const
{
    return m_state;
}

sf::Color CToolbar::GetSelectedColor() const
{
    return m_selectedColor;
}

float CToolbar::GetSelectedThickness() const
{
    return m_selectedThickness;
}

vector<CButton*> CToolbar::GetButtons() const
{
    return m_buttons;
}
