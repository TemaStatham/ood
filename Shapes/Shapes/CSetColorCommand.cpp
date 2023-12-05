#include "CSetColorCommand.h"

CSetColorCommand::CSetColorCommand(CToolbar* reciever, sf::Color color)
    :m_toolbar(reciever), m_color(color)
{
}

void CSetColorCommand::Execute() const
{
    m_toolbar->SetSelectedColor(m_color);
}
