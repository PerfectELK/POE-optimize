#include "App.h"
#include "Modules/Windows/tray.h"

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
	
	this->m_hwndButton = CreateWindowEx(
		0,
		L"BUTTON",
		L"Играть",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		this->AppWidth - 90, 
		this->AppHeight - 60,
		70,
		20,
		this->m_hwnd,
		(HMENU) App::CTRLS_ID::PLAY_BTN_ID,
		nullptr,
		nullptr
	);

	if (!this->m_hwndButton) {
		throw runtime_error("Error, can't create button!");
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
			}
			if (param == SC_CLOSE) {
				PostQuitMessage(EXIT_SUCCESS);
			}
			break;
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

			return 0;
		}
		default: {

			break;
		}
			
	}
	return 0;
}

