#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(100, 100, 1500, 800);

//    QHBoxLayout* hLayout = new QHBoxLayout(this);

    filesView = new FilesView(this);
    topButtons = new TopButtons(this);

    QSplitter *splitter = new QSplitter(this);
//    tableView = new QTableView;
//    tableView->setModel(rightPartModel);
    splitter->addWidget(filesView);
    splitter->addWidget(topButtons);
    setCentralWidget(splitter);

//    hLayout->addWidget(filesView);
//    hLayout->addWidget(topButtons);

}

MainWindow::~MainWindow()
{
    delete ui;
}

