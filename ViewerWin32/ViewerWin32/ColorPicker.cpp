#include "ColorPicker.hpp"

namespace Viewer
{

	bool Viewer::ColorPicker::Initialize(UIControl* parent)
	{
		parent->AddChild(this);
			
		// Create a button for selecting a color
		HWND hButton = CreateWindow(L"BUTTON", L"Select Color",
			WS_CHILD | WS_VISIBLE ,
			10, 10, 100, 30,
			parent->GetHandle(),
			NULL, GetModuleHandle(NULL), this);

		CHOOSECOLOR cc;                 // common dialog box structure 
		static COLORREF acrCustClr[16]; // array of custom colors 
		HBRUSH hbrush;                  // brush handle
		static DWORD rgbCurrent;        // initial color selection

		// Initialize CHOOSECOLOR 
		ZeroMemory(&cc, sizeof(cc));
		cc.lStructSize = sizeof(cc);
		cc.hwndOwner = m_parent->GetHandle();
		cc.lpCustColors = (LPDWORD)acrCustClr;
		cc.rgbResult = rgbCurrent;
		cc.Flags = CC_FULLOPEN | CC_RGBINIT;

		if (ChooseColor(&cc) == TRUE)
		{
			hbrush = CreateSolidBrush(cc.rgbResult);
			rgbCurrent = cc.rgbResult;
		}

		return true;
	}

	void Viewer::ColorPicker::Open()
	{
	
	}

}
