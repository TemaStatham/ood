#include "CChangeOutlineThicknessState.h"

void CChangeOutlineThicknessState::ChangeShapeColor(CToolbar* context)
{
	context->TransitionTo(new CChangeShapeColorState);
}

void CChangeOutlineThicknessState::ChangeShapeOutlineColor(CToolbar* context)
{
	context->TransitionTo(new CChangeShapeOutlineColorState);
}

void CChangeOutlineThicknessState::ChangeOutlineThickness(CToolbar* context)
{
	
}

void CChangeOutlineThicknessState::ChangeCoordinatesOfShape(CToolbar* context)
{
	context->TransitionTo(new CChangeCoordinatesOfShapeState);
}