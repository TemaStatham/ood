#pragma once

#include "ICommand.h"
#include "CToolbar.h"
#include "ISaveFileStrategy.h"
#include "CFileSaver.h"

class CSaveShapesToFileCommand : public ICommand
{
public:
    CSaveShapesToFileCommand(CToolbar* reciever, ISaveFileStrategy* strategy);
    void Execute() const override;
private:
    CToolbar* m_toolbar;
    ISaveFileStrategy* m_strategy;
};
