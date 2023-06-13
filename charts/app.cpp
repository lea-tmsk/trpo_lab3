#include "app.h"
#include "datareader.h"
#include <QFileDialog>
#include <QHBoxLayout>
#include <QDebug>
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

    QVBoxLayout *vLayout = new QVBoxLayout(this);

    QSplitter *splitter = new QSplitter(this);

    filesView->setMaximumWidth(500);
    topButtons->setMaximumHeight(50);
    chartsView->setMinimumSize(200, 200);

    splitter->addWidget(filesView);
    splitter->addWidget(chartsView);

    vLayout->addWidget(topButtons);
    vLayout->addWidget(splitter);

    connect(topButtons->chooseFolder, &QPushButton::clicked, this, &App::chooseFolder);
    connect(this, &App::onFolderChange, filesView, &FilesView::onSelectionChange);
    connect(filesView->selectionModel, &QItemSelectionModel::currentChanged, this, &App::currentIndexChanged);
    connect(this, &App::updateChart, chartsView, &ChartsView::updateChart);
    connect(topButtons->chartType, &QComboBox::currentTextChanged, this, &App::typeChanged);
    connect(this, &App::updateChartData, chartsView, &ChartsView::setData);
    connect(this, &App::showPlaceholder, chartsView, &ChartsView::updatePlaceholder);
    connect(topButtons->isBlackAndWhite, &QCheckBox::stateChanged, chartsView, &ChartsView::changeColorPalette);
}

void App::chooseFolder() {
    QString folderPath = QFileDialog::getExistingDirectory(this, tr("Open Folder"), QDir::homePath(), QFileDialog::ShowDirsOnly);
    if (folderPath != "") {
        emit onFolderChange(folderPath);
    }
}

void App::currentIndexChanged(QModelIndex index) {
    QFileSystemModel *fileModel = new QFileSystemModel(this);

    QString suffix = fileModel->fileInfo(index).suffix();

    if (fileModel->fileInfo(index).size() > 1048576) {
        emit showPlaceholder("Файл слишком большой");
        delete fileModel;
        return;
    }

    if (suffix == "sqlite") {
        qDebug() << "current file is sqlite";

        SQLiteDataReader sql;
        QVariant data = sql.getData(fileModel->fileInfo(index));
        QMap<QString, QVariant> temp = data.toMap();

        if (temp.size() > 0) {
            emit updateChartData(temp);
        }

    } else if (suffix == "json") {
        qDebug() << "current file is json";

        JsonDataReader json;
        QVariant data = json.getData(fileModel->fileInfo(index));
        QMap<QString, QVariant> temp = data.toMap();

        if (temp.size() > 0) {
            emit updateChartData(temp);
        }
    }

    delete fileModel;
}

void App::typeChanged(QString type) {
    if (type == "Bar Chart") {
        chartsView->setChartType(new BarChart());
    } else if (type == "Pie Chart") {
        chartsView->setChartType(new PieChart());
    }
}
