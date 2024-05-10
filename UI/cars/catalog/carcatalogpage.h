#ifndef CARCATALOGPAGE_H
#define CARCATALOGPAGE_H

#include <QtWidgets>
#include "../../../Entities/car/Car.h"
#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollBar>
#include "iostream"
#include "../../static/header/headerwidget.h"
#include "../reservationDialog/qcarreservationdialog.h"
#include "../../../Services/car/CarService.h"
#include "../../orders/orderpage.h"
#include "../../static/header/headerwidget.h"

class CarCatalogPage : public QMainWindow {
Q_OBJECT
public:
    CarCatalogPage(QWidget *parent = nullptr);

private slots:
    void showCarDetails(const Car &car);
    void showOrdersPage();

private:
    CarService service;
    QWidget *createCarCard(const Car &car);
    void resizeEvent(QResizeEvent *event);
};

#endif // CARCATALOGPAGE_H


