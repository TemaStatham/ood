#pragma once
#include "ISaveFileStrategy.h"

#include "fstream"

class CSaveToTextFile : public ISaveFileStrategy
{
public:
    void Save(const std::string& fileName, std::vector<std::shared_ptr<CShapeDecorator>> shapes) const override;
};
