#include "chartsview.h"
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QStackedBarSeries>
#include <QVector>

ChartsView::ChartsView()
{

}

QtCharts::QChartView* ChartsView::createChart(QMap<QString, QVariant> data) {
    m_chartView = new QtCharts::QChartView();
    m_chartView->setRenderHint(QPainter::Antialiasing);
    m_chartView->resize(640, 480);

    QtCharts::QChart *chart = m_chartView->chart();
//    chart->setTitle("Beautiful Pie Chart");
    chart->legend()->hide();

//    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
//    float hits = 73.0f, misses = 27.0f;
//    series->append("Hits", hits);
//    series->append("Misses", misses);

//    QtCharts::QPieSlice *hit_slice = series->slices().at(0);
//    hit_slice->setBrush(QColor(87, 147, 243));  // blue

//    QtCharts::QPieSlice *miss_slice = series->slices().at(1);
//    miss_slice->setBrush(QColor(221, 68, 68)); // red
    chart->addSeries(getSeries(data));

    // Due to Qt bug, must show() the chart before render()
    // or it will be draw too tiny in the PDF by QPainter

//    chartView->show();
    return m_chartView;
}

QtCharts::QAbstractSeries *PieChart::getSeries(QMap<QString, QVariant> data) {
    m_series = new QtCharts::QPieSeries();
    QMapIterator<QString, QVariant> i(data);
    while (i.hasNext()) {
        i.next();
        m_series->append(i.key(), i.value().toDouble());
    }
    return m_series;
}

QtCharts::QAbstractSeries *BarChart::getSeries(QMap<QString, QVariant> data) {
    m_series = new QtCharts::QStackedBarSeries();
//    QVector<QVariant> sets;
    QMapIterator<QString, QVariant> i(data);
    while (i.hasNext()) {
        i.next();
        QtCharts::QBarSet *set = new QtCharts::QBarSet(i.key());
        *set << i.value().toDouble();
//        sets.push_back(QBarSet(i.key()));
        m_series->append(set);
    }
    return m_series;
}
