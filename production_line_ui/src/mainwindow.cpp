// mainwindow.cpp
#include "../ui_mainwindow.h"
#include "../include/mqtt_client.h"
#include "../include/mainwindow.h"
#include "../include/sqlite.hpp"

#include <QtSql>
#include <QLCDNumber>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(std::make_unique<Ui::MainWindow>())
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: rgb(230, 234, 234);");

    //for displaying the temps
    under80 = std::make_unique<QPalette>();
    over80 = std::make_unique<QPalette>();
    over80->setColor(QPalette::WindowText, QColor(Qt::red));
    under80->setColor(QPalette::WindowText, QColor(qRgb(73, 166, 45)));

    axis_x = std::make_unique<QDateTimeAxis>();
    axis_y = std::make_unique<QValueAxis>();
    chart = std::make_unique<QChart>();

    // Y-axis
    axis_y->setLabelFormat("%i");
    axis_y->setTitleText("Celcius degrees");
    axis_y->setTitleFont(QFont("Sans Serif"));
    axis_y->setRange(0, 90);

    // X-axis
    axis_x->setTickCount(10);
    axis_x->setFormat("hh:mm");
    axis_x->setTitleText("hh:mm");
    axis_x->setTitleFont(QFont("Sans Serif"));
    // Set the initial range of the x-axis to the current time
    QDateTime currentDateTime = QDateTime::currentDateTime();
    axis_x-> setMin(currentDateTime); // starts showing from the current time
    axis_x->setMax(currentDateTime.addSecs(5*60)); // +5 mins

    // Chart
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setTitle("Current temperature"); // Chart title
    chart->setTitleFont(QFont("Sans Serif", 18, QFont::Bold)); // Font size and style  of the title
    chart->addAxis(axis_x.get(), Qt::AlignBottom);
    chart->addAxis(axis_y.get(), Qt::AlignLeft);

    for (int i{1}; i < 11; i++)
    {
        multi_series.append(std::make_shared<QSplineSeries>());
        auto series = multi_series.back();
        series->setName(QString("HS " + QString::number(i)));
        chart->addSeries(series.get());
        series->attachAxis(axis_x.get());
        series->attachAxis(axis_y.get());
    }

    // ChartView
    chart_view = std::make_unique<QChartView>(chart.get());
    chart_view->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *layout = new QVBoxLayout(ui->chart_frame);
    layout->addWidget(chart_view.get());

    // Create database and tables, if not exist
    db = std::make_unique<Db_manager>();
    db->create_connection();
    /* !!!!!!!!!!!!!!! CHANGE UNIQUE CLIENT ID HERE !!!!!!!!!!!!!!! */

    mqtt_client = std::make_unique<MQTTClient>("test.mosquitto.org:1883", "123heidu"); // change "test.mosquitto.org" to your mosquitto broker and change your own unique client ID
    mqtt_client->connect();
    mqtt_client->subscribe("sensor_control_data1");
    mqtt_client->subscribe("test/12345"); // name of the test/topic
    mqtt_client->update_analytics_values();

    conveyor_speed_received();
    conveyor_control_received();
    cooler_control_received();
    cooler_states_received();
    heater_states_received();
    heater_controls_received();
    camera_state_received();
    temps_received();

    // Calculate analytics:

    // Find the labels in the analytics tab
    rejectionLabel = ui->tabWidget->findChild<QLabel*>("rejectionLabel");
    costPerUnitLabel = ui->tabWidget->findChild<QLabel*>("costPerUnitLabel");
    totalCostLabel = ui->tabWidget->findChild<QLabel*>("totalCostLabel");

    connect(mqtt_client.get(), &MQTTClient::conveyor_speed_changed, this, &MainWindow::conveyor_speed_received);
    connect(mqtt_client.get(), &MQTTClient::conveyor_control, this, &MainWindow::conveyor_control_received);
    connect(mqtt_client.get(), &MQTTClient::heater_controls, this, &MainWindow::heater_controls_received);
    connect(mqtt_client.get(), &MQTTClient::heater_states, this, &MainWindow::heater_states_received);
    connect(mqtt_client.get(), &MQTTClient::cooler_state, this, &MainWindow::cooler_states_received);
    connect(mqtt_client.get(), &MQTTClient::cooler_control, this, &MainWindow::cooler_control_received);
    connect(mqtt_client.get(), &MQTTClient::qc_camera_state, this, &MainWindow::camera_state_received);
    connect(mqtt_client.get(), &MQTTClient::temps_changed, this, &MainWindow::temps_received);
    connect(mqtt_client.get(), &MQTTClient::db_updated, this, &MainWindow::db_update_received);

    //Gets all data from DB to data_cache
    // - TODO: remove from the constructor and implement a menu to choose a time period etc.
    mqtt_client->data_cache = db->get_all_dbData();
}

