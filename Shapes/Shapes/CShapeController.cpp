#include "CShapeController.h"
#include <algorithm>

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

void CShapeController::Draw()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(250, 220, 100, 0));

        for (auto& el : m_shapes)
        {
            el->Draw(window);
        }

        window.display();
    }
}
