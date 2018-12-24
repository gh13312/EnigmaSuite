#include <include/EnigmaGUI.h>

EnigmaGUI::EnigmaGUI(HINSTANCE hInst, const TCHAR* windowName, const TCHAR* className)
	:AbsGUI()
{
	InitCommonControls();
	_styleEx = WS_EX_CLIENTEDGE;
	_className = className;
	_windowName = windowName;
	_style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	_x = CW_USEDEFAULT;
	_y = CW_USEDEFAULT;
	_width = GUI_DEFAULT_WIDTH;
	_height = GUI_DEFAULT_HEIGHT;
	_hwndParent = NULL;
	_hMenu = NULL;
	_hInstance = hInst;
}

void EnigmaGUI::show() {
	ShowWindow(_hwnd, SW_SHOW);
	UpdateWindow(_hwnd);
}

LRESULT CALLBACK EnigmaGUI::WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_CREATE:
		return OnCreate(hwnd);
	case WM_NOTIFY:
		return OnNotify(hwnd, lp);
	case WM_COMMAND:
		return OnCommand(hwnd, wp);
	case WM_SIZE:
		return OnSize(lp);
	case WM_DESTROY:
		return OnDestroy();
	default:
		return DefWindowProc(hwnd, msg, wp, lp);
	}
	return 0;
}

bool EnigmaGUI::OnCreate(HWND hwnd)
{
	CreateMenuControls(hwnd);
	CreateTabControls(hwnd);
	CreateProxyControls(hwnd);
	CreateSpiderControls(hwnd);
	CreateRepeaterControls(hwnd);
	CreateLogControls(hwnd);
	ShowTabControls(hwnd, TAB_PROXY);
	ProxyInit();

	//TODO
	//SpiderInit();
	//LoggerInit();
	return 0;
}

bool EnigmaGUI::OnSize(LPARAM lp)
{
	SetWindowPos(m_hwndTab, NULL, 0, 0, LOWORD(lp), HIWORD(lp), SWP_SHOWWINDOW);
	SetWindowPos(hwndProxyRequest, NULL, 10, 75, LOWORD(lp) - 25, HIWORD(lp) - 120, SWP_SHOWWINDOW);
	SetWindowPos(hwndRepeaterReq, NULL, 10, 65, LOWORD(lp) / 2 - 20, HIWORD(lp) - 130, 0);
	SetWindowPos(hwndRepeaterRes, NULL, LOWORD(lp) / 2, 65, LOWORD(lp) / 2 - 20, HIWORD(lp) - 130, 0);
	return 0;
}

bool EnigmaGUI::OnDestroy()
{
	PostQuitMessage(0);
	return 0;
}

bool EnigmaGUI::OnNotify(HWND hwnd, LPARAM lp)
{
	switch (((LPNMHDR)lp)->code)
	{
		case TCN_SELCHANGE:
		{
			int hwndCurrentTab;

			hwndCurrentTab = TabCtrl_GetCurSel(m_hwndTab);
			switch (hwndCurrentTab)
			{
			case TAB_PROXY:
				HideTabControls(hwnd, prevTab);
				ShowTabControls(hwnd, TAB_PROXY);
				break;
			case TAB_SPIDER:
				HideTabControls(hwnd, prevTab);
				ShowTabControls(hwnd, TAB_SPIDER);
				break;
			case TAB_REPEATER:
				HideTabControls(hwnd, prevTab);
				ShowTabControls(hwnd, TAB_REPEATER);
				break;
			case TAB_LOG:
				HideTabControls(hwnd, prevTab);
				ShowTabControls(hwnd, TAB_LOG);
			default:
				break;

			}
			break;
		}
	}
	return 0;
}

bool EnigmaGUI::OnCommand(HWND hwnd, WPARAM wp)
{
	switch (wp)
	{
		case PROXY_BUTTON_HTTP_REQUEST:
			ProxySendRequest(hwnd);
			break;
		case REPEATER_BUTTON_HTTP_REQUEST:
			RepeaterSendRequest(hwnd);
			break;
		case FILE_MENU_EXIT:
			return OnDestroy();
	}
	return 0;
}

void EnigmaGUI::CreateMenuControls(HWND hwnd)
{
	m_hMenu = CreateMenu();
	HMENU hFile_menu = CreateMenu();

	AppendMenu(m_hMenu, MF_POPUP, (UINT_PTR)hFile_menu, FILE_MENU);
	AppendMenu(hFile_menu, MF_STRING, FILE_MENU_EXIT, FILE_EXIT);
	SetMenu(hwnd, m_hMenu);
}

