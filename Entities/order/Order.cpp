#include "Order.h"

#include <utility>

Order::Order() {}

Order::Order(const QString &id, const tm &startDate, const tm &endDate, const QString &carId, const QString &clientId,
             double price) : id(id), startDate(startDate), endDate(endDate), carId(carId), clientId(clientId),
                             price(price) {}

const QString &Order::getId() const {
    return this->id;
}

void Order::setId(const QString &id) {
    Order::id = id;
}

const tm &Order::getStartDate() const {
    return startDate;
}

void Order::setStartDate(const tm &startDate) {
    Order::startDate = startDate;
}

const tm &Order::getEndDate() const {
    return endDate;
}

void Order::setEndDate(const tm &endDate) {
    Order::endDate = endDate;
}

const QString &Order::getCarId() const {
    return carId;
}

void Order::setCarId(const QString &carId) {
    Order::carId = carId;
}

const QString &Order::getClientId() const {
    return clientId;
}

void Order::setClientId(const QString &clientId) {
    Order::clientId = clientId;
}

double Order::getPrice() const {
    return price;
}

void Order::setPrice(double price) {
    Order::price = price;
}

