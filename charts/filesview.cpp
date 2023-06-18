#include "filesview.h"
#include <QStatusBar>
#include <QSplitter>
#include <QHeaderView>
#include <QVBoxLayout>

FilesView::FilesView(QWidget *parent) : QWidget(parent) {

    QVBoxLayout* vLayout = new QVBoxLayout(this);
    QString homePath =  QDir::homePath();
    path = new QLabel("Current path: " + homePath, this);

    model = new QFileSystemModel(this);
    model->setFilter(QDir::NoDotAndDotDot | QDir::Files);

    //фильтры для sqlite и json файлов
    QStringList filters;
    filters << "*.sqlite";
    filters << "*.json";
    model->setNameFilters(filters);
    model->setNameFilterDisables(false);

    model->setRootPath(homePath);

    tableView = new QTableView;
    tableView->setModel(model);

    vLayout->addWidget(tableView);
    vLayout->addWidget(path);

    selectionModel = tableView->selectionModel();

    tableView->setRootIndex(model->setRootPath(homePath));

    //Пример организации установки курсора в TreeView относительно модельного индекса
//    QItemSelection toggleSelection;
    //Объявили модельный индекс topLeft
//    QModelIndex topLeft;
    //Получили индекс из модели
//    topLeft = model->index(homePath);
//    toggleSelection.select(topLeft, topLeft);
//    selectionModel->select(toggleSelection, QItemSelectionModel::Toggle);
}

void FilesView::onSelectionChange(QString folderPath) {

    QString filePath = folderPath;
    path->setText("Current path: " + folderPath);

    tableView->setRootIndex(model->setRootPath(filePath));
}
