#pragma once

#include "ICommand.h"
#include "CToolbar.h"


class CRectangleCreateCommand : public ICommand {
public:
    CRectangleCreateCommand(CToolbar* reciever);
    void Execute() const override;
private:
    CToolbar* m_toolbar;
};
