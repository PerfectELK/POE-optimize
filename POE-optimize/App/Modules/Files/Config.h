#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <atlstr.h>
#include <string>
#include <cstring>

#ifndef CONFIG_CONFIG_H
#define CONFIG_CONFIG_H

using namespace std;

class Config {
private:

    Config();
    void writeFile();
    void writeConfig();
    void getFile();
    void makeMap();

public:

    CString getKey(CString key);
    void setKey(CString key, CString value);
    static Config* getInstance();

private:
    static Config* instance;
    map <CString, CString> conf;
    const CString filename = "config.conf";
    CString fileStr;
};

vector<CString> split(const CString& str, const CString& delim);

string AnsiToStrC(CString ansi);

#endif







