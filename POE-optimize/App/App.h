#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <iostream>
#include "Modules/Files/Config.h"
#include "Modules/Windows/registry.h"

class App {

	enum class CTRLS_ID {
		PLAY_BTN_ID,
		PATH_AHK_ID,
		PATH_AHK_BTN,
		PATH_POE_MY_DOC_ID,
		PATH_POE_MY_DOC_BTN_ID,
		PATH_POE_ID,
		PATH_POE_BTN_ID,
		PATH_POE_TRADE_ID,
		PATH_POE_TRADE_BTN,
		CLEAR_CACHE_INTERVAL_ID
	};

	enum class LABELS_ID {
		INTERVAL_LABEL_ID
	};

public:
	explicit App();
	~App();
	int Run();
private:
	void InitWindow();
	void InitControls();
	void ConfToControls();
	void RegistryInConf();
	void clearCache();

	static LRESULT CALLBACK AppProcess(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WINProcess(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK AppCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
private:
	const std::wstring AppName = { L"POE Optimize" }, className{ L"POE Optimize" };
	HWND m_hwnd{}, m_hwndButton, 
		m_hwndPathAhkEdit, m_hvndPathAhkBtn,
		m_hvndPathMyDocEdit, m_hvndPathMyDocEditBtn,
		m_hvndPoeTradeEdit, m_hvndPoeTradeBtn,
		m_hvndPathOfExilePath, m_hvndPathOfExileBtn,
		m_hvndClearCacheInterval;
	HWND m_hvndIntervalLabel;
	const int AppWidth{ 400 }, AppHeight{ 600 };
	NOTIFYICONDATA nf{};
	Config* cnf;

	CString AhkFileName = L"AutoHotkey.exe";
	CString PoeFileName = L"PathOfExile.exe";
	CString DefaultClearCacheInterval = "3";
};
