#pragma once

namespace Viewer
{
	struct MouseState
	{
		MouseState();

		void ResetDeltas();

		// @brief The change of the x position of the mouse.
		int DeltaX;

		// @brief The change of the y position of the mouse.
		int DeltaY;

		// @brief The change of the y position of the mouse.
		int DeltaWheelY;

		int X, Y;
		int LastX, LastY;

		bool LeftButton;
		bool RightButton;
		bool MiddleButton;

	};
}