MainWindow::~MainWindow()
{
    multi_series.clear();
    mqtt_client = nullptr;
    over80 = nullptr;
    under80 = nullptr;
    axis_x = nullptr;
    axis_y = nullptr;
    chart = nullptr;
    chart_view = nullptr;
    db = nullptr;
}

void MainWindow::db_update_received()
{
    db->add_line_data(mqtt_client->curr_data);
}

void MainWindow::conveyor_speed_received()
{
    ui->currentSpeedLcd->display(mqtt_client->curr_data.conveyor_upm);
}

void MainWindow::conveyor_control_received()
{
    ui->speed_manual_or_auto->setChecked(mqtt_client->curr_data.conveyor_manual_control);
}

void MainWindow::heater_controls_received()
{
    ui->heater1_check_on_off->setEnabled(mqtt_client->curr_data.heater1_manual_control);
    ui->heater2_checked_on_off->setEnabled(mqtt_client->curr_data.heater2_manual_control);
    ui->heater3_checked_on_off->setEnabled(mqtt_client->curr_data.heater3_manual_control);

    ui->heater1_manual_automatic->setChecked(mqtt_client->curr_data.heater1_manual_control);
    ui->heater2_manual_automatic->setChecked(mqtt_client->curr_data.heater2_manual_control);
    ui->heater3_manual_automatic->setChecked(mqtt_client->curr_data.heater3_manual_control);

}

void MainWindow::heater_states_received()
{
    ui->heater1_check_on_off->setChecked(mqtt_client->curr_data.heater1);
    ui->heater2_checked_on_off->setChecked(mqtt_client->curr_data.heater2);
    ui->heater3_checked_on_off->setChecked(mqtt_client->curr_data.heater3);

}

void MainWindow::cooler_states_received()
{
    ui->cooler_check_on_off->setChecked(mqtt_client->curr_data.cooler);
}

void MainWindow::camera_state_received()
{
    ui->qc_camera_on_off->setChecked(mqtt_client->curr_data.qc_camera_toggle);
}

void MainWindow::cooler_control_received()
{
    ui->cooler_check_on_off->setEnabled(mqtt_client->curr_data.cooler_manual_control);
    ui->cooler_manual_auto->setChecked(mqtt_client->curr_data.cooler_manual_control);
}

void MainWindow::temps_received()
{
    // Update the UI temperature displays
    for (int i{0}; i < 10; ++i)
    {
        QLCDNumber *lcdNumber = ui->centralwidget->findChild<QLCDNumber *>(QString("s%1_temp").arg(i));
        if (lcdNumber)
        {
            lcdNumber->display(mqtt_client->curr_data.temps[i]);
            if (mqtt_client->curr_data.temps[i] >= 80)
            {
                lcdNumber->setPalette(*over80);
            }
            else
            {
                lcdNumber->setPalette(*under80);
            }
        }
    }

    // Get the current timestamp and update the graph
    qint64 currentTimestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();

    // Check if the current time exceeds the x-axis maximum, and update the x-axis accordingly
    if (currentTimestamp > axis_x->max().toMSecsSinceEpoch())
    {
        axis_x->setMin(QDateTime::fromMSecsSinceEpoch(currentTimestamp)); // every 5 mins the temp graph updated to the current time
        axis_x->setMax(QDateTime::fromMSecsSinceEpoch((currentTimestamp + (5*60*1000)))); // and the x-axis maximum updated +5 mins from the current time
    }

    for (size_t i{0}; i < mqtt_client->curr_data.temps.size(); ++i)
    {
        multi_series[i]->append(currentTimestamp, mqtt_client->curr_data.temps[i]);
    }
}

