#include <QVBoxLayout>
#include "transmissionchart.h"
#include <QMainWindow>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include "QPushButton"
#include "../cars/catalog/carcatalogpage.h"

class CarCatalogPage;

TransmissionChart::TransmissionChart(QWidget *parent)
    : QWidget(parent), chartView(new QChartView(this)) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    orderService = new OrderService();
    carService = new CarService();

    // Create the button and add it to the layout
    goToCarCatalogButton = new QPushButton("Go to Car Catalog", this);
    goToCarCatalogButton->setFixedSize(200, 50); // Adjust the size as needed

    connect(goToCarCatalogButton, &QPushButton::clicked, this, &TransmissionChart::goToCarCatalog);

    createChart();
    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    chartView->setMinimumSize(800, 600); // Adjust the minimum size as needed

    // Add the HeaderWidget, chartView, and back button to the layout
    mainLayout->addWidget(chartView);
    mainLayout->addStretch(1);
    mainLayout->addWidget(goToCarCatalogButton);

    setLayout(mainLayout);
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

    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

void TransmissionChart::goToCarCatalog() {
    CarCatalogPage *carCatalogPage = new CarCatalogPage(new QMainWindow);
    QMainWindow *parent = dynamic_cast<QMainWindow *>(this->parentWidget());
    parent->setCentralWidget(carCatalogPage);
    this->parentWidget()->show();
}
