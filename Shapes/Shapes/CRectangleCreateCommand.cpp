#include "CRectangleCreateCommand.h"

CRectangleCreateCommand::CRectangleCreateCommand(CToolbar* reciever)
    :m_toolbar(reciever)
{
}

void CRectangleCreateCommand::Execute() const
{
    m_toolbar->CreateRectangle();
}
