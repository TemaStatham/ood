#pragma once

#include "CShapeDecorator.h"

class IBuilder
{
public:
    virtual void SetShape() = 0;
    virtual void SetPosition() = 0;

    virtual std::shared_ptr<CShapeDecorator> GetResult() const = 0;

    virtual ~IBuilder() {}
};
