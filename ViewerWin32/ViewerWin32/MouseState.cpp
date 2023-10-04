#include "MouseState.hpp"

Viewer::MouseState::MouseState()
{
	LeftButton = false;
	RightButton = false;
	MiddleButton = false;
	ResetDeltas();
}

void Viewer::MouseState::ResetDeltas()
{
	DeltaX = 0;
	DeltaY = 0;
	DeltaWheelY = 0;
}