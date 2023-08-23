// mainwindow.cpp
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mqtt_client.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

        axis_x = new QDateTimeAxis();
        axis_y = new QValueAxis();
        chart = new QChart();

        // Y-axis
        axis_y->setLabelFormat("%i");
        axis_y->setTitleText("Celcius degrees");
        axis_y->setRange(0, 90);

        // X-axis
        axis_x->setTickCount(10);
        axis_x->setFormat("hh:mm:ss");
        axis_x->setTitleText("Time");
        axis_x->setMax(QDateTime::fromString("230000",  "hhmmss"));
        axis_x->setMin(QDateTime::fromString("200000", "hhmmss"));

        // Chart
        chart->legend()->hide();
        chart->setTitle("Temperature");
        chart->addAxis(axis_x, Qt::AlignBottom);
        chart->addAxis(axis_y, Qt::AlignLeft);
        //chart->addSeries();
        //chart->addSeries();
        //chart->addSeries();

        auto* series = new QLineSeries();
        multi_series.append(series);
        series->setName(QString("sensor " + QString::number(multi_series.count())));
        series->attachAxis(axis_x);
        series->attachAxis(axis_y);

        // ChartView
        chart_view = new QChartView(chart);
        chart_view->setRenderHint(QPainter::Antialiasing);
        chart_view->setParent(ui->temperature_chart);


    MQTTClient test("broker.hivemq.com", "test");
    test.connect();
    test.subscribe("TestTopic123");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    test->publish("TestTopic123", "Hello world");
}


void MainWindow::on_pushButton_2_clicked()
{
    // Series
//    series->clear();
//    series->append(QDateTime::fromString("200000", "hhmmss").toMSecsSinceEpoch(), 28);
//    series->append(QDateTime::fromString("210000", "hhmmss").toMSecsSinceEpoch(), 39);
//    series->append(QDateTime::fromString("220000", "hhmmss").toMSecsSinceEpoch(), 55);
//    series->append(QDateTime::fromString("223000", "hhmmss").toMSecsSinceEpoch(), 70);
}

