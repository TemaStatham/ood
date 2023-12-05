#include "CFileSaver.h"

CFileSaver::CFileSaver(CCanvas* canvas)
    : m_canvas(canvas), m_strategy(nullptr)
{

}

void CFileSaver::SetStrategy(ISaveFileStrategy* strategy)
{
    m_strategy = strategy;
}

void CFileSaver::Save(const std::string& fileName)
{
    m_strategy->Save(fileName, m_canvas->GetShapes());
}
