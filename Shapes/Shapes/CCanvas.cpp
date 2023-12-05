#include "CCanvas.h"

const int COUNT_OF_TRIANGLE_POINTS = 3;
const int COUNT_OF_RECTANGLE_POINTS = 2;

const std::string STR_REGEX_POINT = "P([0-9])=(\\d+),(\\d+);";
const std::string STR_REGEX_CENTER_OF_CIRLCE = "C=(-?\\d+),(-?\\d+);";
const std::string STR_REGEX_RADIUS_OF_CIRLCE = "R=(\\d+);";

CCanvas::CCanvas(sf::RenderWindow& window, std::istream& in)
    :m_window(window),
    m_in(in),
    m_actionMap({
          { "TRIANGLE:", [this]() {
               return ReadTriangleProperties();
           } },
          { "RECTANGLE:", [this]() {
               return ReadRectangleProperties();
           } },
          { "CIRCLE:", [this]() {
               return ReadCircleProperties();
           } },
        })
{
}

void CCanvas::Draw()
{
    for (auto shape : m_shapes)
    {
        shape->Draw(m_window);
    }
}

void CCanvas::CreateShape(const std::string& typeOfFigureAsString)
{
    auto it = m_actionMap.find(typeOfFigureAsString);

    if (it != m_actionMap.end())
    {
        return it->second();
    }

    throw std::invalid_argument("Invalid type of figure");
}

void CCanvas::CreateCircle(sf::Vector2f center, float radius, ShapeStyle* style)
{
    Backup();
    auto circleShape = std::make_shared<sf::CircleShape>();

    circleShape->setPosition(center);
    circleShape->setRadius(radius);

    ConfigureShape(circleShape, style);

    CCircleDecorator circle(circleShape, center, radius);

    m_shapes.push_back(std::make_shared<CCircleDecorator>(circle));
}

void CCanvas::CreateRectangle(sf::Vector2f leftTop, float width, float height, ShapeStyle* style)
{
    Backup();
    auto rectangleShape = std::make_shared<sf::RectangleShape>();

    rectangleShape->setSize(sf::Vector2f(width, height));
    rectangleShape->setPosition(leftTop);

    ConfigureShape(rectangleShape, style);

    CRectangleDecorator rectangle(rectangleShape, leftTop, height, width);

    m_shapes.push_back(std::make_shared<CRectangleDecorator>(rectangle));
}

void CCanvas::CreateTriangle(sf::Vector2f firstPoint, sf::Vector2f secondPoint, sf::Vector2f thirdPoint, ShapeStyle* style)
{
    Backup();
    auto triangleShape = std::make_shared<sf::ConvexShape>();

    triangleShape->setPointCount(3);
    triangleShape->setPoint(0, firstPoint);
    triangleShape->setPoint(1, secondPoint);
    triangleShape->setPoint(2, thirdPoint);

    ConfigureShape(triangleShape, style);

    CTriangleDecorator triangle(triangleShape, firstPoint, secondPoint, thirdPoint);

    m_shapes.push_back(std::make_shared<CTriangleDecorator>(triangle));
}

void CCanvas::ChangeShapeColor(sf::Color color)
{
    for (auto shape : m_shapes)
    {
        if (shape->GetGlobalBounds().contains(m_cursorPosition.x, m_cursorPosition.y))
        {
            Backup();
            shape->SetFillColor(color);
        }
    }
}

void CCanvas::ChangeShapeOutlineColor(sf::Color color)
{
    for (auto shape : m_shapes)
    {
        if (shape->GetGlobalBounds().contains(m_cursorPosition.x, m_cursorPosition.y))
        {
            Backup();
            shape->SetOutlineColor(color);
        }
    }
}

void CCanvas::ChangeOutlineThickness(float thickness)
{
    for (auto shape : m_shapes)
    {
        if (shape->GetGlobalBounds().contains(m_cursorPosition.x, m_cursorPosition.y))
        {
            Backup();
            shape->SetOutlineThickness(thickness);
        }
    }
}

