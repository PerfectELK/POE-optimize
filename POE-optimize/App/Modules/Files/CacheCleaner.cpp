#include "CacheCleaner.h"

CacheCleaner* CacheCleaner::instance = nullptr;

CacheCleaner::CacheCleaner(){}

CacheCleaner* CacheCleaner::getInstance() 
{
    if (instance == nullptr) {
        instance = new CacheCleaner();
    }
    return instance;
}

void CacheCleaner::addFolder()
{
}

void CacheCleaner::setClearCacheInterval(CString interval)
{
    this->clearCacheInterval = _ttoi(interval);
}

void CacheCleaner::setClearCacheDirs(vector<CString> dirs)
{
    this->dirs = dirs;
}

void CacheCleaner::setUpClearCacheThread()
{
     thread t(&CacheCleaner::clearCache, this);
     t.detach();
}

void CacheCleaner::clearCache()
{
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(this->clearCacheInterval * 60 * 1000));
        for (int i = 0; i < this->dirs.size(); i++) {
            removeallfromdir(AnsiToStr(this->dirs[i]));
        }
    }
}