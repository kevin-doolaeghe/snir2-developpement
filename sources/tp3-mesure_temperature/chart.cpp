#include "chart.h"

Chart::Chart(QWidget *parent)
{
    layout = new QHBoxLayout();
    view = new QChartView();
    chart = new QChart();
    trace = new QLineSeries(chart);

    isFirstTrace = true;
    traceName = "Trace";

    chart->setTitle("Chart");

    parent->setLayout(layout);
    layout->addWidget(view);
    view->setChart(chart);

    nbVal = 0;
    yMin = -10;
    yMax = 10;

    update();
}

Chart::~Chart()
{
    delete layout;
    delete view;
    delete chart;
    delete trace;
}

void Chart::update()
{
    if(isFirstTrace) isFirstTrace = false;
    else chart->removeSeries(trace);

    trace->clear();
    for(QPair<QPointF, QString> data : list)
    {
        trace->append(data.first);
    }
    trace->setName(traceName);
    chart->addSeries(trace);
    chart->createDefaultAxes();
    if(nbVal < LIMIT) chart->axisX()->setRange(0, LIMIT);
    else chart->axisX()->setRange(nbVal - LIMIT, nbVal);
    chart->axisY()->setRange(yMin, yMax);
}

void Chart::addValue(float y)
{
    QPair<QPointF, QString> val(QPointF(nbVal, (qreal) y), "");

    list.append(val);
    if(nbVal > LIMIT) list.removeFirst();

    if(y > yMax) yMax = y + 2;
    if(y < yMin) yMin = y - 2;

    nbVal++;
}

void Chart::setTitle(QString s)
{
    chart->setTitle(s);
}

void Chart::setTraceName(QString s)
{
    traceName = s;
}
