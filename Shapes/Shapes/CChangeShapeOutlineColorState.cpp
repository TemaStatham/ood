#include "CChangeShapeOutlineColorState.h"

void CChangeShapeOutlineColorState::ChangeShapeColor(CToolbar* context)
{
	context->TransitionTo(new CChangeShapeColorState);
}

void CChangeShapeOutlineColorState::ChangeShapeOutlineColor(CToolbar* context)
{
	
}

void CChangeShapeOutlineColorState::ChangeOutlineThickness(CToolbar* context)
{
	context->TransitionTo(new CChangeOutlineThicknessState);
}

void CChangeShapeOutlineColorState::ChangeCoordinatesOfShape(CToolbar* context)
{
	context->TransitionTo(new CChangeCoordinatesOfShapeState);
}