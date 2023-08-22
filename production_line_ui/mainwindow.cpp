// mainwindow.cpp
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mqtt_client.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

