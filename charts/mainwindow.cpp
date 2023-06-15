#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


//    QHBoxLayout* hLayout = new QHBoxLayout(this);

//    filesView = new FilesView(this);
//    topButtons = new TopButtons(this);

    //QVBoxLayout *hLayout = new QVBoxLayout(this);

//    hLayout->addWidget(new TopButtons(this));
//    hLayout->addWidget(topButtons);
    //hLayout->addWidget(filesView);
    //hLayout->addStretch();

//    QSplitter *splitter = new QSplitter(this);
//    tableView = new QTableView;
//    tableView->setModel(rightPartModel);
    //splitter->addWidget(filesView);
    //splitter->addWidget(topButtons);
    //setCentralWidget(splitter);

//    hLayout->addWidget(filesView);
//    hLayout->addWidget(topButtons);

}

MainWindow::~MainWindow()
{
    delete ui;
}

