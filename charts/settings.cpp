#include "settings.h"
#include "ioc.h"
#include <QMap>

Settings::Settings() {
    gContainer.RegisterFactory<IDataReader, NullReader>();
}

std::shared_ptr<IDataReader> Settings::getObject() {
    return gContainer.GetObject<IDataReader>();
}

void Settings::changeFileType(QFileInfo fileInfo, int maxSize) {
    if (fileInfo.size() > maxSize) {
        emit changeChartData(QMap<QString, QVariant>());
        emit changePlaceholder("Файл слишком большой");
        gContainer.RegisterFactory<IDataReader, NullReader>();
        return;
    }

    QString suffix = fileInfo.suffix();
    if (suffix == "sqlite") {
        gContainer.RegisterFactory<IDataReader, SQLiteDataReader>();
    } else if (suffix == "json") {
        gContainer.RegisterFactory<IDataReader, JsonDataReader>();
    } else {
        gContainer.RegisterFactory<IDataReader, NullReader>();
    }
}