void CCanvas::ChangeCoordinatesOfShape()
{
    if (m_indexCurrentShape != -1 && m_shapes[m_indexCurrentShape]->IsSelected())
    {
        Backup();
        m_shapes[m_indexCurrentShape]->SetPosition(m_cursorPosition.x - m_offsetCoordinates.x, m_cursorPosition.y - m_offsetCoordinates.y);
    }
}

std::vector<std::shared_ptr<CShapeDecorator>> CCanvas::GetShapes() const
{
    return m_shapes;
}

std::vector<std::shared_ptr<CShapeDecorator>> CCanvas::GetSelectedShapes() const
{
    return m_selectedShapes;
}

void CCanvas::AddNewSelectedShape()
{
    for (size_t i = 0; i < m_shapes.size(); i++)
    {
        if (m_shapes[i]->GetGlobalBounds().contains(m_cursorPosition.x, m_cursorPosition.y))
        {
            Backup();
            m_shapes[i]->SetSelected(true);
            m_selectedShapes.push_back(m_shapes[i]);
        }
    }
}

void CCanvas::DeleteSelectedShape()
{
    for (size_t i = 0; i < m_shapes.size(); i++)
    {
        if (m_shapes[i]->GetGlobalBounds().contains(m_cursorPosition.x, m_cursorPosition.y))
        {
            if (m_shapes[i]->IsSelected())
            {
                m_shapes[i]->SetSelected(false);
                m_indexCurrentShape = -1;
                auto it = std::find(m_selectedShapes.begin(), m_selectedShapes.end(), m_shapes[i]);
                if (it != m_selectedShapes.end())
                {
                    m_selectedShapes.erase(it);
                }
            }
        }
    }
}

void CCanvas::ResetSelectedShapes()
{
    for (auto shape : m_shapes)
    {
        shape->SetSelected(false);
    }
    m_indexCurrentShape = -1;
    m_selectedShapes.clear();
}

void CCanvas::SelectOneMoreShape()
{
    for (size_t i = 0; i < m_shapes.size(); i++)
    {
        if (m_shapes[i]->GetGlobalBounds().contains(m_cursorPosition.x, m_cursorPosition.y))
        {
            Backup();
            m_shapes[i]->SetSelected(true);
            m_selectedShapes.push_back(m_shapes[i]);
        }
    }
}

void CCanvas::SetChoose()
{
    for (size_t i = 0; i < m_shapes.size(); i++)
    {
        if (m_shapes[i]->GetGlobalBounds().contains(m_cursorPosition.x, m_cursorPosition.y))
        {
            Backup();
            if (m_shapes[i]->IsSelected())
            {
                m_indexCurrentShape = i;
                SetOffsetCoordinates
                (
                    sf::Vector2f
                    (
                        m_cursorPosition.x - m_shapes[i]->GetPosition().x,
                        m_cursorPosition.y - m_shapes[i]->GetPosition().y
                    )
                );
            }
            else
            {
                m_indexCurrentShape = i;
                m_shapes[i]->SetSelected(true);
                m_selectedShapes.clear();
                m_selectedShapes.push_back(m_shapes[i]);
                SetOffsetCoordinates
                (
                    sf::Vector2f
                    (
                        m_cursorPosition.x - m_shapes[i]->GetPosition().x,
                        m_cursorPosition.y - m_shapes[i]->GetPosition().y
                    )
                );
                for (size_t j = 0; j < m_shapes.size(); j++)
                {
                    if (j != i)
                    {
                        m_shapes[j]->SetSelected(false);
                    }
                }
            }
        }
    }
}
void CCanvas::Select()
{
    for (size_t i = 0; i < m_shapes.size(); i++)
    {
        if (m_shapes[i]->GetGlobalBounds().contains(m_cursorPosition.x, m_cursorPosition.y))
        {
            if (m_shapes[i]->IsSelected())
            {
                Backup();
                m_shapes[i]->SetSelected(false);
                m_indexCurrentShape = -1;
                vector<std::shared_ptr<CShapeDecorator>>::iterator it = std::find(m_selectedShapes.begin(), m_selectedShapes.end(), m_shapes[i]);
                if (it != m_selectedShapes.end())
                {
                    m_selectedShapes.erase(it);
                }
            }
        }
    }
}

