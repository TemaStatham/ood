#pragma once
#include "ISaveFileStrategy.h"

#include "fstream"

class CSaveToBinFile : public ISaveFileStrategy
{
public:
    void Save(const std::string& fileName, std::vector<std::shared_ptr<CShapeDecorator>> shapes) const override;
};
