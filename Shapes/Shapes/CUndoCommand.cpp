#include "CUndoCommand.h"

CUndoCommand::CUndoCommand(CToolbar* reciever)
    :m_toolbar(reciever)
{
}

void CUndoCommand::Execute() const
{
    m_toolbar->Undo();
}
