#include "CCompositeBuilder.h"

CCompositeBuilder::CCompositeBuilder(const std::vector<unsigned int>& params, const std::vector<std::shared_ptr<CBuilder>>& shapes)
    :m_shapes(shapes), m_leftTop(params[0], params[1]), m_shape(nullptr)
{
}

void CCompositeBuilder::SetShape()
{
    m_shape = std::make_shared<CComposite>();

    for (auto shape : m_shapes)
    {
        m_shape->Add(shape->GetResult());
    }
}

void CCompositeBuilder::SetPosition()
{
    m_shape->SetPosition(m_leftTop.x, m_leftTop.y);
}

std::shared_ptr<CShapeDecorator> CCompositeBuilder::GetResult() const
{
    return m_shape;
}
