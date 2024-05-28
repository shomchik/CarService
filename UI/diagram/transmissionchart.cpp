#include <QVBoxLayout>

#include "transmissionchart.h"
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>

TransmissionChart::TransmissionChart(QWidget *parent)
    : QWidget(parent) {
    orderService = new OrderService();
    carService = new CarService();
    createChart();

}

void TransmissionChart::createChart() {
    auto orders = orderService->getAllOrders();
    std::map<Transmission, int> transmissionCount = {
        {MANUAL, 0},
        {AUTOMATIC, 0},
        {VARIATOR, 0},
        {UNKNOWN_TRANSMISSION, 0}
    };

    for (const auto &order: orders) {
        auto carOpt = carService->getCarById(order.getCarId().toStdString());
        if (carOpt) {
            transmissionCount[carOpt->getTransmission()]++;
        }
    }

    auto *series = new QPieSeries();
    series->append("Механическая", transmissionCount[MANUAL]);
    series->append("Автоматическая", transmissionCount[AUTOMATIC]);
    series->append("Вариатор", transmissionCount[VARIATOR]);

    auto *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Типы коробки передач автомобилей по заказам");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);
}
