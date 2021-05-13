#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QHBoxLayout>
#include <QMessageBox>

using namespace QtCharts;

#define LIMIT 10

class Chart
{
public:
    Chart(QWidget *parent);
    ~Chart();
    void update();
    void addValue(float y);
    void setTitle(QString s);
    void setTraceName(QString s);
private:
    QLayout *layout;
    QChartView *view;
    QChart *chart;
    QLineSeries *trace;
    QList<QPair<QPointF, QString>> list;
    QString traceName;
    int nbVal;
    float yMin, yMax;
    bool isFirstTrace;
};

#endif // CHART_H
