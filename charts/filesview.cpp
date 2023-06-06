#include "filesview.h"
#include <QStatusBar>
#include <QSplitter>
#include <QHeaderView>
#include <QHBoxLayout>

FilesView::FilesView(QWidget *parent) : QWidget(parent) {

    //this->setGeometry(100, 100, 1000, 700);
    QHBoxLayout* hLayout = new QHBoxLayout(this);

//    this->setStatusBar(new QStatusBar(this));
//    this->statusBar()->showMessage("Выбранный путь : ");
    QString homePath = QDir::homePath();
    // Определим  файловой системы:
    leftPartModel =  new QFileSystemModel(this);
    leftPartModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    leftPartModel->setRootPath(homePath);

    rightPartModel = new QFileSystemModel(this);
    rightPartModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);

    rightPartModel->setRootPath(homePath);
    //Показатьв виде "дерева". Пользуемся готовым видом(TreeView):
    treeView = new QTreeView();
    // Устанавливаем модель данных для отображения
    treeView->setModel(leftPartModel);
    //Раскрываем все папки первого уровня
    treeView->expandAll();
    // Создаем объект "сплиттер(разделитель)"
    QSplitter *splitter = new QSplitter(parent);
    tableView = new QTableView;
    tableView->setModel(rightPartModel);
    splitter->addWidget(treeView);
    splitter->addWidget(tableView);
    hLayout->addWidget(splitter);
//    setCentralWidget(splitter);
    /*
     * QItemSelectionModel *selectionModel отслеживает выбранные элементы в представлении treeView,
     * также отслеживает текущий выбранный элемент в представлении treeView.
    */
    QItemSelectionModel *selectionModel = treeView->selectionModel();
    treeView->header()->resizeSection(0, 200);

    //Выполняем соединения слота и сигнала который вызывается когда осуществляется выбор элемента в TreeView

    /*connect(selectionModel, SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this, SLOT(on_selectionChangedSlot(const QItemSelection &, const QItemSelection &)));*/

    connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &FilesView::onSelectionChange);

    //Пример организации установки курсора в TreeView относительно модельного индекса
    QItemSelection toggleSelection;
    //Объявили модельный индекс topLeft
    QModelIndex topLeft;
    //Получили индекс из модели
    topLeft = leftPartModel->index(homePath);
    toggleSelection.select(topLeft, topLeft);
    selectionModel->select(toggleSelection, QItemSelectionModel::Toggle);
}

void FilesView::onSelectionChange(const QItemSelection &selected) {

    QModelIndex index = treeView->selectionModel()->currentIndex();

    QModelIndexList indexs =  selected.indexes();

    QString filePath = "";

    // Размещаем информацию в statusbar относительно выделенного модельного индекса
    /*
     * Смотрим, сколько индексов было выделено.
     * В нашем случае выделяем только один, следовательно всегда берем только первый.
    */
    if (indexs.count() >= 1) {
        QModelIndex ix =  indexs.constFirst();
        filePath = leftPartModel->filePath(ix);
        //this->statusBar()->showMessage("Выбранный путь : " + leftPartModel->filePath(indexs.constFirst()));
    }

    /*
     * Получив выбранные данные из левой части filePath(путь к папке/файлу).
     * Для представления в правой части устанваливаем корневой индекс относительно filePath.
     * Табличное представление отображает только файлы, находящиеся в filePath(папки не отображает)
     */
    tableView->setRootIndex(rightPartModel->setRootPath(filePath));
}
