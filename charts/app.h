#ifndef APP_H
#define APP_H
#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include "filesview.h"
#include "topbuttons.h"
#include "chartsview.h"

class App : public QWidget {
    Q_OBJECT
public:
    App(QWidget* parent = 0);

public slots:
    void chooseFolder();
    void currentFileChanged(QModelIndex index);
    void typeChanged(QString type);

signals:
    void onFolderChange(QString path);
    void updateChart();
    void showPlaceholder(QString str);
    void updateChartData(const QMap<QString, QVariant>& newData);
    void updateChartType(Chart *type);

private:
    TopButtons *topButtons;
    FilesView *filesView;
    ChartsView *chartsView;
};

#endif // APP_H
