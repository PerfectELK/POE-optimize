#include <Windows.h>
#include <iostream>
#include "shlobj.h"
#include <atlstr.h>
#include <filesystem>

#ifndef FOLDER_FUNC_H
#define FOLDER_FUNC_H
#define SUCCESS_STAT 0

using namespace std;

INT CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lp, LPARAM pData);

CString BrowseForFolder(HWND hwnd, CString title, CString folder);

CString BrowseForFile(HWND hwnd, CString title);

string AnsiToStr(CString ansi);

CString StrToAnsi(string str);

string ConvertWideCharToUtf8(const wchar_t* wideText);

void removeallfromdir(string path);

// Пример
// CString folder = BrowseForFolder(hWnd, L"Select Folder", L"C:\\");

#endif