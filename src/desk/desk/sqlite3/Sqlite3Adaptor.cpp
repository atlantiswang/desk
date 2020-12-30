#include "Sqlite3Adaptor.h"
#include <assert.h>

struct Sqlite3Adaptor::Impl
{
    Impl();
    ~Impl();
     std::string m_dbPath;
     sqlite3* m_pSql = nullptr;
};

Sqlite3Adaptor::Impl::Impl()
{
}

Sqlite3Adaptor::Impl::~Impl()
{
}

Sqlite3Adaptor::Sqlite3Adaptor():
    m_impl(new Impl)
{
}

Sqlite3Adaptor::~Sqlite3Adaptor()
{
}

void Sqlite3Adaptor::Init(std::string dbPath)
{
    m_impl->m_dbPath = dbPath;
}

void Sqlite3Adaptor::UnInit()
{
    if (m_impl->m_pSql)
    {
        sqlite3_close_v2(m_impl->m_pSql);
        m_impl->m_pSql = nullptr;
    }
}

void Sqlite3Adaptor::Sqlite3Open()
{
    int result = sqlite3_open_v2(m_impl->m_dbPath.c_str(),
        &m_impl->m_pSql,
        SQLITE_OPEN_READWRITE |
        SQLITE_OPEN_CREATE |
        SQLITE_OPEN_NOMUTEX |
        SQLITE_OPEN_SHAREDCACHE,
        NULL);

    assert(result == SQLITE_OK);
}

bool Sqlite3Adaptor::GetLastRunTime(std::string& strTime)
{
    std::string sqlStr;
    sqlStr = "SELECT value FROM tbConfigure WHERE key = 'loginTime'";
    return Sqlite3Query(sqlStr, strTime);
}

void Sqlite3Adaptor::SetLastRunTime(const std::string& strTime)
{
    char buff[128] = { 0 };
    std::string strLastTime;
    if (!GetLastRunTime(strLastTime))
    {
        std::string strFormat = "INSERT INTO tbConfigure (key, value) VALUES ('loginTime','%s')";
        sprintf_s(buff, sizeof(buff), strFormat.c_str(), strTime.c_str());
    }
    else
    {
        std::string strFormat = "UPDATE tbConfigure SET value = '%s' WHERE key = 'loginTime'";
        sprintf_s(buff, sizeof(buff), strFormat.c_str(), strTime.c_str());
    }
    Sqlite3Exec(buff);
}

void Sqlite3Adaptor::Sqlite3Text()
{
}

void Sqlite3Adaptor::Sqlite3Exec(const std::string& sqlStr)
{
    sqlite3_stmt *stmt = nullptr;
    char* pErrmsg = nullptr;
    int nResult = sqlite3_exec(m_impl->m_pSql, sqlStr.c_str(), nullptr, nullptr, &pErrmsg);
    if (nResult == SQLITE_OK)
    {
        // Ö´ÐÐ³É¹¦
    }
    sqlite3_finalize(stmt);
}

bool Sqlite3Adaptor::Sqlite3Query(const std::string& sqlStr, std::string& value)
{
    sqlite3_stmt *stmt = nullptr;
    const unsigned char* pValue= nullptr;
    int nResult = sqlite3_prepare_v2(m_impl->m_pSql, sqlStr.c_str(), -1, &stmt, nullptr);
    if (nResult == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            pValue = sqlite3_column_text(stmt, 0);
            value = (char*)pValue;
        }
        sqlite3_finalize(stmt);
        return value.empty() ? false : true;
    }
    else
    {
        sqlite3_finalize(stmt);
        return false;
    }
}
