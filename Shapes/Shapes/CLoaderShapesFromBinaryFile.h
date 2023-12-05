#pragma once

#include "CLoaderShapesFromFile.h"
#include <fstream>

class CLoaderShapesFromBinaryFile : public CLoaderShapesFromFile
{
public:
    void Load(const std::string& fileName);
protected:
    std::stringstream GetStringStream(const std::string& fileName) const override;
};