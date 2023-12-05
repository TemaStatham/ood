#include "CMemento.h"
CMemento::CMemento(
    std::vector<std::shared_ptr<CShapeDecorator>>& shapes,
    std::vector<std::shared_ptr<CShapeDecorator>>& selectedShapes
) : m_shapes(GetCopy(shapes)), m_selectedShapes(GetCopy(selectedShapes))
{
}

std::vector<std::shared_ptr<CShapeDecorator>> CMemento::GetShapes() const
{
    return m_shapes;
}

std::vector<std::shared_ptr<CShapeDecorator>> CMemento::GetSelectedShapes() const
{
    return m_selectedShapes;
}

std::vector<std::shared_ptr<CShapeDecorator>> CMemento::GetCopy(std::vector<std::shared_ptr<CShapeDecorator>> shapes)
{
    std::vector<std::shared_ptr<CShapeDecorator>> result;

    for (const auto& shape : shapes)
    {
        if (typeid(*shape) == typeid(CCircleDecorator))
        {
            result.push_back(std::make_shared<CCircleDecorator>(*std::dynamic_pointer_cast<CCircleDecorator>(shape)));
        }
        if (typeid(*shape) == typeid(CTriangleDecorator))
        {
            result.push_back(std::make_shared<CTriangleDecorator>(*std::dynamic_pointer_cast<CTriangleDecorator>(shape)));
        }
        if (typeid(*shape) == typeid(CRectangleDecorator))
        {
            result.push_back(std::make_shared<CRectangleDecorator>(*std::dynamic_pointer_cast<CRectangleDecorator>(shape)));
        }
        if (typeid(*shape) == typeid(CComposite))
        {
            result.push_back(std::make_shared<CComposite>(*std::dynamic_pointer_cast<CComposite>(shape)));
        }
    }

    return result;
}
