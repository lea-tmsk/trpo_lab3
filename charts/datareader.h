#ifndef DATAREADER_H
#define DATAREADER_H
#include <QString>
#include <QVariant>
#include <QSqlDatabase>

class IDataReader {
public:
    virtual ~IDataReader() {};
    virtual QVariant getData(const QString fileName) = 0;
};

class JsonDataReader : public IDataReader {
public:
    JsonDataReader() {};
    QVariant getData(const QString fileName);;
};

class SQLiteDataReader : public IDataReader {
public:
    SQLiteDataReader() {};
    QVariant getData(const QString fileName);

private:
    QSqlDatabase m_db;
};

#endif // DATAREADER_H
