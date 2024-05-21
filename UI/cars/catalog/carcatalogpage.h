#ifndef CARCATALOGPAGE_H
#define CARCATALOGPAGE_H

#include <QMainWindow>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDialog>
#include <QResizeEvent>
#include "../../../Entities/car/Car.h"
#include "../../../Services/car/CarService.h"
#include "../../orders/orderpage.h"
#include "../add/qaddcardialog.h"
#include "../reservationDialog/qcarreservationdialog.h"
#include "../../static/header/headerwidget.h"

class CarCatalogPage : public QMainWindow {
    Q_OBJECT

public:
    CarCatalogPage(QWidget *parent = nullptr);

private slots:
    void showCarDetails(const Car &car);

    void showOrdersPage();

    void showCarCatalogPage();

    void showAddCarDialog();

    void showCarDetailsFromSearch(const QString &result);

private:
    CarService service;

    QWidget *createCarCard(const Car &car);

    void resizeEvent(QResizeEvent *event);
};

#endif // CARCATALOGPAGE_H
