#include <Windows.h>
#include <iostream>
#include "shlobj.h"
#include <atlstr.h>

INT CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lp, LPARAM pData)
{
	if (uMsg == BFFM_INITIALIZED) SendMessage(hwnd, BFFM_SETSELECTION, TRUE, pData);
	return 0;
}

CString BrowseForFolder(HWND hwnd, CString title, CString folder)
{
	CString ret;

	BROWSEINFO br;
	ZeroMemory(&br, sizeof(BROWSEINFO));
	br.lpfn = BrowseCallbackProc;
	br.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	br.hwndOwner = hwnd;
	br.lpszTitle = title;
	br.lParam = (LPARAM)folder.GetString();
	//br.ulFlags = BIF_BROWSEINCLUDEFILES;
	LPITEMIDLIST pidl = NULL;
	if ((pidl = SHBrowseForFolder(&br)) != NULL)
	{
		wchar_t buffer[MAX_PATH];
		if (SHGetPathFromIDList(pidl, buffer)) ret = buffer;

	}

	return ret;
}

CString BrowseForFile(HWND hwnd, CString title)
{
	CString ret;

	OPENFILENAME ofn;
	LPWSTR ls{};
	char str[MAX_PATH];
	str[0] = 0;
	::memset(&ofn, 0, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrTitle = title;
	ofn.nFilterIndex = 2;
	ofn.lpstrFile = (LPWSTR) str;
	ofn.hwndOwner = hwnd;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (::GetOpenFileName(&ofn) != FALSE)
	{
		ret = ofn.lpstrFile;
	}

	return ret;
}


// Пример
// CString folder = BrowseForFolder(hWnd, L"Select Folder", L"C:\\");