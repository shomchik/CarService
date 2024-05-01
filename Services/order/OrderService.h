#include <vector>
#include <fstream>
#include <iostream>
#include "sstream"
#include "../../Entities/order/Order.h"


class OrderService {
private:
    std::vector<Order> orders;

public:
    void addOrder(const Order& order);

    void editOrder(const std::string& orderId, const Order& newOrder);

    void deleteOrder(const std::string& orderId);

    void displayAllOrders() const;

    Order* findOrderByOrderId(const std::string& orderId);

    std::vector<Order> findOrdersByUserId(const std::string& userId) const;

    std::vector<Order> findOrdersByCarId(const std::string& carId) const;

    std::vector<Order> findOrdersByStartDate(const std::chrono::system_clock::time_point& startDate) const;

    std::vector<Order> findOrdersByEndDate(const std::chrono::system_clock::time_point& endDate) const;

    void retrieveOrderData(const std::string& filename);

    void saveOrderData(const std::string& filename) const;
};

// Implementation of functions goes here...
