#pragma once
#include <windows.h>
#include "UIControl.hpp"

namespace Viewer
{
	class ColorPicker final : public UIControl
	{
	public:

		bool Initialize(UIControl* parent);

		void Open();
	};
}