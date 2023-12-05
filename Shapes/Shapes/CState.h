#pragma once

#include "CToolbar.h"

class CToolbar;

class CState {
public:
    void SetContext(CToolbar* context) {
        this->m_toolbar = context;
    }

    CToolbar* GetContext() {
        return m_toolbar;
    }

    virtual void ChangeShapeColor(CToolbar* context) = 0;
    virtual void ChangeShapeOutlineColor(CToolbar* context) = 0;
    virtual void ChangeOutlineThickness(CToolbar* context) = 0;
    virtual void ChangeCoordinatesOfShape(CToolbar* context) = 0;

    virtual ~CState() = default;
private:
    CToolbar* m_toolbar;
};
