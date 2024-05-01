#ifndef CARCATALOGPAGE_H
#define CARCATALOGPAGE_H

#include <QtWidgets>
#include "../../Entities/car/Car.h"

class CarCatalogPage : public QMainWindow {
Q_OBJECT
public:
    CarCatalogPage(QWidget *parent = nullptr);

private slots:

    void showCarDetails(const Car &car);

private:
    QWidget *createCarCard(const Car &car);
    void resizeEvent(QResizeEvent *event);
};

#endif // CARCATALOGPAGE_H
