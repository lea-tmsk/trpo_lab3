#ifndef CHARTSVIEW_H
#define CHARTSVIEW_H
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QStackedBarSeries>
#include <QWidget>
#include <QMap>
#include <QString>
#include <QVariant>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

class Chart {
public:
    Chart() {};
    virtual ~Chart() = default;
    virtual QtCharts::QAbstractSeries* getSeries(const QMap<QString, QVariant>& data) = 0;
};

class PieChart : public Chart {
public:
    PieChart() {};
    ~PieChart() {
        delete m_series;
    }
    QtCharts::QAbstractSeries* getSeries(const QMap<QString, QVariant>& data) override;
    QtCharts::QPieSeries *m_series;
};

class BarChart : public Chart {
public:
    BarChart() {};
    ~BarChart() {
        delete m_series;
    }
    QtCharts::QAbstractSeries* getSeries(const QMap<QString, QVariant>& data) override;
    QtCharts::QStackedBarSeries *m_series;
};

class ChartsView : public QWidget {
    Q_OBJECT
public:
    ChartsView(QWidget *parent = nullptr);
    ~ChartsView() {};

public slots:
    void updateChart();
    void updatePlaceholder(QString str);
    void changeColorPalette(bool isBlackAndWhite);
    void printToPDF();
    void setChartType(Chart *newType);
    void setData(const QMap<QString, QVariant>& data);

private:
    QtCharts::QChartView *m_chartView;
    QVBoxLayout *m_chartLayout;
    QLabel *m_placeholder;
    QHBoxLayout *m_placeholderLayout;
    QtCharts::QChart *m_chart;
    Chart *m_chartType;
    QMap<QString, QVariant> m_currentData;
};

#endif // CHARTSVIEW_H
