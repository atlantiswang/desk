#pragma once
#include <string>

class DataBaseInterface
{
public:
    DataBaseInterface() {};
    virtual ~DataBaseInterface() {};
    virtual void Init(std::string dbPath) = 0;
    virtual void UnInit() = 0;
    virtual void Sqlite3Open() = 0;
    virtual bool GetLastRunTime(std::string& strTime) = 0;
    virtual void SetLastRunTime(const std::string& strTime) = 0;
};
