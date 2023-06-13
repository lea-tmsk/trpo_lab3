#ifndef CHARTSVIEW_H
#define CHARTSVIEW_H
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QWidget>
#include <QMap>
#include <QString>
#include <QVariant>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

class Chart {
//    Q_OBJECT
public:
    Chart() {};
    virtual ~Chart() = default;
    virtual QtCharts::QAbstractSeries* getSeries(QMap<QString, QVariant> data) = 0;/*{
        qDebug() << "no chart chosen";
        return nullptr;
    }*/
};

class PieChart : public Chart {
public:
    PieChart() {};
    ~PieChart() {
        delete m_series;
    }
    QtCharts::QAbstractSeries* getSeries(QMap<QString, QVariant> data) override;
    QtCharts::QPieSeries *m_series;
};

class BarChart : public Chart {
public:
    BarChart() {};
    ~BarChart() {
        delete m_series;
    }
    QtCharts::QAbstractSeries* getSeries(QMap<QString, QVariant> data) override;
    QtCharts::QStackedBarSeries *m_series;
};

class LineChart : public Chart {
public:
    LineChart() {};
    ~LineChart() {
        delete m_series;
    }

    QtCharts::QAbstractSeries *getSeries(QMap<QString, QVariant> data) override;
    QtCharts::QLineSeries *m_series;
};

class ChartsView : public QWidget {
    Q_OBJECT
public:
    ChartsView(QWidget *parent = nullptr);
    ~ChartsView() {
        delete m_chart;
        delete m_chartLayout;
        delete m_chartView;
        delete m_placeholder;
        delete m_placeholderLayout;
        delete m_chartType;
    }

    void setChartType(Chart *newType);
    void setData(const QMap<QString, QVariant>& data);

public slots:
    void updateChart();
    void updatePlaceholder(QString str);
    void changeColorPalette(bool isBlackAndWhite);
    void printToPDF();

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
