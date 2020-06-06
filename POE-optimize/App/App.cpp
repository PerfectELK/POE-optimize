#include "App.h"
#include "Modules/Windows/tray.h"
#include "Lib/FolderFunc.h"

App::App()
{
	using std::string;
	using std::wstring;

	try {

		this->InitWindow();
		this->InitControls();

	}
	catch (const std::exception& e) {

		string ExceptData = e.what();

		MessageBox(nullptr, wstring(begin(ExceptData), end(ExceptData)).c_str(), L"Ошибка", MB_ICONERROR | MB_OK);
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

	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
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
	int BUTTON_WIDTH = 130;
	int EDIT_WIDTH = 200;

	int BUTTON_X = 210;
	int EDIT_X = 10;

	
	this->m_hwndButton = CreateWindowEx(
		0,
		L"BUTTON",
		L"Играть",
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

	}
	else {
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
	
	switch (uMsg) {
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
	switch (CTRL) {

		case App::CTRLS_ID::PLAY_BTN_ID: {

			break;
		}
		case App::CTRLS_ID::PATH_POE_BTN_ID: {
			//CString folder = BrowseForFolder(hWnd, L"Select Folder", L"C:\\");
			CString folder = BrowseForFile(hWnd, "Select \".exe\" file");
			SetWindowText(this->m_hvndPathOfExilePath, folder);
			break;
		}
		default: {

			break;
		}
			
	}
	return 0;
}

