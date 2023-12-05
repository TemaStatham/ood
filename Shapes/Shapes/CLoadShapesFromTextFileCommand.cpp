#include "CLoadShapesFromTextFileCommand.h"

CLoadShapesFromTextFileCommand::CLoadShapesFromTextFileCommand(CToolbar* reciever)
    :m_toolbar(reciever)
{
}

void CLoadShapesFromTextFileCommand::Execute() const
{
    std::string fileName;
    std::cin >> fileName;

    m_toolbar->LoadFromTextFile(fileName);
}
