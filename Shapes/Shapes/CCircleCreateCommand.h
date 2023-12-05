#pragma once

#include "ICommand.h"
#include "CToolbar.h"

class CCircleCreateCommand : public ICommand {
public:
    CCircleCreateCommand(CToolbar* reciever);
    void Execute() const override;
private:
    CToolbar* m_toolbar;
};
