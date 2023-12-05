#include "CSaveToBinFile.h"

void CSaveToBinFile::Save(const std::string& fileName, std::vector<std::shared_ptr<CShapeDecorator>> shapes) const
{
    std::ofstream out(fileName + ".bin", std::ios::binary | std::ios::out);

    for (auto shape : shapes)
    {
        size_t size = shape->GetInfo().str().size();

        out.write((char*)&size, sizeof(size));

        out.write(shape->GetInfo().str().c_str(), size);
    }

    out.close();
}
