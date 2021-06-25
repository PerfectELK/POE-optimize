#include <iostream>
#include <map>
#include <atlstr.h>
#include <string>
#include <cstring>
#include <thread>
#include <chrono>

#ifndef CACHE_CLEANER_H
#define CACHE_CLEANER_H

using namespace std;

class CacheCleaner {
public:
	static CacheCleaner* getInstance();
	void addFolder();
	void setClearCacheInterval(CString interval);
	void setUpClearCacheThread();
	void clearCache();
private:
	CacheCleaner();
	static CacheCleaner* instance;
	map <CString, CString> conf;
	int clearCacheInterval;
};

#endif