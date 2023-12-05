#pragma once

#include <SFML/Graphics.hpp>
#include "CToolbar.h"
#include "ICommand.h"

class CSetColorCommand : public ICommand {
public:
    CSetColorCommand(CToolbar* reciever, sf::Color color);
    void Execute() const override;
private:
    CToolbar* m_toolbar;
    sf::Color m_color;
};
