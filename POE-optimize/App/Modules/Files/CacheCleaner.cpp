#include "CacheCleaner.h"

CacheCleaner* CacheCleaner::instance = nullptr;

CacheCleaner::CacheCleaner()
{

}

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

void CacheCleaner::setUpClearCacheThread()
{
     thread t(&CacheCleaner::clearCache, this);
     t.detach();
}

void CacheCleaner::clearCache()
{
    while (true) {
        wchar_t buffer[256];
        _itow(this->clearCacheInterval, buffer, 10);
        OutputDebugString(buffer);
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}