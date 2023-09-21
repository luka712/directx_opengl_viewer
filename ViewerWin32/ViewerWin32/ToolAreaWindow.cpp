#include "ToolAreaWindow.hpp"
#include "ColorPicker.hpp"

namespace Viewer
{

	LRESULT ToolAreaWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		// TImpl* pThis = NULL;

		if (uMsg == WM_NCCREATE)
		{
			// get the pointer to the window from lpCreateParams which was set in CreateWindow
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
		// 	pThis = (TImpl*)pCreate->lpCreateParams;

			// set the window pointer in GWLP_USERDATA so we can get it later on
			// SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

			// pThis->m_hwnd = hwnd;
		}
		else
		{
			// pThis = (TImpl*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		}


		/*if (pThis)
		{
			return pThis->HandleMessage(uMsg, wParam, lParam);
		}
		else
		{*/
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	 //	}
	}

	bool ToolAreaWindow::Initialize(HWND parent, int width, int height, int xPos, int yPos)
	{
		LPCWSTR className = L"Tool Area";

		WNDCLASS wc = { 0 };

		wc.lpfnWndProc = WindowProc;
		wc.hInstance = GetModuleHandle(NULL);
		wc.lpszClassName = className;

		RegisterClass(&wc);

		m_handle = CreateWindow(className, L"Tool Area", WS_CHILD | WS_VISIBLE,
			xPos, yPos, width, height,
			parent, NULL, GetModuleHandle(NULL), this);

		if (!m_handle) 
		{
		 	DWORD error = GetLastError();
			MessageBox(NULL, L"Tool Area Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
			return false;
		}

		ColorPicker* colorPicker = new ColorPicker();
		colorPicker->Initialize(this);


		return true;
	}
}