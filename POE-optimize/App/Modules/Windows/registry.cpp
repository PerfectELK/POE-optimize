#include "registry.h"

LONG GetStringRegKey(HKEY hKey, const std::wstring& strValueName, std::wstring& strValue, const std::wstring& strDefaultValue)
{
    strValue = strDefaultValue;
    WCHAR szBuffer[1024];
    DWORD dwBufferSize = sizeof(szBuffer);
    ULONG nError;
    nError = RegQueryValueEx(hKey, strValueName.c_str(), 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);
    if (ERROR_SUCCESS == nError)
    {
        strValue = szBuffer;
    }
    return nError;
}

CString getRegistryKey(HKEY section, LPCWSTR Key, LPCWSTR Value)
{
    HKEY hKey;
    bool k = RegOpenKeyEx(section, Key, 0, KEY_WOW64_64KEY | KEY_QUERY_VALUE, &hKey);
    std::wstring str;
    GetStringRegKey(hKey, Value, str, L"bad");
    return str.c_str();
}

