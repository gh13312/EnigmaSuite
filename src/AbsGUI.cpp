#include <include/AbsGUI.h>

// Constructor
bool AbsGUI::Init()
{
	// Passed instance into CreateWindowEx
	_hwnd = CreateWindowEx(_styleEx, _className, _windowName, _style,
		_x, _y, _width, _height,
		_hwndParent, _hMenu, _hInstance, this);

	if (!_hwnd)
	{
		return false;
	}
	else
	{
		return true;
	}
}

/* 
	Retrieve instance from lp param
	cast instance to AbsGUI object
	call an overrided windows procedure function by derived class
*/
LRESULT CALLBACK AbsGUI::MessageRouter(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	AbsGUI *wnd = 0;
	if (msg == WM_NCCREATE)
	{
		wnd = (AbsGUI*)(LPCREATESTRUCT(lp))->lpCreateParams;
		SetWindowLong(hwnd, GWL_USERDATA, long(wnd));
	}
	else
	{
		wnd = (AbsGUI*)(GetWindowLong(hwnd, GWL_USERDATA));
		if (wnd) 
		{
			switch (msg)
			{
				case WM_CREATE:
					return wnd->OnCreate(hwnd);
				case WM_COMMAND:
					return wnd->OnCommand(hwnd, wp);
				case WM_SIZE:
					return wnd->OnSize(lp);
				case WM_NOTIFY:
					return wnd->OnNotify(hwnd, lp);
				case WM_DESTROY:
					return wnd->OnDestroy();
				default:
					return DefWindowProc(hwnd, msg, wp, lp);
			}
		}
	}
	
	if (wnd)
	{
		wnd->WindowProcedure(hwnd, msg, wp, lp);
	}
	else
	{
		return DefWindowProc(hwnd, msg, wp, lp);
	}
}