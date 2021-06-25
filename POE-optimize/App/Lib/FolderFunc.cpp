#include "FolderFunc.h"

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

	OPENFILENAME l = { sizeof(l), };
	TCHAR buf[1024];
	l.hwndOwner = hwnd;
	l.lpstrFilter = NULL;
	l.lpstrFile = buf;
	l.nMaxFile = 1023;
	l.lpstrTitle = _T("Open File");
	l.lpstrDefExt = _T("zip");
	l.lpstrInitialDir = NULL;
	l.Flags = OFN_HIDEREADONLY | OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
	buf[0] = 0;

	if (::GetOpenFileName(&l) != FALSE)
	{
		ret = l.lpstrFile;
	}

	return ret;
}

string AnsiToStr(CString ansi) {
	CT2CA ConvertedAnsiString(ansi);
	string s(ConvertedAnsiString);
	return s;
}

CString StrToAnsi(string str) {
	CString cs(str.c_str());
	return cs;
}

string ConvertWideCharToUtf8(const wchar_t* wideText)
{
	int len = WideCharToMultiByte(CP_UTF8, 0, wideText, -1, NULL, 0, NULL, NULL);
	char* buffer = (char*)malloc(len);
	WideCharToMultiByte(CP_UTF8, 0, wideText, -1, buffer, len, NULL, NULL);
	string s = buffer;
	free(buffer);

	return s;
}

void removeallfromdir(string path) {
	for (const auto& entry : filesystem::directory_iterator(path)) {
		filesystem::remove_all(entry.path());
	}
}