#include "datareader.h"
#include <QDebug>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVector>
#include <QMap>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

QVariant JsonDataReader::getData(const QFileInfo fileInfo) {
    QFile file(fileInfo.filePath());
    QString jsonString;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        jsonString = file.readAll();
        file.close();
    } else {
        qDebug()<< "Error: file not found.";
        m_data = QVariant::fromValue(nullptr);
        return m_data;
    }

    auto jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());

    QJsonArray jArr = jsonDoc.array();
    QJsonValue val;

    QString key;
    QMap<QString, QVariant> keyValue;

    for (auto jsonObj : jArr) {
        val = jsonObj.toObject().value("Time");
        key = val.toString();

        val = jsonObj.toObject().value("Value");
        keyValue[key] = val;
    }

    m_data = QVariant::fromValue(keyValue);
    return m_data;
}

QVariant SQLiteDataReader::getData(const QFileInfo fileInfo) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(fileInfo.filePath());

    if (!m_db.open()) {
        qDebug() << "Error: can't open database";
    } else {

        QString table = fileInfo.baseName();

        QMap<QString, QVariant> keyValue;

        QSqlQuery query;
        query.prepare("SELECT * FROM " + table);

        if (query.exec()) {
           while (query.next()) {
               keyValue[query.value(0).toString()] = query.value(1);
           }
        }
        m_data = QVariant::fromValue(keyValue);
        return m_data;
    }

    m_data = QVariant::fromValue(nullptr);
    return m_data;
}

QVariant NullReader::getData(const QFileInfo fileInfo) {
    Q_UNUSED(fileInfo);
    return QVariant::fromValue(QMap<QString, QVariant>());
}
