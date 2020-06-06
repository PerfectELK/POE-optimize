#include <Windows.h>
#define SWM_TRAYMSG	WM_APP
#define TRAYICONID	1

void to_tray(HWND m_hWnd, NOTIFYICONDATA &nf) {
	nf.hWnd = m_hWnd;
	nf.uID = TRAYICONID;
	nf.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	HICON hIcon;
	hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	nf.hIcon = hIcon;
	nf.uCallbackMessage = SWM_TRAYMSG;
	Shell_NotifyIcon(NIM_ADD, &nf);
}

void from_tray (NOTIFYICONDATA &nf) {
	Shell_NotifyIcon(NIM_DELETE, &nf);
}