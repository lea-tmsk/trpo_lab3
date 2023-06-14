#include "chartsview.h"
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QStackedBarSeries>
#include <QVector>
#include <QLabel>
#include <QHBoxLayout>
#include <QPdfWriter>
#include <QFileDialog>

ChartsView::ChartsView(QWidget *parent) {
    Q_UNUSED(parent);

    m_chartLayout = new QVBoxLayout(this);
    m_placeholder = new QLabel("Выберите файл", this);

    m_placeholderLayout = new QHBoxLayout();

    m_placeholderLayout->addStretch();
    m_placeholderLayout->addWidget(m_placeholder);
    m_placeholderLayout->addStretch();

    m_chartView = new QtCharts::QChartView();

    m_chartLayout->addLayout(m_placeholderLayout);

    m_chartView->setRenderHint(QPainter::Antialiasing);

    m_chart = m_chartView->chart();

    m_chart->setTheme(QtCharts::QChart::ChartThemeLight);

    m_chart->legend()->hide();
    m_chartType = new PieChart();
}

void ChartsView::setChartType(Chart *newType) {
    if (newType != nullptr) {
        m_chartType = newType;
        if (m_currentData.size() > 0) {
            updateChart();
        }
    }
}

void ChartsView::setData(const QMap<QString, QVariant>& data) {
    m_currentData = data;
    updateChart();
}

void ChartsView::updateChart() {
    m_chartLayout->removeItem(m_placeholderLayout);
    m_chart->removeAllSeries();

    QtCharts::QAbstractSeries *series = m_chartType->getSeries(m_currentData);
    m_chart->addSeries(series);

    m_chart->createDefaultAxes();

    m_chartLayout->addWidget(m_chartView);
    m_chartView->show();
}

void ChartsView::updatePlaceholder(QString str) {
    m_chartView->hide();

    m_placeholder->setText(str);

    m_placeholderLayout->setParent(nullptr);
    m_chartLayout->addLayout(m_placeholderLayout);
}

void ChartsView::changeColorPalette(bool isBlackAndWhite) {
    if (isBlackAndWhite == true) {
        m_chart->setTheme(QtCharts::QChart::ChartThemeHighContrast);
    } else {
        m_chart->setTheme(QtCharts::QChart::ChartThemeLight);
    }

    if (m_currentData.size() > 0) {
        updateChart();
    }
}

void ChartsView::printToPDF() {
    if (m_currentData.size() == 0) {
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save as"), QDir::homePath(), tr("PDF Files (*.pdf)"));

    QPdfWriter writer(fileName);

    writer.setCreator("Charts");//Указываем создателя документа

    writer.setPageSize(QPagedPaintDevice::A4);//Устанавливаем размер страницы

    QPainter painter(&writer);

    m_chartView->render(&painter);
    painter.end();
}

QtCharts::QAbstractSeries *PieChart::getSeries(const QMap<QString, QVariant>& data) {
    m_series = new QtCharts::QPieSeries();
    QMapIterator<QString, QVariant> i(data);
    while (i.hasNext()) {
        i.next();
        m_series->append(i.key(), i.value().toDouble());
    }
    return m_series;
}

QtCharts::QAbstractSeries *BarChart::getSeries(const QMap<QString, QVariant>& data) {
    m_series = new QtCharts::QStackedBarSeries();
    QMapIterator<QString, QVariant> i(data);
    QtCharts::QBarSet *set = new QtCharts::QBarSet("");
    while (i.hasNext()) {
        i.next();
        *set << i.value().toDouble();
    }
    m_series->append(set);

//    while (i.hasNext()) {
//        QtCharts::QBarSet *set = new QtCharts::QBarSet("");
//        i.next();
//        *set << i.value().toDouble();
//        m_series->append(set);
//    }
    return m_series;
}