void MainWindow::on_conveyor_units_per_minute_slider_valueChanged(int value)
{
    if(mqtt_client->curr_data.conveyor_manual_control)
    {
        mqtt_client->conveyor_desired_speed = value;
    }
    else
    {
        ui->conveyor_units_per_minute_slider->setValue(mqtt_client->conveyor_desired_speed);
    }
}

void MainWindow::on_conveyor_units_per_minute_slider_sliderReleased()
{
    if(mqtt_client->curr_data.conveyor_manual_control)
    {
        mqtt_client->publish_data();
    }
}

void MainWindow::on_heater1_check_on_off_toggled(bool checked)
{
        mqtt_client->curr_data.heater1 = checked;
        mqtt_client->publish_data();
}

void MainWindow::on_heater1_manual_automatic_toggled(bool checked)
{
    ui->heater1_check_on_off->setEnabled(checked);
    mqtt_client->curr_data.heater1_manual_control = checked;
    mqtt_client->publish_data();
}

void MainWindow::on_heater2_checked_on_off_toggled(bool checked)
{
    mqtt_client-> curr_data.heater2 = checked;
    mqtt_client->publish_data();
}

void MainWindow::on_heater2_manual_automatic_toggled(bool checked)
{
    ui->heater2_checked_on_off->setEnabled(checked);
    mqtt_client-> curr_data.heater2_manual_control = checked;
    mqtt_client->publish_data();
}

void MainWindow::on_heater3_checked_on_off_toggled(bool checked)
{
    mqtt_client-> curr_data.heater3 = checked;
    mqtt_client->publish_data();
}

void MainWindow::on_heater3_manual_automatic_toggled(bool checked)
{
    ui->heater3_checked_on_off->setEnabled(checked);
    mqtt_client-> curr_data.heater3_manual_control = checked;
    mqtt_client->publish_data();
}

void MainWindow::on_qc_camera_on_off_toggled(bool checked)
{
    mqtt_client-> curr_data.qc_camera_toggle = checked;
    mqtt_client->publish_data();
}

void MainWindow::on_speed_manual_or_auto_toggled(bool checked)
{
    mqtt_client-> curr_data.conveyor_manual_control = checked;
    mqtt_client->publish_data();
}

void MainWindow::on_cooler_manual_auto_toggled(bool checked)
{
    ui->cooler_check_on_off->setEnabled(checked);
    mqtt_client->curr_data.cooler_manual_control = checked;
    mqtt_client->publish_data();
}

void MainWindow::on_cooler_check_on_off_toggled(bool checked)
{
    mqtt_client->curr_data.cooler = checked;
    mqtt_client->publish_data();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 1)
    { // analytics window
        mqtt_client->current_mw_tab = 2;

        double rejection_rate{mqtt_client->get_failure_rate()};
        std::pair<double, double> operating_cost = mqtt_client->get_operating_cost();
        double total_cost = operating_cost.first;
        double cost_per_unit_time = operating_cost.second;

        if (rejectionLabel)
        {
            rejectionLabel->setText(QString("%1 %").arg(QString::number(rejection_rate, 'f', 2)));
        }
        if (costPerUnitLabel)
        {
            costPerUnitLabel->setText(QString("%1 €/unit").arg(QString::number(cost_per_unit_time, 'f', 2)));
        }
        if (totalCostLabel)
        {
            totalCostLabel->setText(QString("%1 €").arg(QString::number(total_cost, 'f', 0)));
        }

        double average_temps{mqtt_client->get_average_temperature()};
        int average_speed{mqtt_client->get_average_upm()};

        ui->avgTempLabel->setText(QString("%1 °C").arg(QString::number(average_temps, 'f', 2)));
        ui->avgSpeedLabel->setText(QString("%1 units/min").arg(QString::number(average_speed)));
    }
    else
    {  // control window
        mqtt_client->current_mw_tab = 1;
    }
}
