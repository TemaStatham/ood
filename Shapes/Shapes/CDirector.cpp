#include "CDirector.h"

CDirector::CDirector()
    :m_builder(nullptr)
{
}

void CDirector::SetBuilder(IBuilder* builder)
{
    m_builder = builder;
}

void CDirector::CreateShape()
{
    m_builder->SetShape();
    m_builder->SetPosition();
}

std::shared_ptr<CShapeDecorator> CDirector::GetShape()
{
    return m_builder->GetResult();
}
