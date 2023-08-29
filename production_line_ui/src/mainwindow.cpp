// mainwindow.cpp
#include "../ui_mainwindow.h"
#include "../include/mqtt_client.h"
#include "../include/mainwindow.h"
#include "../include/json_parser.h"
#include "../include/sqlite.hpp"

#include <QtSql>
#include <QThread>
#include <QLCDNumber>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //for displaying the temps
    under80 = new QPalette;
    over80 = new QPalette;
    over80->setColor(QPalette::WindowText, QColor(Qt::red));
    under80->setColor(QPalette::WindowText, QColor(Qt::green));

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

    for (int i{1}; i < 11; i++)
    {
        auto* series = new QSplineSeries();
        multi_series.append(series);
        series->setName(QString("HS " + QString::number(i)));
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
    QVBoxLayout *layout = new QVBoxLayout(ui->chart_frame);
    layout->addWidget(chart_view);

    // Create database and tables, if not exist
    db = new Db_manager();
    db->create_connection();

    /* !!!!!!!!!!!!!!! CHANGE UNIQUE CLIENT ID HERE !!!!!!!!!!!!!!! */

    test = new MQTTClient("0.tcp.eu.ngrok.io:16108", "abc345"); // change unique client ID
    test->connect();
    test->subscribe("conveyer_params");
    test->subscribe("test/12345"); // name of the test/topic


    conveyer_speed_received();
    conveyer_control_received();
    cooler_control_received();
    cooler_states_received();
    heater_states_received();
    heater_controls_received();
    camera_state_received();
    temps_received();

    worker = new QThread;
    test->moveToThread(worker);
    // Calculate analytics
    // Find the labels in the analytics tab
    rejectionLabel = ui->tabWidget->findChild<QLabel*>("rejectionLabel");
    costLabel = ui->tabWidget->findChild<QLabel*>("costLabel");

    // Check if the labels were found and assign initial text
    if (rejectionLabel)
        rejectionLabel->setText("Rejection Percentage: 0.00 %");
    if (costLabel)
        costLabel->setText("Operating Cost: 0.00 €");

    connect(test, &MQTTClient::conveyer_speed_changed, this, &MainWindow::conveyer_speed_received);
    connect(test, &MQTTClient::conveyer_control, this, &MainWindow::conveyer_control_received);
    connect(test, &MQTTClient::heater_controls, this, &MainWindow::heater_controls_received);
    connect(test, &MQTTClient::heater_states, this, &MainWindow::heater_states_received);
    connect(test, &MQTTClient::cooler_state, this, &MainWindow::cooler_states_received);
    connect(test, &MQTTClient::cooler_control, this, &MainWindow::cooler_control_received);
    connect(test, &MQTTClient::qc_camera_state, this, &MainWindow::camera_state_received);
    connect(test, &MQTTClient::temps_changed, this, &MainWindow::temps_received);
    connect(test, &MQTTClient::db_updated, this, &MainWindow::db_update_received);


    worker->start();
}

MainWindow::~MainWindow()
{
    if (data_loop_thread.joinable())
    {
        data_loop_thread.join();

    }
    if (test)
    {
        test->disconnect();
        delete test;
    }

    if (data_loop_thread.joinable())
    {
        data_loop_thread.join();
    }
    delete axis_x;
    delete axis_y;
    delete chart;
    delete chart_view;
    delete db;
    //delete layout;

    worker->quit();
    worker->wait();
    delete worker;

    delete ui;
}

void MainWindow::db_update_received()
{

    db->add_line_data(test->curr_data);
    db->print_line_data();
}

void MainWindow::conveyer_speed_received()
{
    ui->conveyer_units_per_minute_slider->setValue(test->curr_data.conveyer_upm);
    ui->lcdNumber->display(test->curr_data.conveyer_upm);
}

void MainWindow::conveyer_control_received()
{
    ui->speed_manual_or_auto->setChecked(test->curr_data.conveyer_manual_control);
}
void MainWindow::heater_controls_received()
{
    ui->heater1_check_on_off->setEnabled(test->curr_data.heater1_manual_control);
    ui->heater2_checked_on_off->setEnabled(test->curr_data.heater2_manual_control);
    ui->heater3_checked_on_off->setEnabled(test->curr_data.heater3_manual_control);

    ui->heater1_manual_automatic->setChecked(test->curr_data.heater1_manual_control);
    ui->heater2_manual_automatic->setChecked(test->curr_data.heater2_manual_control);
    ui->heater3_manual_automatic->setChecked(test->curr_data.heater3_manual_control);

}
void MainWindow::heater_states_received()
{
    ui->heater1_check_on_off->setChecked(test->curr_data.heater1);
    ui->heater2_checked_on_off->setChecked(test->curr_data.heater2);
    ui->heater3_checked_on_off->setChecked(test->curr_data.heater3);

}
void MainWindow::cooler_states_received()
{
    ui->cooler_check_on_off->setChecked(test->curr_data.cooler);
}
void MainWindow::camera_state_received()
{
    ui->qc_camera_on_off->setChecked(test->curr_data.qc_camera_toggle);
}

