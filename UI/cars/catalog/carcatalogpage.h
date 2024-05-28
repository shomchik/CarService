#ifndef CARCATALOGPAGE_H
#define CARCATALOGPAGE_H

#include <QMainWindow>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QResizeEvent>

#include "../../../Services/car/CarService.h"
#include "../../../Entities/car/Car.h"
#include "../../static/header/headerwidget.h"
#include "../../orders/orderpage.h"
#include "../../cars/add/qaddcardialog.h"
#include "../../cars/reservationDialog/qcarreservationdialog.h"

class CarCatalogPage : public QMainWindow {
    Q_OBJECT

public:
    explicit CarCatalogPage(QWidget *parent = nullptr);

public slots:
    void showAddCarDialog();

    void showOrdersPage();

    void showCarCatalogPage();

    void showCarDetailsFromSearch(const QString &result);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    CarService service;

    QWidget *createCarCard(const Car &car);

    void showCarDetails(const Car &car);
};

#endif // CARCATALOGPAGE_H
