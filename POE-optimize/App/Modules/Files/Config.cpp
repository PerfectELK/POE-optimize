#include "Config.h"

Config* Config::instance = nullptr;


Config::Config() {
    this->getFile();
    this->makeMap();
}

Config* Config::getInstance() {
    if (instance == nullptr) {
        instance = new Config();
    }
    return instance;
}

void Config::getFile() {
    ifstream f;
    f.open(this->filename);
    if (!f.is_open()) {
        ofstream file(this->filename);
        file.close();
        return;
    }
    stringstream ss;
    ss << f.rdbuf();
    string s = ss.str();
    this->fileStr = s.c_str();
    f.close();
}

void Config::writeConfig() {
    this->fileStr = "";
    for (auto& item : this->conf) {
        if (item.second.IsEmpty()) continue;
        this->fileStr += item.first + _T("==") + item.second + _T("\n");
    }
    this->writeFile();
}

void Config::writeFile() {
    ofstream file(this->filename);
    string s = AnsiToStrC(this->fileStr);
    file << s;
    file.close();
}

void Config::makeMap() {
    vector<CString> lines = split(this->fileStr, "\n");
    if (lines.empty()) {
        return;
    }
    for (int i = 0; i < lines.size(); i++) {
        vector<CString> line = split(lines[i], "==");
        if (line.size() != 2) {
            return;
        }
        this->conf[line[0]] = line[1];
    }
}

CString Config::getKey(CString key) {
    return this->conf[key];
}

void Config::setKey(CString key, CString value) {
   
    if (key.IsEmpty() || value.IsEmpty()) {
        return;
    }
    this->conf[key] = value;
    this->writeConfig();
}

vector<CString> split(const CString& str, const CString& delim)
{

    int nTokenPos = 0;
    CString strToken = str.Tokenize(delim, nTokenPos);
    vector<CString> s;
    while (!strToken.IsEmpty())
    {
        s.push_back(strToken);
        strToken = str.Tokenize(delim, nTokenPos);

    }
    return s;
}

string AnsiToStrC(CString ansi)
{
    CT2CA ConvertedAnsiString(ansi);
    string s(ConvertedAnsiString);
    return s;
}
