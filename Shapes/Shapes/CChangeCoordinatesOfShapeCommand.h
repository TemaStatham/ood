#pragma once

#include "ICommand.h"
#include "CToolbar.h"



class CChangeCoordinatesOfShapeCommand : public ICommand {
public:
    CChangeCoordinatesOfShapeCommand(CToolbar* reciever);
    void Execute() const override;
private:
    CToolbar* m_toolbar;
};
