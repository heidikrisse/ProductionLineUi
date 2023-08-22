// mainwindow.cpp
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mqtt_client.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QLineSeries *series =  new QLineSeries();  // Constructor for QLineSeries
    series->append(0, 25);  // Append some hard coded examplle data to series
    series->append(2, 38);
    series->append(4, 55);
    series->append(6, 63);
    series->append(8, 76);

    auto chart = new QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Temperature");
    chart->legend()->setAlignment(Qt::AlignBottom);

    auto chart_view = new QChartView(chart);
    chart_view->setRenderHint(QPainter::Antialiasing);
    chart_view->setParent(ui->temperature_chart);

    test = new MQTTClient("broker.hivemq.com", "test");
    test->connect();
    test->subscribe("TestTopic123");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    test->publish("TestTopic123", "Hello world");
}

