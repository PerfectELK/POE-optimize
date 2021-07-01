#include <iostream>
#include <Windows.h>
#include <string>
#include <atlstr.h>


LONG GetStringRegKey(HKEY hKey, const std::wstring& strValueName, std::wstring& strValue, const std::wstring& strDefaultValue);

// L"SOFTWARE\\GrindingGearGames\\Path of Exile" poe HKEY_CURRENT_USER
// \\SOFTWARE\AutoHotkey HKEY_LOCAL_MACHINE 
CString getRegistryKey(HKEY section, LPCWSTR Key, LPCWSTR Value);
