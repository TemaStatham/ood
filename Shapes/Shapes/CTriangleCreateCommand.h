#pragma once

#include "ICommand.h"
#include "CToolbar.h"

class CTriangleCreateCommand : public ICommand {
public:
    CTriangleCreateCommand(CToolbar* reciever);
    void Execute() const override;
private:
    CToolbar* m_toolbar;
};
