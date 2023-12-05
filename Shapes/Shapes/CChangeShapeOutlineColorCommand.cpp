#include "CChangeShapeOutlineColorCommand.h"

CChangeShapeOutlineColorCommand::CChangeShapeOutlineColorCommand(CToolbar* reciever)
	: m_toolbar(reciever)
{
}

void CChangeShapeOutlineColorCommand::Execute() const
{
	m_toolbar->ChangeShapeOutlineColor();
}
