#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <iostream>

class App {

	enum class CTRLS_ID {
		PLAY_BTN_ID,
		PATH_AHK_ID,
		PATH_MY_DOC_ID
	};

public:
	explicit App();
	~App();
	int Run();
private:
	void InitWindow();
	void InitControls();

	static LRESULT CALLBACK AppProcess(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WINProcess(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK AppCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
private:
	const std::wstring AppName = { L"POE-no_freeze" }, className{ L"POE-no_freeze" };
	HWND m_hwnd{}, m_hwndButton, m_hwndPathAhkEdit, m_hvndPathMyDocEdit;
	const int AppWidth{ 400 }, AppHeight{ 600 };
};