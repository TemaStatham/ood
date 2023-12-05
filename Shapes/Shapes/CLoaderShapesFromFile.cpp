#include "CLoaderShapesFromFile.h"

const int COUNT_OF_TRIANGLE_POINTS = 3;
const int COUNT_OF_RECTANGLE_POINTS = 2;

const std::string STR_REGEX_POINT = "P([0-9])=(\\d+),(\\d+);";
const std::string STR_REGEX_CENTER_OF_CIRLCE = "C=(-?\\d+),(-?\\d+);";
const std::string STR_REGEX_RADIUS_OF_CIRLCE = "R=(\\d+);";

CLoaderShapesFromFile::CLoaderShapesFromFile(CCanvas* canvas)
    :m_canvas(canvas),
    m_director(new CDirector())
{

}

void CLoaderShapesFromFile::LoadShapesFromFile(const std::string& fileName)
{
    auto stream = GetStringStream(fileName);

    m_canvas->Reset();

    std::string typeOfFigureAsString;
    while (stream >> typeOfFigureAsString)
    {
        try
        {
            CreateShape(typeOfFigureAsString, stream);

            m_canvas->AddNewShape(m_director->GetShape());
        }
        catch (const std::exception& e)
        {
            std::cout << "Error shape doesn`t create : " << e.what() << std::endl;
        }
    }
}

void CLoaderShapesFromFile::CreateShape(const std::string& typeOfFigureAsString, std::stringstream& stream)
{
    //std::cout << typeOfFigureAsString << std::endl;
    if (typeOfFigureAsString == "CIRCLE:")
    {
        CreateCircle(stream);
        return;
    }

    if (typeOfFigureAsString == "TRIANGLE:")
    {
        CreateTriangle(stream);
        return;
    }

    if (typeOfFigureAsString == "RECTANGLE:")
    {
        CreateRectangle(stream);
        return;
    }

    if (typeOfFigureAsString == "COMPOSITE:")
    {
        CreateCompound(stream);
        return;
    }

    throw std::invalid_argument("Unknown type of figure");
}

void CLoaderShapesFromFile::CreateCircle(std::stringstream& stream)
{
    auto params = GetParams(stream, 6);

    m_director->SetBuilder(new CCircleBuilder(params));

    m_canvas->AddNewShape(m_director->GetShape());
}

void CLoaderShapesFromFile::CreateRectangle(std::stringstream& stream)
{
    auto params = GetParams(stream, 7);

    m_director->SetBuilder(new CRectangleBuilder(params));
}

void CLoaderShapesFromFile::CreateTriangle(std::stringstream& stream)
{
    auto params = GetParams(stream, 9);

    m_director->SetBuilder(new CTriangleBuilder(params));
}

void CLoaderShapesFromFile::CreateCompound(std::stringstream& stream)
{
    auto params = GetParams(stream, 9);

    //m_director->SetBuilder(new CCompositeBuilder(params));
}

std::vector<float> CLoaderShapesFromFile::GetParams(std::stringstream& stream, size_t countParams)
{
    std::vector<float> params(countParams);

    std::string line;
    getline(stream, line);
    //std::cout << line << std::endl;
    std::stringstream ss(line);
    for (int i = 0; i < countParams; i++)
    {
        if (!(ss >> line))
        {
            throw std::invalid_argument("Not enough arguments");
        }

        try
        {
            params[i] = std::stof(line);
        }
        catch (const std::invalid_argument& e)
        {
            throw std::invalid_argument("Invalid argument: " + line);
        }
        catch (const std::out_of_range& e)
        {
            throw std::out_of_range("Out of range: " + line);
        }

        line.clear();
    }

    /*char ch;
    stream.get(ch);
    if (!stream.fail() && ch != '\n')
    {
        throw std::invalid_argument("Too many arguments");
    }*/

    return params;
}
