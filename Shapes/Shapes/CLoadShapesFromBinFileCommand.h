#pragma once

#include "ICommand.h"
#include "CToolbar.h"

class CLoadShapesFromBinFileCommand : public ICommand
{
public:
    CLoadShapesFromBinFileCommand(CToolbar* reciever);
    void Execute() const override;
private:
    CToolbar* m_toolbar;
};
