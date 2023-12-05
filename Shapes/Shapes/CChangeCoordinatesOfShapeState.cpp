#include "CChangeCoordinatesOfShapeState.h"

void CChangeCoordinatesOfShapeState::ChangeShapeColor(CToolbar* context)
{
	context->TransitionTo(new CChangeShapeColorState);
}

void CChangeCoordinatesOfShapeState::ChangeShapeOutlineColor(CToolbar* context)
{
	context->TransitionTo(new CChangeShapeOutlineColorState);
}

void CChangeCoordinatesOfShapeState::ChangeOutlineThickness(CToolbar* context)
{
	context->TransitionTo(new CChangeOutlineThicknessState);
}

void CChangeCoordinatesOfShapeState::ChangeCoordinatesOfShape(CToolbar* context)
{
	
}
