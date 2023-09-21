#pragma once


#include <windows.h>
#include <string>

namespace Viewer
{

    template <class TImpl>
    class BaseWindow
    {
    public:
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            TImpl* pThis = NULL;

            if (uMsg == WM_NCCREATE)
            {
                // get the pointer to the window from lpCreateParams which was set in CreateWindow
                CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
                pThis = (TImpl*)pCreate->lpCreateParams;

                // set the window pointer in GWLP_USERDATA so we can get it later on
                SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

                pThis->m_hwnd = hwnd;
            }
            else
            {
                pThis = (TImpl*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
            }


            if (pThis)
            {
                return pThis->HandleMessage(uMsg, wParam, lParam);
            }
            else
            {
                return DefWindowProc(hwnd, uMsg, wParam, lParam);
            }
        }

        BaseWindow() : m_hwnd(NULL) { }

        bool Initialize(
            LPCTSTR windowTitle,
            DWORD windowStyle,
            int width = CW_USEDEFAULT,
            int height = CW_USEDEFAULT,
            HWND parentHandle = 0,
            HMENU menuHandle = 0
        )
        {
            WNDCLASS wc = { 0 };


            wc.lpfnWndProc = TImpl::WindowProc;
            wc.hInstance = GetModuleHandle(NULL);
            wc.lpszClassName = ClassName();

            RegisterClass(&wc);

            // make x and y centered
            int xPos = CW_USEDEFAULT;
            int yPos = CW_USEDEFAULT;

            m_hwnd = CreateWindow(
                ClassName(), // the name of a registered window class
                windowTitle, // the title of a window
                windowStyle,
                xPos, yPos, 
                width, height, 
                parentHandle,
                menuHandle,
                GetModuleHandle(NULL),
                this // pass self as the parameter to WM_NCCREATE
            );

            return (m_hwnd ? true : false);
        }

        inline HWND GetWindowHandle() const { return m_hwnd; }

    protected:

        virtual LPCTSTR ClassName() const = 0;
        virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

        HWND m_hwnd;
    };
} // namespace Viewer