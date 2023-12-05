#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "CCanvas.h"
#include "CToolbar.h"
#include "CChangeOutlineThicknessVisitor.h"
#include "CChangeShapeOutlineColorVisitor.h"
#include "CChangeShapeColorVisitor.h"
#include "CFileSaver.h"
#include "CLoaderShapesFromFile.h"
#include "CLoaderShapesFromTextFile.h"

class CApplication {
public:
    static CApplication* GetInstance(std::string& fileName, std::ostream& output, sf::RenderWindow& window);

    void Start();

private:
    CApplication(std::string& fileName, ostream& output, sf::RenderWindow& window);

    void Read();
    void Write();
    void HandleEvent(sf::Event event);

    static CApplication* m_instance;

    std::string& m_fileName;
    std::ostream& m_out;

    sf::RenderWindow& m_window;

    CCanvas* m_canvas;
    CToolbar* m_toolbar;
    CLoaderShapesFromTextFile* m_loader;
};
