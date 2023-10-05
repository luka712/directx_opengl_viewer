#ifndef MOUSE_STATE_HPP

#define MOUSE_STATE_HPP

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

		bool LeftButton;
		bool RightButton;
		bool MiddleButton;
	};
}

#endif