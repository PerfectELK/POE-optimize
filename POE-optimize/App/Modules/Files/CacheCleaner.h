#include <iostream>
#include <map>
#include <atlstr.h>
#include <string>
#include <cstring>
#include <thread>
#include <chrono>
#include <vector>
#include "../../Lib/FolderFunc.h"

#ifndef CACHE_CLEANER_H
#define CACHE_CLEANER_H

using namespace std;

class CacheCleaner {
public:
	static CacheCleaner* getInstance();
	void setClearCacheInterval(CString interval);
	void setClearCacheDirs(vector<CString> dirs);
	void setUpClearCacheThread();

private:
	CacheCleaner();
	void clearCache();

private:
	static CacheCleaner* instance;
	int clearCacheInterval;
	vector<CString> dirs;
};

#endif