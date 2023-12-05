#include "CLoaderShapesFromTextFile.h"

CLoaderShapesFromTextFile::CLoaderShapesFromTextFile(CCanvas* canvas)
    :CLoaderShapesFromFile(canvas)
{
}

void CLoaderShapesFromTextFile::Load(const std::string& fileName)
{
    this->LoadShapesFromFile(fileName);
}

std::stringstream CLoaderShapesFromTextFile::GetStringStream(const std::string& fileName) const
{
    std::ifstream input(fileName + ".txt");
    if (!input.is_open())
    {
        std::cout << fileName << " doesnt opened" << std::endl;
        return std::stringstream{};
    }

    std::stringstream stream;

    std::string s;
    while (std::getline(input, s))
    {
        stream << s << std::endl;
    }

    return stream;
}
