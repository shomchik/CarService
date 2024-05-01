#ifndef OP_PROJ_CONSOLE_ORDER_H
#define OP_PROJ_CONSOLE_ORDER_H


#include "QString"
#include "../car/Car.h"
#include "ctime"
#include "chrono"

class Order {
private:
    QString id;
    tm startDate{};
    tm endDate{};
    QString carId;
    QString clientId;
    double price{};
public:
    Order();

    Order(const QString &id, const tm &startDate, const tm &endDate, const QString &carId, const QString &clientId,
          double price);

    const QString &getId() const;

    void setId(const QString &id);

    const tm &getStartDate() const;

    void setStartDate(const tm &startDate);

    const tm &getEndDate() const;

    void setEndDate(const tm &endDate);

    const QString &getCarId() const;

    void setCarId(const QString &carId);

    const QString &getClientId() const;

    void setClientId(const QString &clientId);

    double getPrice() const;

    void setPrice(double price);
};


#endif //OP_PROJ_CONSOLE_ORDER_H
