#include "CSaveShapesToFileCommand.h"

CSaveShapesToFileCommand::CSaveShapesToFileCommand(CToolbar* reciever, ISaveFileStrategy* strategy)
    :m_toolbar(reciever),
    m_strategy(strategy)
{
}

void CSaveShapesToFileCommand::Execute() const
{
    std::string fileName;
    std::cin >> fileName;

    m_toolbar->Save(fileName, m_strategy);
}