void EnigmaGUI::CreateTabControls(HWND hwnd)
{
	RECT rcClient;
	TCITEM tabinfo;

	// get dimension of parent window
	GetClientRect(_hwnd, &rcClient);
	m_hwndTab = CreateWindowEx(
		0,
		"SysTabControl32",
		"",
		WS_CHILD | WS_CLIPSIBLINGS,
		0, 0, GUI_DEFAULT_WIDTH, GUI_DEFAULT_HEIGHT,
		hwnd, (HMENU)TAB_MAIN, _hInstance, NULL);

	//const_cast<char*>
	tabinfo.mask = TCIF_TEXT;
	tabinfo.pszText = (TCHAR *)"Proxy";
	TabCtrl_InsertItem(m_hwndTab, TAB_PROXY, &tabinfo);

	tabinfo.mask = TCIF_TEXT;
	tabinfo.pszText = (TCHAR *)"Spider";
	TabCtrl_InsertItem(m_hwndTab, TAB_SPIDER, &tabinfo);

	tabinfo.mask = TCIF_TEXT;
	tabinfo.pszText = (TCHAR *)"Repeater";
	TabCtrl_InsertItem(m_hwndTab, TAB_REPEATER, &tabinfo);

	tabinfo.mask = TCIF_TEXT;
	tabinfo.pszText = (TCHAR *)"Log";
	TabCtrl_InsertItem(m_hwndTab, TAB_LOG, &tabinfo);

	// default tab
	prevTab = TAB_PROXY;
	ShowWindow(m_hwndTab, SW_SHOW);
}

void EnigmaGUI::CreateProxyControls(HWND hwnd)
{
	hwndButtonSend = CreateWindowEx(0, _T("Button"), _T("Forward"),
		WS_CHILD | WS_EX_CONTROLPARENT,
		10, 35, 100, 23,
		hwnd, (HMENU)PROXY_BUTTON_HTTP_REQUEST, _hInstance, NULL);

	hwndProxyRequest = CreateWindowEx(0, _T("Edit"), _T("Proxy"),
		WS_CHILD | WS_EX_CONTROLPARENT | WS_BORDER | WS_VSCROLL | ES_MULTILINE,
		10, 75, GUI_DEFAULT_WIDTH - 50, GUI_DEFAULT_HEIGHT - 180,
		hwnd, (HMENU)PROXY_EDIT_HTTP_REQUEST, _hInstance, NULL);

	ShowWindow(hwndProxyRequest, SW_HIDE);
	UpdateWindow(m_hwndTab);
}
void EnigmaGUI::CreateSpiderControls(HWND hwnd)
{
	RECT rcClient;
	GetClientRect(m_hwndTab, &rcClient);

	HWND hWndHttpRequest = CreateWindowEx(0, _T("Edit"), _T("Spider"),
		WS_CHILD,
		10, 100, 100, 25,
		hwnd, (HMENU)SPIDER_HTTP_FOUND, _hInstance, NULL);

	ShowWindow(hWndHttpRequest, SW_HIDE);
	UpdateWindow(m_hwndTab);
}

void EnigmaGUI::CreateRepeaterControls(HWND hwnd)
{
	RECT rcClient;
	GetClientRect(hwnd, &rcClient);

	HWND hwndButtonSend = CreateWindowEx(0, _T("Button"), _T("Send Request"),
		WS_CHILD | WS_EX_CONTROLPARENT,
		10, 35, 100, 23,
		hwnd, (HMENU)REPEATER_BUTTON_HTTP_REQUEST, _hInstance, NULL);

	HWND hwndHostStatic = CreateWindowEx(0, _T("Static"), _T("Host: "),
		WS_CHILD | WS_EX_CONTROLPARENT,
		125, 35, 50, 23,
		hwnd, (HMENU)REPEATER_STATIC_HOST, _hInstance, NULL);

	hwndHostField = CreateWindowEx(0, _T("Edit"), _T(REPEATER_HOST_DEFAULT.c_str()),
		WS_CHILD | WS_EX_CONTROLPARENT | WS_BORDER | ES_AUTOHSCROLL,
		175, 35, 300, 23,
		hwnd, (HMENU)REPEATER_EDIT_HOST, _hInstance, NULL);

	HWND hwndPortStatic = CreateWindowEx(0, _T("Static"), _T("Port: "),
		WS_CHILD | WS_EX_CONTROLPARENT,
		485, 35, 50, 23,
		hwnd, (HMENU)REPEATER_STATIC_PORT, _hInstance, NULL);

	hwndPortField = CreateWindowEx(0, _T("Edit"), _T(REPEATER_PORT_DEFAULT.c_str()),
		WS_CHILD | WS_EX_CONTROLPARENT | WS_BORDER,
		535, 35, 70, 23,
		hwnd, (HMENU)REPEATER_EDIT_PORT, _hInstance, NULL);

	hwndRepeaterReq = CreateWindowEx(0, _T("Edit"), _T(REPEATER_REQ_DEFAULT.c_str()),
		WS_CHILD | WS_BORDER | WS_EX_CONTROLPARENT |
		WS_VSCROLL | ES_MULTILINE,
		10, 65, GUI_DEFAULT_WIDTH / 2 - 20, GUI_DEFAULT_HEIGHT - 130,
		hwnd, (HMENU)REPEATER_HTTP_REQUEST, _hInstance, NULL);

	hwndRepeaterRes = CreateWindowEx(0, _T("Edit"), _T("Response"),
		WS_CHILD | WS_BORDER | WS_EX_CONTROLPARENT |
		WS_VSCROLL | ES_MULTILINE,
		GUI_DEFAULT_WIDTH / 2, 65, GUI_DEFAULT_WIDTH / 2 - 20, GUI_DEFAULT_HEIGHT - 130,
		hwnd, (HMENU)REPEATER_HTTP_RESPONSE, _hInstance, NULL);

	UpdateWindow(m_hwndTab);
}

