#include <iostream>
#include <fstream>
#include "CApplication.h"

const std::string INPUT_FILE_NAME = "Figures.txt";

int main()
{
    std::ifstream inF1(INPUT_FILE_NAME);

    sf::RenderWindow window(sf::VideoMode(1100, 900), "Visualization of shapes");

    CApplication* application = CApplication::GetInstance(inF1, std::cout, window);
    application->Start();

    return 0;
}
