#include <include/EnigmaGUIClass.h>
#include <include/EnigmaGUI.h>
#include <iostream>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	//InitCommonControls();

	MSG msg;
	EnigmaGUIClass guiClass(hInst, TEXT("Main"));
	EnigmaGUI gui(hInst, TEXT("Suite"), guiClass.className());
	gui.Init();
	gui.show();

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}