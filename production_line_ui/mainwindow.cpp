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
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setTitle("Temperature");
    chart->addAxis(axis_x, Qt::AlignBottom);
    chart->addAxis(axis_y, Qt::AlignLeft);

    for (int i = 1; i < 11; i++) {
        auto* series = new QSplineSeries();
        multi_series.append(series);
        series->setName(QString("Sensor " + QString::number(i)));
        chart->addSeries(series);
        series->append(QDateTime::fromString("200000", "hhmmss").toMSecsSinceEpoch()+(3*i), (28+(2*i)));
        series->append(QDateTime::fromString("210000", "hhmmss").toMSecsSinceEpoch()+(3*i), (39+(2*i)));
        series->append(QDateTime::fromString("220000", "hhmmss").toMSecsSinceEpoch()+(3*i), (55+(2*i)));
        series->append(QDateTime::fromString("223000", "hhmmss").toMSecsSinceEpoch()+(3*i), (70+(2*i)));
        series->attachAxis(axis_x);
        series->attachAxis(axis_y);
    }

    // ChartView
    chart_view = new QChartView(chart);
    chart_view->setRenderHint(QPainter::Antialiasing);
    chart_view->setParent(ui->temperature_chart);

    test = new MQTTClient("4.tcp.eu.ngrok.io:16834", "11234567890heidi"); // change unique client ID
    test->connect();
    test->subscribe("test/12345"); // name of the test/topic
}

MainWindow::~MainWindow()
{
    test->disconnect();
    delete test;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    nlohmann::json j;
    j["timestamp"] = "asdf";
    j["conveyor_speed"] = 14;
    j["heater1"] = false;
    j["heater2"] = false;
    j["heater3"] = false;
    j["cooler"] = false;
    j["qc_camera"] = false;
    j["temp_sensor1"] = 1.1f;
    j["temp_sensor2"] = 1.1f;
    j["temp_sensor3"] = 1.1f;
    j["temp_sensor4"] = 1.1f;
    j["temp_sensor5"] = 1.1f;
    j["temp_sensor6"] = 1.1f;
    j["temp_sensor7"] = 1.1f;
    j["temp_sensor8"] = 1.1f;
    j["temp_sensor9"] = 1.1f;
    j["temp_sensor10"] = 1.1f;


    test->publish("test/12345", j.dump());
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

