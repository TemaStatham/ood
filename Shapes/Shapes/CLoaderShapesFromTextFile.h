#pragma once

#include "CLoaderShapesFromFile.h"
#include <fstream>

class CLoaderShapesFromTextFile : public CLoaderShapesFromFile
{
public:
    CLoaderShapesFromTextFile(CCanvas* canvas);
    void Load(const std::string& fileName);
protected:
    std::stringstream GetStringStream(const std::string& fileName) const override;
};
