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
#include <QVBoxLayout>
#include "../reservationDialog/qcarreservationdialog.h"
#include "../../../Services/car/CarService.h"

class CarCatalogPage : public QMainWindow {
Q_OBJECT
public:
    CarCatalogPage(QWidget *parent = nullptr);

private slots:

    void showCarDetails(const Car &car);

private:
    CarService service;
    QWidget *createCarCard(const Car &car);
    void resizeEvent(QResizeEvent *event);
};

#endif // CARCATALOGPAGE_H
