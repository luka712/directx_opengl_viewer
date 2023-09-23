#pragma once


#include <string>

namespace Viewer
{
	class Win32ErrorUtil final
	{
	public:
		static void DisplayLastErrorMessage();
	};
}