void CCanvas::Accept(IVisitor* visitor)
{
    for (auto shape : m_shapes)
    {
        if (shape->GetGlobalBounds().contains(m_cursorPosition.x, m_cursorPosition.y))
        {
            visitor->VisitShape(shape.get());
        }
    }
}
void CCanvas::Backup()
{
    m_history.push(new CMemento(m_shapes, m_selectedShapes));
}
void CCanvas::Undo()
{
    if (m_history.size() == 0)
    {
        return;
    }

    m_shapes = m_history.top()->GetShapes();
    m_selectedShapes = m_history.top()->GetSelectedShapes();
    m_indexCurrentShape = -1;
    m_cursorPosition = sf::Vector2i(0, 0);
    m_offsetCoordinates = sf::Vector2f(0, 0);
    m_history.pop();
}

void CCanvas::SelectMultipleShape()
{
    for (size_t i = 0; i < m_shapes.size(); i++)
    {
        if (!(m_shapes[i]->GetGlobalBounds().contains(m_cursorPosition.x, m_cursorPosition.y))) {
            continue;
        }

        m_shapes[i]->SetSelected(true);
        m_selectedShapes.push_back(m_shapes[i]);
    }
}

void CCanvas::GroupShapes()
{
    if (!m_selectedShapes.empty())
    {
        std::shared_ptr<CComposite> compoundFigure = std::make_shared<CComposite>();
        for (std::shared_ptr<CShapeDecorator> figure : m_selectedShapes)
        {
            compoundFigure->Add(figure);
            auto itShapes = find(m_shapes.begin(), m_shapes.end(), figure);
            if (itShapes != m_shapes.end())
            {
                m_shapes.erase(itShapes);
            }
        }
        m_selectedShapes.clear();
        m_indexCurrentShape = -1;

        m_shapes.push_back(compoundFigure);
    }
}

void CCanvas::UngroupShapes()
{
    if (m_selectedShapes.size() == 1)
    {
        std::shared_ptr<CComposite> compoundFigure = std::static_pointer_cast<CComposite>(m_selectedShapes.front());;
        list<std::shared_ptr<CShapeDecorator>> figures = compoundFigure->GetShapes();

        vector<std::shared_ptr<CShapeDecorator>>::iterator itShapes = find(m_shapes.begin(), m_shapes.end(), compoundFigure);
        if (itShapes != m_shapes.end())
        {
            m_shapes.erase(itShapes);
        }
        for (std::shared_ptr<CShapeDecorator> figure : figures)
        {
            m_shapes.push_back(figure);
        }
        m_selectedShapes.clear();
        m_indexCurrentShape = -1;
    }
}

void CCanvas::SetCursorPosition(sf::Vector2i pos)
{
    m_cursorPosition = pos;
}

void CCanvas::SetOffsetCoordinates(sf::Vector2f coordinates)
{
    m_offsetCoordinates = coordinates;
}

void CCanvas::ResetIndex()
{
    m_indexCurrentShape = -1;
}

void CCanvas::ConfigureShape(std::shared_ptr<sf::Shape> shape, ShapeStyle* style)
{
    shape->setOutlineThickness(style->thickness);
    shape->setOutlineColor(style->outlineColor);
    shape->setFillColor(sf::Color(style->fillColor.r, style->fillColor.g, style->fillColor.b, 255));
}

