#include "CChangeCoordinatesOfShapeCommand.h"

CChangeCoordinatesOfShapeCommand::CChangeCoordinatesOfShapeCommand(CToolbar* reciever)
	: m_toolbar(reciever)
{
}

void CChangeCoordinatesOfShapeCommand::Execute() const
{
	m_toolbar->ChangeCoordinatesOfShape();
}
