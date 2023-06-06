#ifndef CHARTSVIEW_H
#define CHARTSVIEW_H
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QStackedBarSeries>
#include <QWidget>
#include <QMap>
#include <QString>
#include <QVariant>

class ChartsView : public QWidget {
    Q_OBJECT
public:
    ChartsView();
    QtCharts::QChartView* createChart(QMap<QString, QVariant> data);

private:
    virtual QtCharts::QAbstractSeries* getSeries(QMap<QString, QVariant> data) = 0;
    QtCharts::QChartView *m_chartView;
};

class PieChart : public ChartsView {
    QtCharts::QAbstractSeries* getSeries(QMap<QString, QVariant> data) override;
    QtCharts::QPieSeries *m_series;
};

class BarChart : public ChartsView {
    QtCharts::QAbstractSeries* getSeries(QMap<QString, QVariant> data) override;
    QtCharts::QStackedBarSeries *m_series;
};

#endif // CHARTSVIEW_H
