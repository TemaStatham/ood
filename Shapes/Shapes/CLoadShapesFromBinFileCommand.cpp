#include "CLoadShapesFromBinFileCommand.h"

CLoadShapesFromBinFileCommand::CLoadShapesFromBinFileCommand(CToolbar* reciever)
    :m_toolbar(reciever)
{
}

void CLoadShapesFromBinFileCommand::Execute() const
{
    std::string fileName;
    std::cin >> fileName;

    m_toolbar->LoadFromBinFile(fileName);
}
