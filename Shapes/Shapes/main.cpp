#include <iostream>
#include <fstream>
#include "CShapeController.h"

const std::string INPUT_FILE_NAME = "Figures.txt";

int main()
{
    std::ifstream inF1(INPUT_FILE_NAME);
    std::vector<std::shared_ptr<CShapeDecorator>> shapes;

    CShapeController shapeController(shapes, inF1, std::cout);

    shapeController.Start();

    return 0;
}
