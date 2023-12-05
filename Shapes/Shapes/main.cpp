#include <iostream>
#include <fstream>
#include "CApplication.h"

std::string INPUT_FILE_NAME = "Figures.txt";

int main()
{
    sf::RenderWindow window(sf::VideoMode(1100, 900), "Visualization of shapes");

    CApplication* application = CApplication::GetInstance(INPUT_FILE_NAME, std::cout, window);
    application->Start();

    return 0;
}
