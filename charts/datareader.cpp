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

QVariant JsonDataReader::getData(const QString fileName) {
    QFile file(fileName);
    QString jsonString;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        jsonString = file.readAll();
        file.close();
    } else {
        qDebug()<< "Error: file not found.";
        return QVariant::fromValue(nullptr);
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

    return QVariant::fromValue(keyValue);
}

QVariant SQLiteDataReader::getData(const QString fileName) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(fileName);

    if (!m_db.open()) {
        qDebug() << "Error: can't open database";
    } else {

        QStringList* tables = new QStringList;
        *tables = m_db.tables();

        QMap<QString, QVariant> keyValue;

        for (auto i = 0; i < tables->size(); i++) {
            QSqlQuery query;
            int idTime = query.record().indexOf("Time");
            int idValue = query.record().indexOf("Value");
            query.prepare("SELECT * FROM (:name)");
            query.bindValue(":name", tables[i]);

            if (query.exec())
            {
               while (query.next())
               {
                   keyValue[query.value(idTime).toString()] = query.value(idValue);
               }
            }
        }
        return QVariant::fromValue(keyValue);
    }
    return QVariant::fromValue(nullptr);
}
