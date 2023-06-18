#include "app.h"
#include <QFileDialog>
#include <QHBoxLayout>
#include <QMap>
#include <QVariant>
#include <QSplitter>

App::App(QWidget *parent) {
    Q_UNUSED(parent);
    setWindowTitle("Charts");
    this->setGeometry(0, 0, 1500, 800);

    filesView = new FilesView(this);
    topButtons = new TopButtons(this);
    chartsView = new ChartsView(this);
    settings = new Settings();
    maxSize = 1048576;

    QVBoxLayout *vLayout = new QVBoxLayout(this);

    QSplitter *splitter = new QSplitter(this);

    filesView->setMaximumWidth(500);
    topButtons->setMaximumHeight(50);
    chartsView->setMinimumSize(200, 200);

    splitter->addWidget(filesView);
    splitter->addWidget(chartsView);

    vLayout->addWidget(topButtons);
    vLayout->addWidget(splitter);

    connect(this, &App::onFolderChange, filesView, &FilesView::onSelectionChange);
    connect(this, &App::updateChart, chartsView, &ChartsView::updateChart);
    connect(this, &App::updateChartData, chartsView, &ChartsView::setData);
//    connect(this, &App::showPlaceholder, chartsView, &ChartsView::updatePlaceholder);
    connect(this, &App::updateChartType, chartsView, &ChartsView::setChartType);
    connect(this, &App::updateFileType, settings, &Settings::changeFileType);
    connect(settings, &Settings::changeChartData, chartsView, &ChartsView::setData);
    connect(settings, &Settings::changePlaceholder, chartsView, &ChartsView::updatePlaceholder);
    connect(filesView->selectionModel, &QItemSelectionModel::currentChanged, this, &App::currentFileChanged);
    connect(topButtons->chooseFolder, &QPushButton::clicked, this, &App::chooseFolder);
    connect(topButtons->isBlackAndWhite, &QCheckBox::stateChanged, chartsView, &ChartsView::changeColorPalette);
    connect(topButtons->chartType, &QComboBox::currentTextChanged, this, &App::typeChanged);
    connect(topButtons->printToPDF, &QPushButton::clicked, chartsView, &ChartsView::printToPDF);
}

void App::chooseFolder() {
    QString folderPath = QFileDialog::getExistingDirectory(this, tr("Open Folder"), QDir::homePath(), QFileDialog::ShowDirsOnly);
    if (folderPath != "") {
        emit onFolderChange(folderPath);
    }
}

void App::currentFileChanged(QModelIndex index) {
    QFileSystemModel *fileModel = new QFileSystemModel(this);

    emit updateFileType(fileModel->fileInfo(index), maxSize);

    QVariant data = settings->getObject()->getData(fileModel->fileInfo(index));
    QMap<QString, QVariant> temp = data.toMap();

    if (temp.size() > 0) {
        emit updateChartData(temp);
    }

    delete fileModel;
}

void App::typeChanged(QString type) {
    if (type == "Bar Chart") {
        emit updateChartType(new BarChart());
    } else if (type == "Pie Chart") {
        emit updateChartType(new PieChart());
    }
}
