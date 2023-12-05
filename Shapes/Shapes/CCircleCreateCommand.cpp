#include "CCircleCreateCommand.h"

CCircleCreateCommand::CCircleCreateCommand(CToolbar* reciever)
    :m_toolbar(reciever)
{
}

void CCircleCreateCommand::Execute() const
{
    m_toolbar->CreateCircle();
}
