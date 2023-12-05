#pragma once

#include <vector>

#include "CShapeDecorator.h"

class ISaveFileStrategy
{
public:
    virtual void Save(const std::string& fileName, std::vector<std::shared_ptr<CShapeDecorator>> shapes) const = 0;
    virtual ~ISaveFileStrategy() = default;
};
