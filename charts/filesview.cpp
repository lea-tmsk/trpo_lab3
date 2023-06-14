#include "filesview.h"
#include <QStatusBar>
#include <QSplitter>
#include <QHeaderView>
#include <QHBoxLayout>

FilesView::FilesView(QWidget *parent) : QWidget(parent) {

    //this->setGeometry(100, 100, 1000, 700);
    QHBoxLayout* hLayout = new QHBoxLayout(this);
//    int width = parent->width();
//    QRect size(100, 100, width, 500);
//    hLayout->setGeometry(size);

//    this->setStatusBar(new QStatusBar(this));
//    this->statusBar()->showMessage("Выбранный путь : ");
    QString homePath = QDir::homePath();

    model = new QFileSystemModel(this);
    model->setFilter(QDir::NoDotAndDotDot | QDir::Files);

    //фильтры для sqlite и json файлов
    QStringList filters;
    filters << "*.sqlite";
    filters << "*.json";
    model->setNameFilters(filters);
    model->setNameFilterDisables(false);

    model->setRootPath(homePath);
    //Показатьв виде "дерева". Пользуемся готовым видом(TreeView):
    treeView = new QTreeView();
    // Устанавливаем модель данных для отображения
    treeView->setModel(leftPartModel);
    //Раскрываем все папки первого уровня
    treeView->expandAll();

    tableView = new QTableView;
    tableView->setModel(model);

    hLayout->addWidget(tableView);
    /*
     * QItemSelectionModel *selectionModel отслеживает выбранные элементы в представлении treeView,
     * также отслеживает текущий выбранный элемент в представлении treeView.
    */
    selectionModel = tableView->selectionModel();
    treeView->header()->resizeSection(0, 500);

    //Выполняем соединения слота и сигнала который вызывается когда осуществляется выбор элемента в TreeView

    //Пример организации установки курсора в TreeView относительно модельного индекса
    QItemSelection toggleSelection;
    //Объявили модельный индекс topLeft
    QModelIndex topLeft;
    //Получили индекс из модели
    topLeft = leftPartModel->index(homePath);
    toggleSelection.select(topLeft, topLeft);
    selectionModel->select(toggleSelection, QItemSelectionModel::Toggle);
}

void FilesView::onSelectionChange(QString folderPath) {

    QModelIndex index = treeView->selectionModel()->currentIndex();

    QString filePath = folderPath;

    tableView->setRootIndex(model->setRootPath(filePath));
}