void MainWindow::cooler_control_received()
{
    ui->cooler_check_on_off->setEnabled(test->curr_data.cooler_manual_control);
    ui->cooler_manual_auto->setChecked(test->curr_data.cooler_manual_control);
}
void MainWindow::temps_received()
{
    ui->s0_temp->display(test->curr_data.temps[0]);
    if(test->curr_data.temps[0] >= 80){
        ui->s0_temp->setPalette(*over80);
    }
    else{
        ui->s0_temp->setPalette(*under80);
    }
    ui->s1_temp->display(test->curr_data.temps[1]);
    if(test->curr_data.temps[1] >= 80){
        ui->s1_temp->setPalette(*over80);
    }
    else{
        ui->s1_temp->setPalette(*under80);
    }
    ui->s2_temp->display(test->curr_data.temps[2]);
    if(test->curr_data.temps[2] >= 80){
        ui->s2_temp->setPalette(*over80);
    }
    else{
        ui->s2_temp->setPalette(*under80);
    }
    ui->s3_temp->display(test->curr_data.temps[3]);
    if(test->curr_data.temps[3] >= 80){
        ui->s3_temp->setPalette(*over80);
    }
    else{
        ui->s3_temp->setPalette(*under80);
    }
    ui->s4_temp->display(test->curr_data.temps[4]);
    if(test->curr_data.temps[4] >= 80){
        ui->s4_temp->setPalette(*over80);
    }
    else{
        ui->s4_temp->setPalette(*under80);
    }
    ui->s5_temp->display(test->curr_data.temps[5]);
    if(test->curr_data.temps[5] >= 80){
        ui->s5_temp->setPalette(*over80);
    }
    else{
        ui->s5_temp->setPalette(*under80);
    }
    ui->s6_temp->display(test->curr_data.temps[6]);
    if(test->curr_data.temps[6] >= 80){
        ui->s6_temp->setPalette(*over80);
    }
    else{
        ui->s6_temp->setPalette(*under80);
    }
    ui->s7_temp->display(test->curr_data.temps[7]);
    if(test->curr_data.temps[7] >= 80){
        ui->s7_temp->setPalette(*over80);
    }
    else{
        ui->s7_temp->setPalette(*under80);
    }
    ui->s8_temp->display(test->curr_data.temps[8]);
    if(test->curr_data.temps[8] >= 80){
        ui->s8_temp->setPalette(*over80);
    }
    else{
        ui->s8_temp->setPalette(*under80);
    }
    ui->s9_temp->display(test->curr_data.temps[9]);
    if(test->curr_data.temps[9] >= 80){
        ui->s9_temp->setPalette(*over80);
    }
    else{
        ui->s9_temp->setPalette(*under80);
    }
}

void MainWindow::on_conveyer_units_per_minute_slider_valueChanged(int value)
{
    if(test->curr_data.conveyer_manual_control)
    {
        test->curr_data.conveyer_upm = value;
    }
    else
    {
        ui->conveyer_units_per_minute_slider->setValue(test->curr_data.conveyer_upm);
    }
}

void MainWindow::on_conveyer_units_per_minute_slider_sliderReleased()
{
    if(test->curr_data.conveyer_manual_control)
    {
        test->publish_data();
    }
}

void MainWindow::on_heater1_check_on_off_toggled(bool checked)
{
        test->curr_data.heater1 = checked;
        test->publish_data();
}

void MainWindow::on_heater1_manual_automatic_toggled(bool checked)
{
    ui->heater1_check_on_off->setEnabled(checked);
    test->curr_data.heater1_manual_control = checked;
    test->publish_data();
}

void MainWindow::on_heater2_checked_on_off_toggled(bool checked)
{
    test-> curr_data.heater2 = checked;
    test->publish_data();
}


void MainWindow::on_heater2_manual_automatic_toggled(bool checked)
{
    ui->heater2_checked_on_off->setEnabled(checked);
    test-> curr_data.heater2_manual_control = checked;
    test->publish_data();
}

void MainWindow::on_heater3_checked_on_off_toggled(bool checked)
{
    test-> curr_data.heater3 = checked;
    test->publish_data();
}


void MainWindow::on_heater3_manual_automatic_toggled(bool checked)
{
    ui->heater3_checked_on_off->setEnabled(checked);
    test-> curr_data.heater3_manual_control = checked;
    test->publish_data();
}

void MainWindow::on_qc_camera_on_off_toggled(bool checked)
{
    test-> curr_data.qc_camera_toggle = checked;
    test->publish_data();
}


void MainWindow::on_speed_manual_or_auto_toggled(bool checked)
{
    test-> curr_data.conveyer_manual_control = checked;
    test->publish_data();
}

void MainWindow::on_cooler_manual_auto_toggled(bool checked)
{
    ui->cooler_check_on_off->setEnabled(checked);
    test->curr_data.cooler_manual_control = checked;
    test->publish_data();
}

void MainWindow::on_cooler_check_on_off_toggled(bool checked)
{
    test->curr_data.cooler = checked;
    test->publish_data();
}

void MainWindow::on_calculateButton_clicked()
{
    double rejectionRate = test->get_failure_rate() * 100.0;
    double operatingCost = test->get_operating_cost();

    if (rejectionLabel)
    {
        rejectionLabel->setText(QString("Rejection Percentage: %1%").arg(QString::number(rejectionRate, 'f', 2)));
    }
    if (costLabel)
    {
        costLabel->setText(QString("Operating Cost: $%1").arg(QString::number(operatingCost, 'f', 2)));
    }
}
