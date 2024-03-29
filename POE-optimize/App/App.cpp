#include "App.h"
#include "Modules/Windows/tray.h"

using namespace std;

App::App()
{
	using std::string;
	using std::wstring;

	try {

		this->InitWindow();
		this->InitControls();
		this->cacheCleaner = CacheCleaner::getInstance();
		this->cnf = Config::getInstance();
		this->ConfToControls();
		this->RegistryInConf();
		this->setUpCacheCleaner();
	}
	catch (const std::exception& e) {

		string ExceptData = e.what();

		MessageBox(nullptr, wstring(begin(ExceptData), end(ExceptData)).c_str(), L"App crash", MB_ICONERROR | MB_OK);
		ExitProcess(EXIT_FAILURE);
	}
}

App::~App()
{
}

int App::Run()
{
	MSG msg{};
	ShowWindow(this->m_hwnd, SW_SHOWDEFAULT);
	UpdateWindow(this->m_hwnd);

	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return EXIT_SUCCESS;
}

void App::InitWindow()
{

	using std::runtime_error;

	HICON hIcon = static_cast<HICON>(LoadImage(NULL, L"Assets\\app.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE));

	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = hIcon;
	wc.hIconSm = hIcon;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpfnWndProc = App::AppProcess;
	wc.lpszClassName = this->className.c_str();
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wc)) {
		throw runtime_error("Error, can't register main window class!");
	}

	RECT windowRC{ 0, 0, this->AppWidth, this->AppHeight };
	AdjustWindowRect(&windowRC, WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, false);

	this->m_hwnd = CreateWindowExW(
		0,
		this->className.c_str(),
		this->AppName.c_str(),
		WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
		(GetSystemMetrics(SM_CXSCREEN) - windowRC.right) / 2.3,
		(GetSystemMetrics(SM_CXSCREEN) - windowRC.bottom) / 4,
		windowRC.right, windowRC.bottom, nullptr, nullptr, nullptr, this);

	if (!this->m_hwnd) {
		throw runtime_error("Error, can't create main window!");
	}
}

