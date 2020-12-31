#pragma once
#include "sqlite3/sqlite3.h"
#include "defines/DataBaseInterface.h"
#include <string>

class Sqlite3Adaptor : public DataBaseInterface
{
public:
    Sqlite3Adaptor();
    ~Sqlite3Adaptor();
    void Init(std::string dbPath) override;
    void UnInit() override;
    void Sqlite3Open() override;
    bool GetLastRunTime(std::string& strTime) override;
    void SetLastRunTime(const std::string& strTime) override;
public:
    void Sqlite3Text();
private:
    void Sqlite3Exec(const std::string& sqlStr);
    bool Sqlite3Query(const std::string& sqlStr, std::string& value);

private:
    // 使用前置声明
    struct Impl;
    std::unique_ptr<Impl> m_impl = nullptr;
};
