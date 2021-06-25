#include "CacheCleaner.h"

CacheCleaner* CacheCleaner::instance = nullptr;

CacheCleaner* CacheCleaner::getInstance() {
    if (instance == nullptr) {
        instance = new CacheCleaner();
    }
    return instance;
}