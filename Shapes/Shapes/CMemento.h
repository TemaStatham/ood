#pragma once

#include <vector>
#include <memory>

#include "CShapeDecorator.h"
#include "CCircleDecorator.h"
#include "CTriangleDecorator.h"
#include "CRectangleDecorator.h"
#include "CComposite.h"

class CMemento
{
public:
    CMemento(
        std::vector<std::shared_ptr<CShapeDecorator>>& shapes,
        std::vector<std::shared_ptr<CShapeDecorator>>& selectedShapes
    );
    std::vector<std::shared_ptr<CShapeDecorator>> GetShapes() const;
    std::vector<std::shared_ptr<CShapeDecorator>> GetSelectedShapes() const;
private:
    std::vector<std::shared_ptr<CShapeDecorator>> GetCopy(std::vector<std::shared_ptr<CShapeDecorator>> shapes);

    std::vector<std::shared_ptr<CShapeDecorator>> m_shapes;
    std::vector<std::shared_ptr<CShapeDecorator>> m_selectedShapes;
};
