#ifndef CARCATALOGPAGE_H
#define CARCATALOGPAGE_H

#include <QtWidgets>
#include "../../../Entities/car/Car.h"
#include "iostream"
#include "../../../Services/car/CarService.h"
#include "../../orders/orderpage.h"

class CarCatalogPage : public QMainWindow {
    Q_OBJECT

public:
    CarCatalogPage(QWidget *parent = nullptr);

private slots:
    void showCarDetails(const Car &car);

    void showOrdersPage();

    void showCarCatalogPage();

    void showAddCarDialog();

private:
    CarService service;

    QWidget *createCarCard(const Car &car);

    void resizeEvent(QResizeEvent *event);
};

#endif // CARCATALOGPAGE_H
