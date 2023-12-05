#include "CSetThicknessCommand.h"

CSetThicknessCommand::CSetThicknessCommand(CToolbar* reciever, int thickness)
    :m_toolbar(reciever), m_thickness(thickness)
{
}

void CSetThicknessCommand::Execute() const
{
    m_toolbar->SetSelectedThickness(m_thickness);
}
