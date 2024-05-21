#ifndef ORDERSERVICE_H
#define ORDERSERVICE_H

#include <vector>
#include <string>
#include <ctime>
#include "../../Entities/order/Order.h"
#include "../../serializers/order/OrderMapper.h"
#include "QDate"
using namespace std;

class OrderService {
private:
    string path = "/Users/noriksaroyan/CLionProjects/CarService/database/orders.txt";
    OrderMapper mapper;

public:
    std::vector<std::pair<QDate, QDate> > getOccupiedDatesForCar(const QString &carId) const;

    void createOrder(const Order &order);

    Order getOrder(const string &orderId) const;

    void editOrder(const string &orderId, const Order &order);

    void deleteOrder(const string &orderId);

    vector<Order> getAllOrders() const;

    vector<Order> findOrdersByClientId(const string &clientId) const;

    Order findOrderByOrderId(const string &orderId) const;

    vector<Order> findOrdersByCarId(const string &carId) const;

    vector<Order> findOrdersByStartDate(const tm &startDate) const;

    vector<Order> findOrdersByEndDate(const tm &endDate) const;

    vector<Order> findOrdersByPriceRange(double low, double high);

    Order findOrderByClientId(const string &clientId) const;

    Order findOrderByCarId(const string &carId) const;

    Order findOrderByStartDate(const tm &startDate) const;

    Order findOrderByEndDate(const tm &endDate) const;
};

#endif // ORDERSERVICE_H
