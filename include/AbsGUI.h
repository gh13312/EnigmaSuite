#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tchar.h>
#include <Commctrl.h>

#pragma comment( lib, "comctl32.lib" )

class AbsGUI {

	public:
		AbsGUI() {}
		static LRESULT CALLBACK MessageRouter(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
		virtual LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) = 0;
		
		virtual bool Init();
		virtual bool OnCreate(HWND hwnd) {	return false; }
		virtual bool OnSize(LPARAM lp) { return false; }
		virtual bool OnNotify(HWND hwnd, LPARAM lp) { return false; }
		virtual bool OnDestroy() { return false; }
		virtual bool OnCommand(HWND hwnd, WPARAM wp) { return false; }

	protected:
		HWND				_hwnd;
		DWORD				_styleEx;
		LPCTSTR				_className;
		LPCTSTR				_windowName;
		DWORD				_style;
		int					_x;
		int					_y;
		int					_width;
		int					_height;
		HWND				_hwndParent;
		HMENU				_hMenu;
		HINSTANCE			_hInstance;

};
