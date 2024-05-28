#include "OrderService.h"
#include "../../serializers/order/OrderMapper.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "../../utils/TimeHelper.h"

void OrderService::createOrder(const Order &order) {
    string orderData = OrderMapper::mapOrderToString(order);
    ofstream file(this->path, ios_base::app);
    file << orderData << endl;
    file.close();
}

Order OrderService::getOrder(const string &orderId) const {
    ifstream file(this->path);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Order currentOrder = OrderMapper::mapStringToOrder(line);
            if (currentOrder.getId().toStdString() == orderId) {
                file.close();
                return currentOrder;
            }
        }
        file.close();
    }
    return Order();
}

void OrderService::editOrder(const string &orderId, const Order &newOrder) {
    ifstream inFile(this->path);
    ofstream outFile("temp.txt");
    string line;

    while (getline(inFile, line)) {
        Order currentOrder = OrderMapper::mapStringToOrder(line);
        if (currentOrder.getId().toStdString() == orderId) {
            outFile << OrderMapper::mapOrderToString(newOrder) << endl;
        } else {
            outFile << line << endl;
        }
    }

    inFile.close();
    outFile.close();

    remove(this->path.c_str());
    rename("temp.txt", this->path.c_str());
}

vector<Order> OrderService::getAllOrders() const {
    vector<Order> orders;
    ifstream file(this->path);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Order order = OrderMapper::mapStringToOrder(line);
            orders.push_back(order);
        }
        file.close();
    } else {
        cerr << "Unable to open file: " << this->path << endl;
    }
    return orders;
}

vector<Order> OrderService::findOrdersByClientId(const string &clientId) const {
    vector<Order> orders;
    ifstream file(this->path);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Order order = OrderMapper::mapStringToOrder(line);
            if (order.getClientId().toStdString() == clientId) {
                orders.push_back(order);
            }
        }
        file.close();
    }
    return orders;
}

vector<Order> OrderService::findOrdersByCarId(const string &carId) const {
    vector<Order> orders;
    ifstream file(this->path);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Order order = OrderMapper::mapStringToOrder(line);
            if (order.getCarId().toStdString() == carId) {
                orders.push_back(order);
            }
        }
        file.close();
    }
    return orders;
}

vector<Order> OrderService::findOrdersByStartDate(const tm &startDate) const {
    vector<Order> orders;
    ifstream file(this->path);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Order order = OrderMapper::mapStringToOrder(line);
            if (TimeHelper::compareDates(order.getStartDate(), startDate)) {
                orders.push_back(order);
            }
        }
        file.close();
    }
    return orders;
}

vector<Order> OrderService::findOrdersByEndDate(const tm &endDate) const {
    vector<Order> orders;
    ifstream file(this->path);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Order order = OrderMapper::mapStringToOrder(line);
            if (TimeHelper::compareDates(order.getEndDate(), endDate)) {
                orders.push_back(order);
            }
        }
        file.close();
    }
    return orders;
}

Order OrderService::findOrderByClientId(const string &clientId) const {
    ifstream file(this->path);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Order order = OrderMapper::mapStringToOrder(line);
            if (order.getClientId().toStdString() == clientId) {
                file.close();
                return order;
            }
        }
        file.close();
    }
    return Order();
}

Order OrderService::findOrderByCarId(const string &carId) const {
    ifstream file(this->path);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Order order = OrderMapper::mapStringToOrder(line);
            if (order.getCarId().toStdString() == carId) {
                file.close();
                return order;
            }
        }
        file.close();
    }
    return Order();
}

Order OrderService::findOrderByStartDate(const tm &startDate) const {
    ifstream file(this->path);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Order order = OrderMapper::mapStringToOrder(line);
            if (TimeHelper::compareDates(order.getStartDate(), startDate)) {
                file.close();
                return order;
            }
        }
        file.close();
    }
    return Order();
}

Order OrderService::findOrderByEndDate(const tm &endDate) const {
    ifstream file(this->path);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Order order = OrderMapper::mapStringToOrder(line);
            if (TimeHelper::compareDates(order.getEndDate(), endDate)) {
                file.close();
                return order;
            }
        }
        file.close();
    }
    return Order();
}

void OrderService::deleteOrder(const string &orderId) {
    ifstream inFile(this->path);
    ofstream outFile("temp.txt");
    string line;

    while (getline(inFile, line)) {
        Order currentOrder = OrderMapper::mapStringToOrder(line);
        if (currentOrder.getId().toStdString() != orderId) {
            outFile << line << endl;
        }
    }

    inFile.close();
    outFile.close();

    remove(this->path.c_str());
    rename("temp.txt", this->path.c_str());
}

vector<Order> OrderService::findOrdersByPriceRange(double low, double high) {
    std::vector<Order> orders;
    std::ifstream file(this->path);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            Order order = OrderMapper::mapStringToOrder(line);
            if (order.getPrice() >= low && order.getPrice() <= high) {
                orders.push_back(order);
            }
        }
        file.close();
    }
    return orders;
}


std::vector<std::pair<QDate, QDate> > OrderService::getOccupiedDatesForCar(const QString &carId) const {
    std::vector<std::pair<QDate, QDate> > occupiedDates;
    std::ifstream inFile(this->path);
    if (!inFile.is_open()) {
        throw std::runtime_error("Failed to open orders file for reading.");
    }

    std::string line;
    while (std::getline(inFile, line)) {
        Order order = OrderMapper::mapStringToOrder(line);
        if (order.getCarId() == carId) {
            QDate startDate = TimeHelper::tmToQDate(order.getStartDate());
            QDate endDate = TimeHelper::tmToQDate(order.getEndDate());

            if (!startDate.isValid() || !endDate.isValid()) {
                throw std::runtime_error("Invalid date format in order data.");
            }

            occupiedDates.push_back(std::make_pair(startDate, endDate));
        }
    }

    inFile.close();
    return occupiedDates;
}
std::vector<Order> OrderService::findOrdersByDateRange(const tm &startDate, const tm &endDate) const {
    std::vector<Order> ordersInRange;

    auto ordersStartingOnOrAfterStart = findOrdersByStartDate(startDate);
    auto ordersEndingOnOrBeforeEnd = findOrdersByEndDate(endDate);
    for (const auto &order : ordersStartingOnOrAfterStart) {
        if (TimeHelper::compareDates(order.getEndDate(), endDate) || TimeHelper::compareDates(order.getEndDate(), startDate)) {
            ordersInRange.push_back(order);
        }
    }

    for (const auto &order : ordersEndingOnOrBeforeEnd) {
        if (TimeHelper::compareDates(order.getStartDate(), startDate) || TimeHelper::compareDates(order.getStartDate(), endDate)) {
            ordersInRange.push_back(order);
        }
    }

    return ordersInRange;
}

