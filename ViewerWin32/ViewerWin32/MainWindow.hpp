#pragma once

#include <vector>
#include "BaseWindow.hpp"
#include "UIControl.hpp"

namespace Viewer
{

	class MainWindow final : public BaseWindow<MainWindow>, UIControl
	{
	public:
		LPCTSTR ClassName() const { return L"Viewer Window Class"; }
		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	};

}