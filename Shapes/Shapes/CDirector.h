#pragma once

#include "IBuilder.h"
#include "CBuilder.h"
#include "CCompositeBuilder.h"
#include "CShapeDecorator.h"
#include <iostream>
#include <functional>

class CDirector
{
public:
    CDirector();
    void SetBuilder(IBuilder* builder);

    void CreateShape();

    std::shared_ptr<CShapeDecorator> GetShape();
private:
    IBuilder* m_builder;
};
