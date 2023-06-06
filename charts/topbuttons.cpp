#include "topbuttons.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

TopButtons::TopButtons(QWidget* parent) : QWidget(parent) {
    chartType = new QComboBox(this);

    chartType->addItem("Pie Chart");
    chartType->addItem("Bar Chart");

    chartTypeLabel = new QLabel(this);

    chartTypeLabel->setText("Выберите тип диаграммы");

    isBlackAndWhite = new QCheckBox(this);

    isBlackAndWhiteLabel = new QLabel(this);

    isBlackAndWhiteLabel->setText("Черно-белый график");

    printToPDF = new QPushButton(this);

    printToPDF->setText("Печать графика");

    QHBoxLayout* hLayout = new QHBoxLayout(this);

    hLayout->addWidget(chartTypeLabel);
    hLayout->addWidget(chartType);
    hLayout->addWidget(isBlackAndWhite);
    hLayout->addWidget(isBlackAndWhiteLabel);
    hLayout->addWidget(printToPDF);
}
