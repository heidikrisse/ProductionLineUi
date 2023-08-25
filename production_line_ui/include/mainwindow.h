// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mqtt_client.h"

#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <memory>
#include <thread>
#include <QThread>

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
        void data_update_loop();
        void start_data_update_loop();
    private slots:


        void on_pushButton_clicked();

        void on_pushButton_2_clicked();

        //slider values
        void on_conveyer_units_per_minute_slider_valueChanged(int value);

        void on_conveyer_units_per_minute_slider_sliderReleased();

        friend class MQTTClient;

        void on_heater1_check_on_off_toggled(bool checked);

        void on_heater1_manual_automatic_toggled(bool checked);

        void on_heater2_checked_on_off_toggled(bool checked);

        void on_heater2_manual_automatic_toggled(bool checked);

        void on_heater3_checked_on_off_toggled(bool checked);

        void on_heater3_manual_automatic_toggled(bool checked);

        void on_qc_camera_on_off_toggled(bool checked);

        void on_speed_manual_or_auto_toggled(bool checked);

        void on_cooler_manual_auto_toggled(bool checked);

        void on_cooler_check_on_off_toggled(bool checked);

        void on_calculateButton_clicked();


      private:
        //int conveyer_upm = 423; // conveyer units per minute speed
        Ui::MainWindow *ui;
        MQTTClient *test;
        //QSplineSeries *series;
        QList<QSplineSeries *> multi_series;
        QChart *chart;
        QChartView *chart_view;
        QDateTimeAxis* axis_x;
        QValueAxis* axis_y;
        std::thread data_loop_thread;
        //std::unique_ptr<QValueAxis> axis_y;
        QLabel *rejectionLabel;
        QLabel *costLabel;
};

#endif