void CCanvas::ParseInputString(const std::string& input, float& pref, float& num1, float& num2)
{
    std::regex pattern(STR_REGEX_POINT);

    std::smatch match;
    if (!(std::regex_search(input, match, pattern))) {
        std::cout << "Error regex search" << std::endl;
        return;
    }

    if (match.size() != 4) {
        std::cout << "Error match size" << std::endl;
        return;
    }

    pref = std::stof(match[1]);
    num1 = std::stof(match[2]);
    num2 = std::stof(match[3]);
}

sf::Vector2f CCanvas::ParseCoordinate(const std::string& input)
{
    std::regex pattern(STR_REGEX_CENTER_OF_CIRLCE);
    std::smatch match;

    if (std::regex_search(input, match, pattern)) {
        float x = std::stof(match[1]);
        float y = std::stof(match[2]);
        return sf::Vector2f(x, y);
    }

    return sf::Vector2f(0, 0);
}

float CCanvas::ParseRadius(const std::string& input)
{
    std::regex pattern(STR_REGEX_RADIUS_OF_CIRLCE);
    std::smatch match;

    if (std::regex_search(input, match, pattern)) {
        float radius = std::stof(match[1]);
        return radius;
    }

    return 0;
}

void CCanvas::ReadCircleProperties()
{
    std::string c;
    float radius;

    m_in >> c;

    sf::Vector2f center = ParseCoordinate(c);

    std::string r;

    m_in >> r;

    radius = ParseRadius(r);
    if (m_in.fail())
    {
        throw std::invalid_argument("Not enough arguments");
    }

    if (radius < 0)
    {
        throw std::invalid_argument("Invalid radius param");
    }

    char ch;
    m_in.get(ch);
    if (m_in.fail() || ch == '\n')
    {
        ShapeStyle style = ShapeStyle{ 5, sf::Color::Red, sf::Color::Blue };
        CreateCircle(center, radius, &style);
        return;
    }

    throw std::invalid_argument("Too many arguments");
}

void CCanvas::ReadRectangleProperties()
{
    std::vector<sf::Vector2f> rectanglePoints;
    for (int i = 0; i < COUNT_OF_RECTANGLE_POINTS; i++)
    {
        std::string inp;
        float pref, x, y;

        m_in >> inp;

        ParseInputString(inp, pref, x, y);

        if (m_in.fail())
        {
            throw std::invalid_argument("Not enough arguments");
        }
        sf::Vector2f vec(x, y);
        rectanglePoints.push_back(vec);
    }

    float width = rectanglePoints[1].x - rectanglePoints[0].x,
        height = rectanglePoints[1].y - rectanglePoints[0].y;

    if (width < 0 || height < 0)
    {
        throw std::invalid_argument("Invalid width or height params");
    }
    char ch;
    m_in.get(ch);
    if (m_in.fail() || ch == '\n')
    {
        ShapeStyle style = ShapeStyle{ 5, sf::Color::Red, sf::Color::Blue };
        sf::Vector2f leftTop(rectanglePoints[0].x, rectanglePoints[0].y);
        CreateRectangle(leftTop, width, height, &style);
        return;
    }

    throw std::invalid_argument("Too many arguments");
}

void CCanvas::ReadTriangleProperties()
{
    std::vector<sf::Vector2f> trianglePoints;
    for (size_t i = 0; i < COUNT_OF_TRIANGLE_POINTS; i++)
    {
        std::string inp;
        float pref, x, y;

        m_in >> inp;

        ParseInputString(inp, pref, x, y);

        if (m_in.fail())
        {
            throw std::invalid_argument("Not enough arguments");
        }
        sf::Vector2f vec(x, y);
        trianglePoints.push_back(vec);
    }

    char ch;
    m_in.get(ch);
    if (m_in.fail() || ch == '\n')
    {
        ShapeStyle style = ShapeStyle{ 5, sf::Color::Red, sf::Color::Magenta };
        CreateTriangle(trianglePoints[0], trianglePoints[1], trianglePoints[2], &style);
        return;
    }

    throw std::invalid_argument("Too many arguments");
}
