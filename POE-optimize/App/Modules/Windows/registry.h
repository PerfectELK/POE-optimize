#include <iostream>
#include <Windows.h>


LONG GetStringRegKey(HKEY hKey, const std::wstring& strValueName, std::wstring& strValue, const std::wstring& strDefaultValue)
{
    strValue = strDefaultValue;
    WCHAR szBuffer[512];
    DWORD dwBufferSize = sizeof(szBuffer);
    ULONG nError;
    nError = RegQueryValueExW(hKey, strValueName.c_str(), 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);
    if (ERROR_SUCCESS == nError)
    {
        strValue = szBuffer;
    }
    return nError;
}
// L"SOFTWARE\\GrindingGearGames\\Path of Exile"
std::string getInstallLocation(LPCWSTR Key)
{
    HKEY hKey;
    RegOpenKeyExW(HKEY_CURRENT_USER, Key , 0, KEY_READ, &hKey);

    std::wstring str;
    GetStringRegKey(hKey, L"InstallLocation", str, L"bad");

    const std::string s(str.begin(), str.end());

    return s;

}
