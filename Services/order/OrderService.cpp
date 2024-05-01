#include "OrderService.h"
#include "../../utils/TimeHelper.h"


OrderService::OrderService() {}

void OrderService::createOrder(const Order &order) {
    orders.push_back(order);
}

Order OrderService::getOrder(const string &orderId) const {
    for (const auto &order: orders) {
        if (order.getId().toStdString() == orderId) {
            return order;
        }
    }
    return Order();
}

void OrderService::editOrder(const string &orderId, const Order &newOrder) {
    for (auto &order: orders) {
        if (order.getId().toStdString() == orderId) {
            order = newOrder;
            break;
        }
    }
}

vector<Order> OrderService::getAllOrders() const {
    return orders;
}

vector<Order> OrderService::findOrdersByClientId(const string &clientId) const {
    vector<Order> foundOrders;
    for (const auto &order: orders) {
        if (order.getClientId().toStdString() == clientId) {
            foundOrders.push_back(order);
        }
    }
    return foundOrders;
}

Order OrderService::findOrderByOrderId(const string &orderId) const {
    for (const auto &order: orders) {
        if (order.getId().toStdString() == orderId) {
            return order;
        }
    }
    return Order();
}

vector<Order> OrderService::findOrdersByCarId(const string &carId) const {
    vector<Order> foundOrders;
    for (const auto &order: orders) {
        if (order.getCarId().toStdString() == carId) {
            foundOrders.push_back(order);
        }
    }
    return foundOrders;
}

vector<Order> OrderService::findOrdersByStartDate(const tm &startDate) const {
    vector<Order> foundOrders;
    for (const auto &order: orders) {
        if (TimeHelper::compareDates(order.getStartDate(), startDate)) {
            foundOrders.push_back(order);
        }
    }
    return foundOrders;
}

vector<Order> OrderService::findOrdersByEndDate(const tm &endDate) const {
    vector<Order> foundOrders;
    for (const auto &order: orders) {
        if (TimeHelper::compareDates(order.getEndDate(), endDate)) {
            foundOrders.push_back(order);
        }
    }
    return foundOrders;
}

Order OrderService::findOrderByClientId(const string &clientId) const {
    for (const auto &order: orders) {
        if (order.getClientId().toStdString() == clientId) {
            return order;
        }
    }
    return Order();
}

Order OrderService::findOrderByCarId(const string &carId) const {
    for (const auto &order: orders) {
        if (order.getCarId().toStdString() == carId) {
            return order;
        }
    }
    return Order();
}

Order OrderService::findOrderByStartDate(const tm &startDate) const {
    for (const auto &order: orders) {
        if (TimeHelper::compareDates(order.getStartDate(), startDate)) {
            return order;
        }
    }
    return Order();
}

Order OrderService::findOrderByEndDate(const tm &endDate) const {
    for (const auto &order: orders) {
        if (TimeHelper::compareDates(order.getEndDate(), endDate)) {
            return order;
        }
    }
    return Order();
}

