// mainwindow.cpp
#include "../include/mainwindow.h"
#include "../ui_mainwindow.h"
#include "../include/mqtt_client.h"
#include "../include/json_parser.h"
#include "../include/mqtt_main_window_bridge.h"

#include <thread>
#include <mutex>

static std::mutex data_mutex;
static std::atomic<bool> stop_data_loop(false);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // MainWindow has a member called 'test' of type 'MQTTClient*'
    MqttMainWindowBridge* bridge = new MqttMainWindowBridge(this, test);

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
    QVBoxLayout *layout = new QVBoxLayout(ui->chart_frame);
    layout->addWidget(chart_view);

    /* !!!!!!!!!!!!!!! CHANGE UNIQUE CLIENT ID HERE !!!!!!!!!!!!!!! */

    test = new MQTTClient("5.tcp.eu.ngrok.io:18017", "abcd1234heidikr"); // change unique client ID
    test->connect();
    test->subscribe("conveyer_params");
    test->subscribe("test/12345"); // name of the test/topic
    ui->lcdNumber->display(test->conveyer_upm); // set speed lcdNumber to display current default speed.
    ui->conveyer_units_per_minute_slider->setValue(test->conveyer_upm); // set slider starting value to current speed
    ui->speed_manual_or_auto->setChecked(test->conveyer_manual_control);
    ui->cooler_manual_auto->setChecked(test->cooler_manual_control);
    ui->cooler_check_on_off->setChecked(test->cooler);
    ui->heater1_manual_automatic->setChecked(test->heater1_manual_control);
    ui->heater2_manual_automatic->setChecked(test->heater2_manual_control);
    ui->heater3_manual_automatic->setChecked(test->heater3_manual_control);
    ui->heater1_check_on_off->setChecked(test->heater1);
    ui->heater2_checked_on_off->setChecked(test->heater2);
    ui->heater3_checked_on_off->setChecked(test->heater3);
    ui->qc_camera_on_off->setChecked(test->qc_camera_toggle);

    // Calculate analytics
    // Find the labels in the analytics tab
    rejectionLabel = ui->tabWidget->findChild<QLabel*>("rejectionLabel");
    costLabel = ui->tabWidget->findChild<QLabel*>("costLabel");

    // Check if the labels were found and assign initial text
    if (rejectionLabel)
        rejectionLabel->setText("Rejection Percentage: 0.00%");
    if (costLabel)
        costLabel->setText("Operating Cost: $0.00");
}

MainWindow::~MainWindow()
{
    stop_data_loop.store(true);
    if (data_loop_thread.joinable())
    {
        data_loop_thread.join();

    }
    if (test)
    {
        test->disconnect();
        delete test;
    }
    delete ui;
}

void MainWindow::data_update_loop()
{
    std::lock_guard<std::mutex> data_lock(data_mutex);
    while(not stop_data_loop)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        ui->lcdNumber->display(test->conveyer_upm); // set speed lcdNumber to display current default speed.
        ui->conveyer_units_per_minute_slider->setValue(test->conveyer_upm); // set slider starting value to current speed
        ui->speed_manual_or_auto->setChecked(test->conveyer_manual_control);
        ui->cooler_manual_auto->setChecked(test->cooler_manual_control);
        ui->cooler_check_on_off->setChecked(test->cooler);
        ui->heater1_manual_automatic->setChecked(test->heater1_manual_control);
        ui->heater2_manual_automatic->setChecked(test->heater2_manual_control);
        ui->heater3_manual_automatic->setChecked(test->heater3_manual_control);
        ui->heater1_check_on_off->setChecked(test->heater1);
        ui->heater2_checked_on_off->setChecked(test->heater2);
        ui->heater3_checked_on_off->setChecked(test->heater3);
        ui->qc_camera_on_off->setChecked(test->qc_camera_toggle);
    }

}
void MainWindow::start_data_update_loop(){
    data_loop_thread = std::thread(&MainWindow::data_update_loop, this);
}
void MainWindow::on_pushButton_clicked()
{
    // Load data from a sample JSON file (line1.json) for testing
    std::string filename{"../json_examples/line1.json"};

    std::ifstream file(filename);
    if (file.is_open())
    {
        nlohmann::json j;
        file >> j;
        file.close();

        test->publish("test/12345", j.dump());
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    // Load the sample data
    std::vector<json_data::parsed_json> samples = test->load_sample_data("../json_examples");

    // Clear previous data from multi_series list (using multi_series list to manage the different series for each sensor)
    for (auto* series : multi_series) {
        series->clear();
    }

    // Add sample data to series
    for (const auto& sample : samples)
    {
        QDateTime timestamp = QDateTime::fromString(QString::fromStdString(sample.timestamp), "yyyy-MM-ddTHH:mm:ssGMT+2");
        for (int i{0}; i < 10; ++i)
        {
            multi_series[i]->append(timestamp.toMSecsSinceEpoch(), sample.heat_sensors[i]);
        }
    }
}




void MainWindow::on_conveyer_units_per_minute_slider_valueChanged(int value)
{
    if(test->conveyer_manual_control)
    {
        test->conveyer_upm = value;
    }
    else
    {
        ui->conveyer_units_per_minute_slider->setValue(test->conveyer_upm);
    }

}


void MainWindow::on_conveyer_units_per_minute_slider_sliderReleased()
{
    if(test->conveyer_manual_control)
    {
        test->publish_data();
    }

}

void MainWindow::on_heater1_check_on_off_toggled(bool checked)
{
    if(test->heater1_manual_control)
    {
        test->heater1 = checked;
        test->publish_data();
    }

}


void MainWindow::on_heater1_manual_automatic_toggled(bool checked)
{
    test->heater1_manual_control = checked;
    test->publish_data();
}


void MainWindow::on_heater2_checked_on_off_toggled(bool checked)
{
    if(test->heater2_manual_control){
        test->heater2 = checked;
        test->publish_data();
    }

}


void MainWindow::on_heater2_manual_automatic_toggled(bool checked)
{
    test->heater2_manual_control = checked;
    test->publish_data();
}


void MainWindow::on_heater3_checked_on_off_toggled(bool checked)
{
    if(test->heater3_manual_control){
        test->heater3 = checked;
        test->publish_data();
    }

}


void MainWindow::on_heater3_manual_automatic_toggled(bool checked)
{
    test->heater3_manual_control = checked;
    test->publish_data();
}


void MainWindow::on_qc_camera_on_off_toggled(bool checked)
{
    test->qc_camera_toggle = checked;
    test->publish_data();
}


void MainWindow::on_speed_manual_or_auto_toggled(bool checked)
{
    test->conveyer_manual_control = checked;
    test->publish_data();
}


void MainWindow::on_cooler_manual_auto_toggled(bool checked)
{
    test->cooler_manual_control = checked;
    test->publish_data();
}


void MainWindow::on_cooler_check_on_off_toggled(bool checked)
{
    if(test->cooler_manual_control)
    {
        test->cooler = checked;
        test->publish_data();
    }
}

void MainWindow::on_calculateButton_clicked()
{
    double rejectionRate = test->get_failure_rate() * 100.0;
    double operatingCost = test->get_operating_cost();

    ui->rejectionLabel->setText(QString("Rejection Percentage: %1%").arg(QString::number(rejectionRate, 'f', 2)));
    ui->costLabel->setText(QString("Operating Cost: $%1").arg(QString::number(operatingCost, 'f', 2)));
}

