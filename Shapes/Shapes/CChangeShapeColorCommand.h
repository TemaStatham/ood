#pragma once

#include "ICommand.h"
#include "CToolbar.h"

class CChangeShapeColorCommand : public ICommand {
public:
	CChangeShapeColorCommand(CToolbar* reciever);
	void Execute() const override;
private:
	CToolbar* m_toolbar;
};