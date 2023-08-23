// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mqtt_client.h"

#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void on_pushButton_clicked();

        void on_pushButton_2_clicked();


private:
    Ui::MainWindow *ui;
    MQTTClient *test;
    //QSplineSeries *series;
    QList<QSplineSeries *> multi_series;
    QChart *chart;
    QChartView *chart_view;
    QDateTimeAxis* axis_x;
    QValueAxis* axis_y;
    //std::unique_ptr<QValueAxis> axis_y;
};

#endif
