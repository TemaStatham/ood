#pragma once

#include <iostream>
#include <algorithm>
#include "CCanvas.h"
#include <fstream>
#include "IBuilder.h"
#include "CDirector.h"
#include "CCircleBuilder.h"
#include "CTriangleBuilder.h"
#include "CRectangleBuilder.h"
#include "CCompositeBuilder.h"

class CLoaderShapesFromFile
{
public:
    CLoaderShapesFromFile(CCanvas* canvas);

    void LoadShapesFromFile(const std::string& fileName);

protected:
    virtual std::stringstream GetStringStream(const std::string& fileName) const = 0;
private:
    void CreateShape(const std::string& typeOfFigureAsString, std::stringstream& stream);

    void CreateCircle(std::stringstream& stream);
    void CreateRectangle(std::stringstream& stream);
    void CreateTriangle(std::stringstream& stream);
    void CreateCompound(std::stringstream& stream);

    std::vector<float> GetParams(std::stringstream& stream, size_t countParams);

    CCanvas* m_canvas;
    CDirector* m_director;
};
