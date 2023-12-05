#pragma once

#include <SFML/Graphics.hpp>
#include "CToolbar.h"
#include "ICommand.h"

class CSetThicknessCommand : public ICommand {
public:
    CSetThicknessCommand(CToolbar* reciever, int thickness);
    void Execute() const override;
private:
    CToolbar* m_toolbar;
    int m_thickness;
};
