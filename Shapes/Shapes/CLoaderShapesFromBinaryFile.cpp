#include "CLoaderShapesFromBinaryFile.h"

CLoaderShapesFromBinaryFile::CLoaderShapesFromBinaryFile(CCanvas* canvas)
    :CLoaderShapesFromFile(canvas)
{
}

void CLoaderShapesFromBinaryFile::Load(const std::string& fileName)
{
    this->LoadShapesFromFile(fileName);
}

std::stringstream CLoaderShapesFromBinaryFile::GetStringStream(const std::string& fileName) const
{
    std::ifstream input(fileName + ".bin", std::ios::in | std::ios::out | std::ios::binary);
    if (!input.is_open())
    {
        std::cout << fileName << " doesnt opened" << std::endl;
        return std::stringstream{};
    }

    std::stringstream stream;

    char ch[1];
    while (input.read(ch, 1))
    {
        stream << ch << std::endl;
    }

    return stream;
}
