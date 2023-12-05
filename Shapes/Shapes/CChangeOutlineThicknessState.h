#pragma once

#include "CState.h"
#include "CChangeCoordinatesOfShapeState.h"
#include "CChangeShapeColorState.h"
#include "CChangeShapeOutlineColorState.h"

class CChangeOutlineThicknessState : public CState {
public:
	void ChangeShapeColor(CToolbar* context) override;
	void ChangeShapeOutlineColor(CToolbar* context) override;
	void ChangeOutlineThickness(CToolbar* context) override;
	void ChangeCoordinatesOfShape(CToolbar* context) override;
};