void EnigmaGUI::CreateLogControls(HWND hwnd)
{
	RECT rcClient;
	GetClientRect(m_hwndTab, &rcClient);

	HWND hWndEnigmaLogs = CreateWindowEx(0, _T("Edit"), _T("Log"),
		WS_CHILD | WS_EX_CONTROLPARENT | WS_BORDER | WS_VSCROLL | ES_MULTILINE,
		10, 35, GUI_DEFAULT_WIDTH - 50, GUI_DEFAULT_HEIGHT - 180,
		hwnd, (HMENU)LOG_INFO_FIELD, _hInstance, NULL);

	EnableWindow(hWndEnigmaLogs, false);

	ShowWindow(hWndEnigmaLogs, SW_HIDE);
	UpdateWindow(m_hwndTab);
}

void EnigmaGUI::HideTabControls(HWND hwnd, int tab_id)
{
	HWND hwndControl;
	/// tab control ID starts @tab_id * 100 + 1
	int control_id = tab_id * 100;
	do
	{
		control_id += 1;
		hwndControl = GetDlgItem(hwnd, control_id);
		ShowWindow(hwndControl, SW_HIDE);
	} while (hwndControl != 0);
}

void EnigmaGUI::ShowTabControls(HWND hwnd, int tab_id)
{
	HWND hwndControl;
	/// tab control ID starts @tab_id * 100 + 1
	int control_id = tab_id * 100;
	do
	{
		control_id += 1;
		hwndControl = GetDlgItem(hwnd, control_id);
		ShowWindow(hwndControl, SW_SHOW);
	} while (hwndControl != 0);
	prevTab = tab_id;
}

void EnigmaGUI::RepeaterSendRequest(HWND hwnd)
{

	// get host
	int size = GetWindowTextLength(hwndHostField);
	char * hostchar = new char[size + 1];
	GetWindowText(hwndHostField, hostchar, size + 1);
	std::string host = std::string(hostchar);

	// get port
	size = GetWindowTextLength(hwndPortField);
	char * port_str = new char[size + 1];
	GetWindowText(hwndPortField, port_str, size + 1);
	int port = atoi(port_str);

	// get request text
	size = GetWindowTextLength(hwndRepeaterReq);
	char *request_data = new char[size + 1];
	GetWindowText(hwndRepeaterReq, request_data, size + 1);
	std::string request_str = std::string(request_data);
	
	EnigmaRepeater repeater(host, port);
	SOCKET client = repeater.CreateConnection();
	repeater.Send(client, request_str);
	repeater.Receive(client, hwndRepeaterRes);
}

void EnigmaGUI::ProxyInit()
{
	proxy = EnigmaProxy(hwndProxyRequest, hwndButtonSend);
	std::thread t_service(&EnigmaProxy::StartProxyService, std::ref(proxy));
	t_service.detach();
}

void EnigmaGUI::ProxySendRequest(HWND hwnd)
{
	//MessageBox(hwnd, proxy.gethostname().c_str(), "", MB_OK);
	//MessageBox(hwnd, proxy.getrequest().c_str(), "", MB_OK);
	proxy.ForwardReceive();
}