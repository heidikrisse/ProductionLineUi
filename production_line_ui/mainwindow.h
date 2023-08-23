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


        //slider values
        void on_conveyer_units_per_minute_slider_valueChanged(int value);

        void on_conveyer_units_per_minute_slider_sliderReleased();

        void on_Allow_custom_params_toggled(bool checked);

      private:
        // TODO: Säädetään MQTT esim sillain että se pitää kirjaa
        // siitä mikä on viimeisin tiedetty arvo, ja nopeus otetaan sen perusteella
        // Jos ei saada onnistumaan niin luetaan vaikka tiedostosta tms.
        bool allow_custom_params = false;
        int conveyer_upm = 423; // conveyer units per minute speed


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
