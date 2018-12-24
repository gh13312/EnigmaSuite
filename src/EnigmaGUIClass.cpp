#include <include/EnigmaGUIClass.h>

EnigmaGUIClass::EnigmaGUIClass(HINSTANCE hInst, const TCHAR* className)
{
	cbSize = sizeof(WNDCLASSEX);
	cbClsExtra = 0;
	cbWndExtra = 0;

	hInstance = hInst;
	hIcon = LoadIcon(NULL, IDI_APPLICATION);
	hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	hCursor = LoadCursor(NULL, IDC_ARROW);
	hbrBackground = (HBRUSH)(COLOR_WINDOW);

	lpszMenuName = NULL;
	lpszClassName = className;


	style = 0;
	lpfnWndProc = AbsGUI::MessageRouter;
	Register();
}

bool EnigmaGUIClass::Register()
{
	if (RegisterClassEx(this))
	{
		return true;
	}
	else
	{
		return false;
	}

}