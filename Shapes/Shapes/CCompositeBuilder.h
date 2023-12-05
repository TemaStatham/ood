#pragma once

#include "IBuilder.h"
#include "CBuilder.h"
#include "CComposite.h"

class CCompositeBuilder : public IBuilder
{
public:
    CCompositeBuilder(const std::vector<unsigned int>& params, const std::vector<std::shared_ptr<CBuilder>>& shapes);

    void SetShape() override;
    void SetPosition() override;

    std::shared_ptr<CShapeDecorator> GetResult() const override;

private:
    std::vector<std::shared_ptr<CBuilder>> m_shapes;
    std::shared_ptr<CComposite> m_shape;
    sf::Vector2f m_leftTop;
};
