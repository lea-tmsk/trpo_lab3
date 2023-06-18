#ifndef SETTINGS_H
#define SETTINGS_H
#include <QObject>
#include <QFileInfo>
#include <memory>
#include "datareader.h"

class Settings : public QObject {
    Q_OBJECT
public:
    Settings();

    std::shared_ptr<IDataReader> getObject();
public slots:
    void changeFileType(QFileInfo fileInfo, int maxSize);

signals:
    void changePlaceholder(QString msg);
    void changeChartData(const QMap<QString, QVariant> &data);
};

#endif // SETTINGS_H
