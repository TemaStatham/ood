#include "CShapeController.h"
#include <algorithm>

using namespace std;

const int COUNT_OF_TRIANGLE_POINTS = 3;
const int COUNT_OF_RECTANGLE_POINTS = 2;

const std::string STR_REGEX_POINT = "P([0-9])=(\\d+),(\\d+);";
const std::string STR_REGEX_CENTER_OF_CIRLCE = "C=(-?\\d+),(-?\\d+);";
const std::string STR_REGEX_RADIUS_OF_CIRLCE = "R=(\\d+);";

CShapeController::CShapeController(std::vector<std::shared_ptr<CShapeDecorator>>& shapes, std::istream& in, std::ostream& out)
    : m_shapes(shapes)
    , m_in(in)
    , m_out(out)
    , m_actionMap({
          { "TRIANGLE:", [this]() {
               return CreateTriangle();
           } },
          { "RECTANGLE:", [this]() {
               return CreateRectangle();
           } },
          { "CIRCLE:", [this]() {
               return CreateCircle();
           } },
        })
{
}

void CShapeController::Start()
{
    Help();

    std::string typeOfFigureAsString;

    while (m_in >> typeOfFigureAsString)
    {
        try
        {
            m_shapes.push_back(CreateShape(typeOfFigureAsString));
            m_out << "The shape was saved successfully" << std::endl;
        }
        catch (const std::exception& e)
        {
            m_out << e.what() << std::endl;
            std::string garbage;
            getline(m_in, garbage);
        }
    }

    PrintToOut();
    Draw();
}

std::shared_ptr<CShapeDecorator> CShapeController::CreateShape(const std::string& typeOfFigureAsString) const
{
    auto it = m_actionMap.find(typeOfFigureAsString);

    if (it != m_actionMap.end())
    {
        return it->second();
    }

    throw std::invalid_argument("Invalid type of figure");
}

std::shared_ptr<CTriangleDecorator> CShapeController::CreateTriangle() const
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
        auto triangleShape = std::make_shared<sf::ConvexShape>();

        triangleShape->setPointCount(3);
        triangleShape->setPoint(0, trianglePoints[0]);
        triangleShape->setPoint(1, trianglePoints[1]);
        triangleShape->setPoint(2, trianglePoints[2]);

        triangleShape->setOutlineThickness(5);
        triangleShape->setOutlineColor(sf::Color(0, 0, 100));
        triangleShape->setFillColor(sf::Color(0, 0, 100));

        CTriangleDecorator triangle(triangleShape, trianglePoints[0], trianglePoints[1], trianglePoints[2]);

        return std::make_shared<CTriangleDecorator>(triangle);
    }

    throw std::invalid_argument("Too many arguments");
}

std::shared_ptr<CRectangleDecorator> CShapeController::CreateRectangle() const
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
        auto rectangleShape = std::make_shared<sf::RectangleShape>();

        sf::Vector2f leftTop(rectanglePoints[0].x, rectanglePoints[0].y);

        rectangleShape->setSize(sf::Vector2f(width, height));
        rectangleShape->setPosition(leftTop);

        rectangleShape->setOutlineThickness(5);
        rectangleShape->setOutlineColor(sf::Color(100, 0, 0));
        rectangleShape->setFillColor(sf::Color(100, 0, 0));

        CRectangleDecorator rectangle(rectangleShape, leftTop, height, width);

        return std::make_shared<CRectangleDecorator>(rectangle);
    }

    throw std::invalid_argument("Too many arguments");
}

std::shared_ptr<CCircleDecorator> CShapeController::CreateCircle() const
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
        auto circleShape = std::make_shared<sf::CircleShape>();

        circleShape->setPosition(center);
        circleShape->setRadius(radius);

        circleShape->setOutlineThickness(5);
        circleShape->setOutlineColor(sf::Color(0, 100, 0));
        circleShape->setFillColor(sf::Color(0, 100, 0));

        CCircleDecorator circle(circleShape, center, radius);

        return std::make_shared<CCircleDecorator>(circle);
    }

    throw std::invalid_argument("Too many arguments");
}

void CShapeController::Help()
{
    m_out << "Commands : " << std::endl
        << "\tTRIANGLE: P1=100,100; P2=200,200; P3=150,150" << std::endl
        << "\tRECTANGLE: P1=200,200; P2=300,300;" << std::endl
        << "\tCIRCLE: C=100,100; R=50" << std::endl;
}

void ParseInputString(const std::string& input, float& pref, float& num1, float& num2)
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

sf::Vector2f FindTopLeft(const sf::Vector2f& point1, const sf::Vector2f& point2) {
    float left = std::min(point1.x, point2.x);
    float top = std::min(point1.y, point2.y);
    return sf::Vector2f(left, top);
}

sf::Vector2f ParseCoordinate(const std::string& input)
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

float ParseRadius(const std::string& input)
{
    std::regex pattern(STR_REGEX_RADIUS_OF_CIRLCE);
    std::smatch match;

    if (std::regex_search(input, match, pattern)) {
        float radius = std::stof(match[1]);
        return radius;
    }

    return 0;
}

