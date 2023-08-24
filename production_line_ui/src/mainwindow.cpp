// mainwindow.cpp

#include "../include/mainwindow.h"
#include "../ui_mainwindow.h"
#include "../include/mqtt_client.h"
#include "../include/json_parser.h"

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


    test = new MQTTClient("5.tcp.eu.ngrok.io:18017", "testff"); // change unique client ID
    test->connect();
    test->subscribe("test/12345"); // name of the test/topic
    test->subscribe("Conveyer_speed");
    ui->lcdNumber->display(test->conveyer_upm); // set speed lcdNumber to display current default speed.
    ui->conveyer_units_per_minute_slider->setValue(test->conveyer_upm); // set slider starting value to current speed
}

MainWindow::~MainWindow()
{
    if (test) {
        test->disconnect();
        delete test;
    }
    delete ui;
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

    /*
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


    test->publish("test/12345", j.dump()); */
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
        QDateTime timestamp = QDateTime::fromString(QString::fromStdString(sample.timestamp), "yyyy-MM-ddTHH:mm:ssZ");
        for (int i{0}; i < 10; ++i)
        {
            multi_series[i]->append(timestamp.toMSecsSinceEpoch(), sample.heat_sensors[i]);
        }
    }

}




void MainWindow::on_conveyer_units_per_minute_slider_valueChanged(int value)
{
    if(allow_custom_params)
    {
        test->conveyer_upm = value;
    }
    else{
        ui->conveyer_units_per_minute_slider->setValue(test->conveyer_upm);
    }

}


void MainWindow::on_conveyer_units_per_minute_slider_sliderReleased()
{
    if(allow_custom_params)
    {
        test->set_conveyor_speed(test->conveyer_upm);
    }

}


void MainWindow::on_Allow_custom_params_toggled(bool checked)
{
    allow_custom_params = !allow_custom_params;
}
