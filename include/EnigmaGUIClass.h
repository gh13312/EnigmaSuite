#pragma once
#include <include/AbsGUI.h>

class EnigmaGUIClass :protected WNDCLASSEX {
	public:
		EnigmaGUIClass(HINSTANCE hInst, const TCHAR * className);

		virtual bool Register();

		virtual const TCHAR * className() const {
			return lpszClassName;
		}
	protected:
};