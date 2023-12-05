#include "CChangeShapeColorState.h"

void CChangeShapeColorState::ChangeShapeColor(CToolbar* context)
{
	
}

void CChangeShapeColorState::ChangeShapeOutlineColor(CToolbar* context)
{
	context->TransitionTo(new CChangeShapeOutlineColorState);
}

void CChangeShapeColorState::ChangeOutlineThickness(CToolbar* context)
{
	context->TransitionTo(new CChangeOutlineThicknessState);
}

void CChangeShapeColorState::ChangeCoordinatesOfShape(CToolbar* context)
{
	context->TransitionTo(new CChangeCoordinatesOfShapeState);
}
