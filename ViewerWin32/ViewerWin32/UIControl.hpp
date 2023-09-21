#pragma once

#include <Windows.h>
#include <vector>

namespace Viewer
{
	class UIControl
	{
	protected:
		HWND m_handle; 

		std::vector<UIControl*> m_children;
		UIControl* m_parent;

		void ShowLastErrorMessage();

public:
		inline HWND GetHandle() const { return m_handle; }

		void AddChild(UIControl* child);
	};
}