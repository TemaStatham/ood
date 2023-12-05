#pragma once

#include "ICommand.h"
#include "CToolbar.h"

class CChangeShapeOutlineColorCommand : public ICommand  {
public:
	CChangeShapeOutlineColorCommand(CToolbar* reciever);
	void Execute() const override;
private:
	CToolbar* m_toolbar;
};