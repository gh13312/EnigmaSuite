#pragma once
#include <include/EnigmaRepeater.h>
#include <include/EnigmaProxy.h>
#include <include/CONSTANTS.h>
#include <include/EnigmaGUIClass.h>
#include <regex>

class EnigmaGUI : public AbsGUI {

public:
	EnigmaGUI(HINSTANCE hInst, const TCHAR *windowName, const TCHAR *className);
	virtual LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
	void show();
	
	virtual bool OnCreate(HWND hwnd);
	virtual bool OnSize(LPARAM lp);
	virtual bool OnNotify(HWND hwnd, LPARAM lp);
	virtual bool OnDestroy();
	virtual bool OnCommand(HWND hwnd, WPARAM wp);

	// ON_CREATE
	void CreateMenuControls(HWND hwnd);
	void CreateTabControls(HWND hwnd);
	void CreateProxyControls(HWND hwnd);
	void CreateSpiderControls(HWND hwnd);
	void CreateRepeaterControls(HWND hwnd);
	void CreateLogControls(HWND hwnd);
	void ProxyInit();

	// TAB functions
	void HideTabControls(HWND hWnd, int tab_id);
	void ShowTabControls(HWND hWnd, int tab_id);

	// Proxy functionality
	void ProxySendRequest(HWND hwnd);

	// Repeater Functionality
	void RepeaterSendRequest(HWND hwnd);


private:
	// GUI handlers
	HMENU				m_hMenu;
	HWND				m_hwndTab;
	
	// PROXY handlers
	EnigmaProxy			proxy = EnigmaProxy(0,0);
	HWND				hwndProxyRequest;
	HWND				hwndButtonSend;

	// Repeater Edit Handlers
	HWND				hwndHostField;
	HWND				hwndPortField;
	HWND				hwndRepeaterReq;
	HWND				hwndRepeaterRes;


	int					prevTab = 0;
};


