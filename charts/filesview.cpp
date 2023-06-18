#include "filesview.h"
#include <QStatusBar>
#include <QSplitter>
#include <QHeaderView>
#include <QHBoxLayout>

FilesView::FilesView(QWidget *parent) : QWidget(parent) {

    QHBoxLayout* hLayout = new QHBoxLayout(this);
    QString homePath = QDir::currentPath() + "/trpo_lab3/data";

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

    hLayout->addWidget(tableView);

    selectionModel = tableView->selectionModel();

    //Пример организации установки курсора в TreeView относительно модельного индекса
    QItemSelection toggleSelection;
    //Объявили модельный индекс topLeft
    QModelIndex topLeft;
    //Получили индекс из модели
    topLeft = model->index(homePath);
    toggleSelection.select(topLeft, topLeft);
    selectionModel->select(toggleSelection, QItemSelectionModel::Toggle);
}

void FilesView::onSelectionChange(QString folderPath) {

    QString filePath = folderPath;

    tableView->setRootIndex(model->setRootPath(filePath));
}
