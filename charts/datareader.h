#ifndef DATAREADER_H
#define DATAREADER_H
#include <QString>
#include <QVariant>
#include <QSqlDatabase>
#include <QFileInfo>

class IDataReader {
public:
    virtual ~IDataReader() {};
    virtual QVariant getData(const QFileInfo fileInfo) = 0;
protected:
    QVariant m_data;

};

class JsonDataReader : public IDataReader {
public:
    JsonDataReader() {};
    QVariant getData(const QFileInfo fileInfo);
};

class SQLiteDataReader : public IDataReader {
public:
    SQLiteDataReader() {};
    QVariant getData(const QFileInfo fileInfo);

private:
    QSqlDatabase m_db;
};

#endif // DATAREADER_H
