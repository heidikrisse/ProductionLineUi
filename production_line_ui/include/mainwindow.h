// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mqtt_client.h"
#include "sqlite.hpp"

#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QThread>
#include <memory>
#include <thread>
#include <QSharedPointer>
#include <QScopedPointer>
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

        void conveyor_speed_received();
        void conveyor_control_received();
        void heater_controls_received();
        void heater_states_received();
        void cooler_states_received();
        void cooler_control_received();
        void camera_state_received();
        void temps_received();
        void db_update_received();
        void on_tabWidget_currentChanged(int index);

      private:
        Ui::MainWindow *ui;
        std::unique_ptr<MQTTClient> mqtt_client;
        QList<QSplineSeries *> multi_series;
        QLabel *rejectionLabel;
        QLabel *costLabel;
        QLCDNumber *h1_temp;
        std::unique_ptr<Db_manager> db;
        std::unique_ptr<QPalette> over80;
        std::unique_ptr<QPalette> under80;
        std::unique_ptr<QChart> chart;
        std::unique_ptr<QChartView> chart_view;
        std::unique_ptr<QDateTimeAxis> axis_x;
        std::unique_ptr<QValueAxis> axis_y;
};

#endif
