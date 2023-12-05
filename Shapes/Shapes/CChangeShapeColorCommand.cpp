#include "CChangeShapeColorCommand.h"

CChangeShapeColorCommand::CChangeShapeColorCommand(CToolbar* reciever)
	: m_toolbar(reciever)
{
}

void CChangeShapeColorCommand::Execute() const
{
	m_toolbar->ChangeShapeColor();
}