void CShapeController::PrintToOut()
{
    for (auto& el : m_shapes)
    {
        m_out << el.get()->ToString();
    }
}

using namespace sf;

void CShapeController::Draw()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    window.setVerticalSyncEnabled(true);

    int index = -1;
    float dX = 0;
    float dY = 0;

    vector<std::shared_ptr<CShapeDecorator>> selectedShapes;
    while (window.isOpen())
    {
        sf::Vector2i pos = sf::Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (Keyboard::isKeyPressed(sf::Keyboard::LShift))
            {
                if (event.type == Event::MouseButtonPressed)
                {
                    if (event.key.code == Mouse::Left)
                    {
                        for (size_t i = 0; i < m_shapes.size(); i++)
                        {
                            if (m_shapes[i]->GetGlobalBounds().contains(pos.x, pos.y))
                            {
                                m_shapes[i]->SetSelected(true);
                                selectedShapes.push_back(m_shapes[i]);
                            }
                        }
                    }
                }
            }

            if (event.type == Event::MouseButtonPressed)
            {
                if (event.key.code == Mouse::Left)
                {
                    SetChoose(selectedShapes, index, pos, dX, dY);
                }

                if (event.key.code == Mouse::Right)
                {
                    Select(selectedShapes, index, pos);
                }
            }

            if (Keyboard::isKeyPressed(sf::Keyboard::LControl))
            {
                if (Keyboard::isKeyPressed(sf::Keyboard::G))
                {
                    Group(selectedShapes, index);
                }
            }
            if (Keyboard::isKeyPressed(sf::Keyboard::LControl))
            {
                if (Keyboard::isKeyPressed(sf::Keyboard::U))
                {
                    Ungroup(selectedShapes, index);
                }
            }

            if (event.type == Event::MouseButtonReleased)
            {
                if (event.key.code == Mouse::Left)
                {
                    index = -1;
                }
            }
        }

        if (index != -1 && m_shapes[index]->IsSelected())
        {
            m_shapes[index]->SetPosition(pos.x - dX, pos.y - dY);
        }

        window.clear(sf::Color::Cyan);
        for (size_t i = 0; i < m_shapes.size(); i++)
        {
            m_shapes[i]->Draw(window);
        }
        window.display();

    }

}

void CShapeController::SetChoose(vector<std::shared_ptr<CShapeDecorator>>& selectedShapes,
    int& index, sf::Vector2i pos, float& dX, float& dY)
{
    for (size_t i = 0; i < m_shapes.size(); i++)
    {
        if (m_shapes[i]->GetGlobalBounds().contains(pos.x, pos.y))
        {
            if (m_shapes[i]->IsSelected())
            {
                index = i;
                dX = pos.x - m_shapes[i]->GetPosition().x;
                dY = pos.y - m_shapes[i]->GetPosition().y;
            }
            else
            {
                index = i;
                m_shapes[i]->SetSelected(true);
                selectedShapes.clear();
                selectedShapes.push_back(m_shapes[i]);
                dX = pos.x - m_shapes[i]->GetPosition().x;
                dY = pos.y - m_shapes[i]->GetPosition().y;
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

void CShapeController::Select(vector<std::shared_ptr<CShapeDecorator>>& selectedShapes, int& index, sf::Vector2i pos)
{
    for (size_t i = 0; i < m_shapes.size(); i++)
    {
        if (m_shapes[i]->GetGlobalBounds().contains(pos.x, pos.y))
        {
            if (m_shapes[i]->IsSelected())
            {
                m_shapes[i]->SetSelected(false);
                index = -1;
                vector<std::shared_ptr<CShapeDecorator>>::iterator it = find(selectedShapes.begin(), selectedShapes.end(), m_shapes[i]);
                if (it != selectedShapes.end())
                {
                    selectedShapes.erase(it);
                }
            }
        }
    }
}

void CShapeController::Ungroup(vector<std::shared_ptr<CShapeDecorator>>& selectedShapes, int& index)
{
    if (selectedShapes.size() == 1)
    {
        std::shared_ptr<CComposite> compoundFigure = std::static_pointer_cast<CComposite>(selectedShapes.front());;
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
        selectedShapes.clear();
        index = -1;
    }
}

void CShapeController::Group(vector<std::shared_ptr<CShapeDecorator>>& selectedShapes, int& index)
{
    if (!selectedShapes.empty())
    {
        std::shared_ptr<CComposite> compoundFigure = std::make_shared<CComposite>();
        for (std::shared_ptr<CShapeDecorator> figure : selectedShapes)
        {
            compoundFigure->Add(figure);
            auto itShapes = find(m_shapes.begin(), m_shapes.end(), figure);
            if (itShapes != m_shapes.end())
            {
                m_shapes.erase(itShapes);
            }
        }
        selectedShapes.clear();
        index = -1;

        m_shapes.push_back(compoundFigure);
    }
}
