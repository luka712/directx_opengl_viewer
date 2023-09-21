#pragma once
#include "MainWindow.hpp"
#include "UIControl.hpp"

namespace Viewer
{
	class ToolAreaWindow final : public UIControl
	{
	private:
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	public:
		bool Initialize(HWND parent, int width, int height, int xOffset = 0, int yOffset = 0);

	};
}