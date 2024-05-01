#ifndef ORDERSERVICE_H
#define ORDERSERVICE_H

#include <vector>
#include <string>
#include <ctime>
#include "../../Entities/order/Order.h"
#include "../../../utils/TimeHelper.h"

using namespace std;

class OrderService {
private:
    vector<Order> orders;
public:
    OrderService();

    void createOrder(const Order &order);

    Order getOrder(const string &orderId) const;

    void editOrder(const string &orderId, const Order &order);

    vector<Order> getAllOrders() const;

    vector<Order> findOrdersByClientId(const string &clientId) const;

    Order findOrderByOrderId(const string &orderId) const;

    vector<Order> findOrdersByCarId(const string &carId) const;

    vector<Order> findOrdersByStartDate(const tm &startDate) const;

    vector<Order> findOrdersByEndDate(const tm &endDate) const;

    Order findOrderByClientId(const string &clientId) const;

    Order findOrderByCarId(const string &carId) const;

    Order findOrderByStartDate(const tm &startDate) const;

    Order findOrderByEndDate(const tm &endDate) const;
};

#endif // ORDERSERVICE_H
