#pragma once

#include <iostream>

#include "ISaveFileStrategy.h"
#include "CCanvas.h"

class CFileSaver
{
public:
    CFileSaver(CCanvas* canvas);

    void SetStrategy(ISaveFileStrategy* saveFileStrategy);

    void Save(const std::string& m_fileName);

private:
    ISaveFileStrategy* m_strategy;
    CCanvas* m_canvas;
};
