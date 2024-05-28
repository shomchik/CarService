#ifndef CARCATALOGPAGE_H
#define CARCATALOGPAGE_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include "../../../Services/car/CarService.h"
#include "../../../Entities/car/Car.h"
#include "../../../serializers/car/CarSerializer.h"
#include "../add/qaddcardialog.h"
#include "../reservationDialog/qcarreservationdialog.h"
#include "../../orders/orderpage.h"
#include "../../static/header/headerwidget.h"
#include "QResizeEvent"

class CarCatalogPage : public QMainWindow {
    Q_OBJECT

public:
    explicit CarCatalogPage(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void showAddCarDialog();

    void showCarDetails(const Car &car);

    void showOrdersPage();

    void showCarCatalogPage();

    void showCarDetailsFromSearch(const QString &result);

private:
    CarService service;
    QWidget *catalogWidget;
    QVBoxLayout *catalogLayout;
    HeaderWidget *header;

    void populateCarCatalog();

    void clearCarCatalog();

    QWidget *createCarCard(const Car &car);
};

#endif // CARCATALOGPAGE_H
