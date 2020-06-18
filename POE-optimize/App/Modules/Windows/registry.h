#include <iostream>
#include <Windows.h>
#include <string>
#include <exception>

LONG GetStringRegKey(HKEY hKey, const std::wstring& strValueName, std::wstring& strValue, const std::wstring& strDefaultValue);

// L"SOFTWARE\\GrindingGearGames\\Path of Exile" poe HKEY_CURRENT_USER
// \\SOFTWARE\AutoHotkey HKEY_LOCAL_MACHINE 
std::string getRegistryKey(HKEY section, LPCWSTR Key, LPCWSTR Value);
