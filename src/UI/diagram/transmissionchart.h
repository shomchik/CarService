#ifndef TRANSMISSIONCHART_H
#define TRANSMISSIONCHART_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

#include "../../Services/order/OrderService.h"
#include "../../Services/car/CarService.h"
class QPushButton;

class TransmissionChart : public QWidget {
    Q_OBJECT

public:
    explicit TransmissionChart(QWidget *parent = nullptr);

public slots:
    void goToCarCatalog();

private:
    void createChart();

    QPushButton *goToCarCatalogButton;
    OrderService *orderService;
    CarService *carService;
    QChartView *chartView;
};

#endif // TRANSMISSIONCHART_H
