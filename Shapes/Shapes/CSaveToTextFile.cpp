#include "CSaveToTextFile.h"

void CSaveToTextFile::Save(const std::string& fileName, std::vector<std::shared_ptr<CShapeDecorator>> shapes) const
{
    std::ofstream out(fileName + ".txt");

    for (auto shape : shapes)
    {
        out << shape->GetInfo().str();
    }

    out.close();
}
