#pragma once
#include "MainWindow.hpp"

namespace Viewer
{
	class RenderSurfaceWindow final : public BaseWindow<MainWindow>
	{
	public:
		LPCTSTR ClassName() const { return L"Render Surface"; }
		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}