void App::InitControls()
{
	using std::runtime_error;

	int CONTROL_HEIHGT = 25;
	int BUTTON_WIDTH = 165;
	int EDIT_WIDTH = 200;
	int NUM_EDIT_WIDTH = 50;

	int BUTTON_X = 210;
	int EDIT_X = 10;

	int bottomBlockStart = this->AppHeight - 250;

	
	this->m_hwndButton = CreateWindowEx(
		0,
		L"BUTTON",
		L"Play",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		this->AppWidth - 90, 
		this->AppHeight - 70,
		70,
		CONTROL_HEIHGT,
		this->m_hwnd,
		(HMENU) App::CTRLS_ID::PLAY_BTN_ID,
		nullptr,
		nullptr
	);

	this->m_hvndPathOfExilePath = CreateWindowEx(
		0,
		L"EDIT",
		L"",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_READONLY | WS_BORDER | WS_EX_STATICEDGE,
		EDIT_X, 20, EDIT_WIDTH, CONTROL_HEIHGT,
		this->m_hwnd,
		(HMENU)App::CTRLS_ID::PATH_POE_ID,
		nullptr,
		nullptr
	);


	this->m_hvndPathOfExileBtn = CreateWindowEx(
		0,
		L"BUTTON",
		L"Poe dir",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE | ES_LEFT ,
		BUTTON_X, 20, BUTTON_WIDTH, CONTROL_HEIHGT,
		this->m_hwnd,
		(HMENU)App::CTRLS_ID::PATH_POE_BTN_ID,
		nullptr,
		nullptr
	);

	this->m_hvndPathMyDocEdit = CreateWindowEx(
		0,
		L"EDIT",
		L"",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_READONLY | WS_BORDER | WS_EX_STATICEDGE,
		EDIT_X, 50, EDIT_WIDTH, CONTROL_HEIHGT,
		this->m_hwnd,
		(HMENU)App::CTRLS_ID::PATH_POE_MY_DOC_ID,
		nullptr,
		nullptr
	);

	this->m_hvndPathMyDocEditBtn = CreateWindowEx(
		0,
		L"BUTTON",
		L"My doc poe dir",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE | ES_LEFT,
		BUTTON_X, 50, BUTTON_WIDTH, CONTROL_HEIHGT,
		this->m_hwnd,
		(HMENU)App::CTRLS_ID::PATH_POE_MY_DOC_BTN_ID,
		nullptr,
		nullptr
	);
	
	this->m_hwndPathAhkEdit = CreateWindowEx(
		0,
		L"EDIT",
		L"",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_READONLY | WS_BORDER | WS_EX_STATICEDGE,
		EDIT_X, 80, EDIT_WIDTH, CONTROL_HEIHGT,
		this->m_hwnd,
		(HMENU)App::CTRLS_ID::PATH_AHK_ID,
		nullptr,
		nullptr
	);

	this->m_hvndPathAhkBtn = CreateWindowEx(
		0,
		L"BUTTON",
		L"Ahk path",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE | ES_LEFT,
		BUTTON_X, 80, BUTTON_WIDTH, CONTROL_HEIHGT,
		this->m_hwnd,
		(HMENU)App::CTRLS_ID::PATH_AHK_BTN,
		nullptr,
		nullptr
	);
	
	this->m_hvndPoeTradeEdit = CreateWindowEx(
		0,
		L"EDIT",
		L"",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_READONLY | WS_BORDER | WS_EX_STATICEDGE,
		EDIT_X, 110, EDIT_WIDTH, CONTROL_HEIHGT,
		this->m_hwnd,
		(HMENU)App::CTRLS_ID::PATH_POE_TRADE_ID,
		nullptr,
		nullptr
	);

	this->m_hvndPoeTradeBtn = CreateWindowEx(
		0,
		L"BUTTON",
		L"Poe trade macro",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE | ES_LEFT,
		BUTTON_X, 110, BUTTON_WIDTH, CONTROL_HEIHGT,
		this->m_hwnd,
		(HMENU)App::CTRLS_ID::PATH_POE_TRADE_BTN,
		nullptr,
		nullptr
	);
	
	this->m_hvndAwakePoeTradeEdit = CreateWindowEx(
		0,
		L"EDIT",
		L"",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_READONLY | WS_BORDER | WS_EX_STATICEDGE,
		EDIT_X, 140, EDIT_WIDTH, CONTROL_HEIHGT,
		this->m_hwnd,
		(HMENU)App::CTRLS_ID::PATH_AWAKE_TRADE_ID,
		nullptr,
		nullptr
	);

	this->m_hvndAwakePoeTradeBtn = CreateWindowEx(
		0,
		L"BUTTON",
		L"Awakened POE trade",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE | ES_LEFT,
		BUTTON_X, 140, BUTTON_WIDTH, CONTROL_HEIHGT,
		this->m_hwnd,
		(HMENU)App::CTRLS_ID::PATH_AWAKE_TRADE_BTN,
		nullptr,
		nullptr
	);
	
	this->m_hvndPathPOBEdit = CreateWindowEx(
		0,
		L"EDIT",
		L"",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_READONLY | WS_BORDER | WS_EX_STATICEDGE,
		EDIT_X, 170, EDIT_WIDTH, CONTROL_HEIHGT,
		this->m_hwnd,
		(HMENU)App::CTRLS_ID::PATH_POB_ID,
		nullptr,
		nullptr
	);

	this->m_hvndPathPOBBtn = CreateWindowEx(
		0,
		L"BUTTON",
		L"POB",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE | ES_LEFT,
		BUTTON_X, 170, BUTTON_WIDTH, CONTROL_HEIHGT,
		this->m_hwnd,
		(HMENU)App::CTRLS_ID::PATH_POB_BTN_ID,
		nullptr,
		nullptr
	);

	this->m_hvndIntervalLabel = CreateWindowEx(
		0,
		L"STATIC",
		L"Clear cache interval (default 3 minutes)",
		WS_CHILD | WS_VISIBLE,
		EDIT_X, bottomBlockStart, 400, CONTROL_HEIHGT,
		this->m_hwnd,
		(HMENU)App::LABELS_ID::INTERVAL_LABEL_ID,
		nullptr,
		nullptr
	);


	this->m_hvndClearCacheInterval = CreateWindowEx(
		0,
		L"EDIT",
		L"",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER | WS_EX_STATICEDGE | ES_NUMBER,
		EDIT_X, bottomBlockStart + CONTROL_HEIHGT, NUM_EDIT_WIDTH, CONTROL_HEIHGT,
		this->m_hwnd,
		(HMENU)App::CTRLS_ID::CLEAR_CACHE_INTERVAL_ID,
		nullptr,
		nullptr
	);



	HFONT hFont = CreateFont(18, 0, 0, 0, FW_REGULAR, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Roboto");

	SendMessage(this->m_hwndButton, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(this->m_hvndPathOfExilePath, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(this->m_hvndPathOfExileBtn, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(this->m_hvndPathMyDocEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(this->m_hvndPathMyDocEditBtn, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(this->m_hwndPathAhkEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(this->m_hvndPathAhkBtn, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(this->m_hvndPoeTradeEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(this->m_hvndPoeTradeBtn, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(this->m_hvndAwakePoeTradeEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(this->m_hvndAwakePoeTradeBtn, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(this->m_hvndPathPOBEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(this->m_hvndPathPOBBtn, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(this->m_hvndClearCacheInterval, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(this->m_hvndIntervalLabel, WM_SETFONT, (WPARAM)hFont, TRUE);
}

void App::ConfToControls() {
	CString s = this->cnf->getKey("POE");
	if (!s.IsEmpty()) {
		SetWindowText(this->m_hvndPathOfExilePath, s);
	}
	
	s = this->cnf->getKey("POE_DOC");

	if (!s.IsEmpty()) {
		SetWindowText(this->m_hvndPathMyDocEdit, s);
	}

	s = this->cnf->getKey("AHK");

	if (!s.IsEmpty()) {
		SetWindowText(this->m_hwndPathAhkEdit, s);
	}

	s = this->cnf->getKey("POE_TRADE");

	if (!s.IsEmpty()) {
		SetWindowText(this->m_hvndPoeTradeEdit, s);
	}

	s = this->cnf->getKey("AWAKENED_POE_TRADE");

	if (!s.IsEmpty()) {
		SetWindowText(this->m_hvndAwakePoeTradeEdit, s);
	}

	s = this->cnf->getKey("POB");

	if (!s.IsEmpty()) {
		SetWindowText(this->m_hvndPathPOBEdit, s);
	}
}


void App::RegistryInConf() {

	if (this->cnf->getKey(_T("AHK")).IsEmpty()) {
		CString AhkInstallPath = getRegistryKey(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\AutoHotkey"), _T("InstallDir"));
		if (AhkInstallPath != "bad") {
			this->cnf->setKey(_T("AHK"), AhkInstallPath);
			SetWindowText(this->m_hwndPathAhkEdit, AhkInstallPath);
		}
	}

	if (this->cnf->getKey(_T("POE")).IsEmpty()) {
		CString poeInstallPath = getRegistryKey(HKEY_CURRENT_USER, L"SOFTWARE\\GrindingGearGames\\Path of Exile", L"InstallLocation");
		if (poeInstallPath != L"bad") {
			this->cnf->setKey(_T("POE"), poeInstallPath);
			SetWindowText(this->m_hvndPathOfExilePath, poeInstallPath);
		}
	}
	
	if (this->cnf->getKey(_T("POB")).IsEmpty()) {
		CString pobPath = getRegistryKey(HKEY_CLASSES_ROOT, L"pob\\DefaultIcon", L"");
	
		if (pobPath != L"bad") {
			this->cnf->setKey(_T("POB"), pobPath);
			SetWindowText(this->m_hvndPathPOBEdit, pobPath);
		}
	}

	if (this->cnf->getKey(_T("ClearCacheInterval")).IsEmpty()) {
		this->cnf->setKey(_T("ClearCacheInterval"), this->DefaultClearCacheInterval);
		SetWindowText(this->m_hvndClearCacheInterval, this->DefaultClearCacheInterval);
	} else {
		SetWindowText(this->m_hvndClearCacheInterval, this->cnf->getKey(_T("ClearCacheInterval")));
	}
}


void App::setUpCacheCleaner()
{
	this->cacheCleaner->setClearCacheInterval(this->cnf->getKey(_T("ClearCacheInterval")));
	
	vector<CString> dirs;
	CString poeDir = this->cnf->getKey(_T("POE"));
	CString poeDocDir = this->cnf->getKey(_T("POE_DOC"));

	if (!poeDir.IsEmpty()) {
		dirs.push_back(poeDir + "\\logs\\");
	}

	if (!poeDocDir.IsEmpty()) {
		dirs.push_back(poeDocDir + "\\Minimap\\");
		dirs.push_back(poeDocDir + "\\MOTDCache\\");
		dirs.push_back(poeDocDir + "\\ShaderCacheD3D11\\");
		dirs.push_back(poeDocDir + "\\ShopImages\\");
		dirs.push_back(poeDocDir + "\\DailyDealCache\\");
	}

	this->cacheCleaner->setClearCacheDirs(dirs);
	this->cacheCleaner->setUpClearCacheThread();
}

void App::play()
{
	if (!this->cnf->getKey(_T("POE_TRADE")).IsEmpty() && !this->cnf->getKey(_T("AHK")).IsEmpty()) {
		CString ahk = this->cnf->getKey(_T("AHK")) + "\\" + this->AhkFileName;
		ShellExecute(NULL, L"open", ahk, this->cnf->getKey(_T("POE_TRADE")), 0, SW_SHOWNORMAL);
	}

	if (!this->cnf->getKey(_T("AWAKENED_POE_TRADE")).IsEmpty()) {

		ShellExecute(NULL, L"open", this->cnf->getKey(_T("AWAKENED_POE_TRADE")), NULL, 0, SW_SHOWNORMAL);
	}

	if (!this->cnf->getKey(_T("POB")).IsEmpty()) {
		ShellExecute(NULL, L"open", this->cnf->getKey(_T("POB")), NULL, 0, SW_SHOWNORMAL);
	}

	
	Sleep(5000);

	if (!this->cnf->getKey(_T("POE")).IsEmpty()) {
		CString poe = this->cnf->getKey(_T("POE")) + "\\" + this->PoeFileName;
		ShellExecute(NULL, L"open", poe, NULL, this->cnf->getKey(_T("POE")), SW_SHOWNORMAL);
	}
}


LRESULT App::AppProcess(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	App* pApp;
	if (uMsg == WM_NCCREATE) {
		pApp = (App*) ((CREATESTRUCT*) lParam)->lpCreateParams;
		SetLastError(0);
		if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pApp)) {
			if (GetLastError() != 0) {
				return false;
			}
		}
	} else {
		pApp = (App*) GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}

	if (pApp != nullptr) {
		pApp->m_hwnd = hWnd;
		return pApp->WINProcess(hWnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT App::WINProcess(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	using namespace std;
	static HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));

	switch (uMsg) {
		// Set a static controls bg color #fff
		case WM_CTLCOLORSTATIC: 
		{
			HDC hdcStatic = (HDC) wParam;
			SetTextColor(hdcStatic, RGB(0, 0, 0));
			SetBkColor(hdcStatic, RGB(255, 255, 255));
			return (INT_PTR) hBrush;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(EXIT_SUCCESS);
			break;
		}
		case WM_COMMAND:
		{
			return this->AppCommand(hWnd, uMsg, wParam, lParam);
		}
		case WM_SYSCOMMAND:
		{
			WORD param = LOWORD(wParam);
			
			if (param == SC_MINIMIZE) {
				ShowWindow(this->m_hwnd, SW_HIDE);
				to_tray(this->m_hwnd, this->nf);
				break;
			}
			if (param == SC_CLOSE) {
				PostQuitMessage(EXIT_SUCCESS);
				break;
			}
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
		case SWM_TRAYMSG:
		{
			switch (lParam)
			{
				case WM_LBUTTONDBLCLK:
				{
					ShowWindow(this->m_hwnd, SW_SHOWDEFAULT);
					UpdateWindow(this->m_hwnd);
					from_tray(this->nf);
				}
				case WM_RBUTTONDOWN:
				{
					break;
				}
				case WM_CONTEXTMENU: 
				{
					break;
				}
			}

			break;
		}
		default:
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;
		}

	}
	return 0;
}

LRESULT App::AppCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	App::CTRLS_ID CTRL = (App::CTRLS_ID) LOWORD(wParam);
	int actionCode = HIWORD(wParam);

	switch (CTRL) {

		case App::CTRLS_ID::PLAY_BTN_ID: {
			this->play();
			break;
		}
		case App::CTRLS_ID::PATH_POE_BTN_ID: {
			CString folder = BrowseForFolder(hWnd, L"Select Folder", L"C:\\");
			SetWindowText(this->m_hvndPathOfExilePath, folder);
			this->cnf->setKey(_T("POE"), folder);

			break;
		}
		case App::CTRLS_ID::PATH_POE_MY_DOC_BTN_ID: {
			CString folder = BrowseForFolder(hWnd, L"Select Folder", L"C:\\");
			SetWindowText(this->m_hvndPathMyDocEdit, folder);
			this->cnf->setKey(_T("POE_DOC"), folder);

			break;
		}
		case App::CTRLS_ID::PATH_AHK_BTN: {
			CString file = BrowseForFolder(hWnd, L"Select folder", L"C:\\");
			SetWindowText(this->m_hwndPathAhkEdit, file);
			this->cnf->setKey(_T("AHK"), file);

			break;
		}
		case App::CTRLS_ID::PATH_POE_TRADE_BTN: {
			CString file = BrowseForFile(hWnd, L"Select file");
			SetWindowText(this->m_hvndPoeTradeEdit, file);

			this->cnf->setKey(_T("POE_TRADE"), file);

			break;
		}
		case App::CTRLS_ID::PATH_AWAKE_TRADE_BTN: {
			CString file = BrowseForFile(hWnd, L"Select file");
			SetWindowText(this->m_hvndAwakePoeTradeEdit, file);

			this->cnf->setKey(_T("AWAKENED_POE_TRADE"), file);

			break;
		}
		case App::CTRLS_ID::PATH_POB_BTN_ID: {
			CString file = BrowseForFile(hWnd, L"Select file");
			SetWindowText(this->m_hvndPathPOBEdit, file);

			this->cnf->setKey(_T("POB"), file);

			break;
		}
		case App::CTRLS_ID::CLEAR_CACHE_INTERVAL_ID: {
			if (actionCode == EN_CHANGE) {
				CString clearCacheIntervalCStr;
				TCHAR clearCacheIntervalStr[1024];
				GetWindowText(this->m_hvndClearCacheInterval, clearCacheIntervalStr, sizeof(clearCacheIntervalStr));
				clearCacheIntervalCStr = clearCacheIntervalStr;
				if (!clearCacheIntervalCStr.IsEmpty()) {
					this->cnf->setKey(_T("ClearCacheInterval"), clearCacheIntervalCStr);
				} else {
					this->cnf->setKey(_T("ClearCacheInterval"), this->DefaultClearCacheInterval);
				}
				this->cacheCleaner->setClearCacheInterval(this->cnf->getKey(_T("ClearCacheInterval")));
			}
			break;
		}
		default: {
			break;
		}
			
	}
	return 0;
}

