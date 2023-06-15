#include "topbuttons.h"
#include <QHBoxLayout>
#include <QFormLayout>

TopButtons::TopButtons(QWidget* parent) : QWidget(parent) {
    chooseFolder = new QPushButton("Выбрать папку", this);

    chartType = new QComboBox(this);
    chartType->addItem("Pie Chart");
    chartType->addItem("Bar Chart");

    chartTypeLabel = new QLabel("Тип диаграммы", this);

    isBlackAndWhite = new QCheckBox(this);
    isBlackAndWhiteLabel = new QLabel("Черно-белый график", this);

    printToPDF = new QPushButton("Сохранить в PDF", this);

    QHBoxLayout* comboboxLayout = new QHBoxLayout();

    comboboxLayout->addWidget(chartTypeLabel);
    comboboxLayout->addWidget(chartType);
    comboboxLayout->setSpacing(5);

    QHBoxLayout* checkboxLayout = new QHBoxLayout();

    checkboxLayout->addWidget(isBlackAndWhite);
    checkboxLayout->addWidget(isBlackAndWhiteLabel);
    checkboxLayout->setSpacing(5);

    QHBoxLayout* hLayout = new QHBoxLayout(this);
    hLayout->setSpacing(20);

    hLayout->addStretch();
    hLayout->addWidget(chooseFolder);
    hLayout->addLayout(comboboxLayout);
    hLayout->addLayout(checkboxLayout);
    hLayout->addWidget(printToPDF);
    hLayout->addStretch();
}
