#include "CChangeOutlineThicknessCommand.h"

CChangeOutlineThicknessCommand::CChangeOutlineThicknessCommand(CToolbar* reciever)
	: m_toolbar(reciever)
{
}

void CChangeOutlineThicknessCommand::Execute() const
{
	m_toolbar->ChangeOutlineThickness();
}
