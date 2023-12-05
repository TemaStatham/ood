#pragma once

#include "ICommand.h"
#include "CToolbar.h"

class CLoadShapesFromTextFileCommand : public ICommand
{
public:
    CLoadShapesFromTextFileCommand(CToolbar* reciever);
    void Execute() const override;
private:
    CToolbar* m_toolbar;
};
