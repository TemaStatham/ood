#include "CTriangleCreateCommand.h"

CTriangleCreateCommand::CTriangleCreateCommand(CToolbar* reciever)
    :m_toolbar(reciever)
{
}

void CTriangleCreateCommand::Execute() const
{
    m_toolbar->CreateTriangle();
}
