#include "OrderService.h"
#include <algorithm>
using namespace std;

namespace OrderMapper {
    std::string serialize(const Order& order) {
        std::ostringstream oss;
        oss << order.getId() << ',' << order.getStartDate().time_since_epoch().count() << ','
            << order.getEndDate().time_since_epoch().count() << ',' << order.getCarId() << ','
            << order.getClientId() << ',' << order.getPrice();
        return oss.str();
    }

    Order deserialize(const std::string& str) {
        std::istringstream iss(str);
        std::string id, carId, clientId;
        long long startEpoch, endEpoch;
        double price;
        char comma;

        iss >> id >> comma >> startEpoch >> comma >> endEpoch >> comma
            >> carId >> comma >> clientId >> comma >> price;

        return Order(id, std::chrono::system_clock::time_point(std::chrono::seconds(startEpoch)),
                     std::chrono::system_clock::time_point(std::chrono::seconds(endEpoch)), carId, clientId, price);
    }
}
void OrderService::addOrder(const Order &order) {
    orders.push_back(order);
}

void OrderService::editOrder(const std::string &orderId, const Order &newOrder) {
    auto it = std::find_if(orders.begin(), orders.end(), [&](const Order &order) {
        return order.getId() == orderId;
    });
    if (it != orders.end()) {
        *it = newOrder;
    }
}

void OrderService::deleteOrder(const std::string &orderId) {
    orders.erase(std::remove_if(orders.begin(), orders.end(), [&](const Order &order) {
        return order.getId() == orderId;
    }), orders.end());
}

void OrderService::displayAllOrders() const {
    std::cout << "List of all orders:\n";
    for (const auto& order : orders) {
        std::cout << "Order ID: " << order.getId() << "\n";
        std::cout << "Start Date: " << std::chrono::system_clock::to_time_t(order.getStartDate()) << "\n";
        std::cout << "End Date: " << std::chrono::system_clock::to_time_t(order.getEndDate()) << "\n";
        std::cout << "Car ID: " << order.getCarId() << "\n";
        std::cout << "Client ID: " << order.getClientId() << "\n";
        std::cout << "Price: " << order.getPrice() << "\n\n";
    }
}
Order *OrderService::findOrderByOrderId(const std::string &orderId) {
    auto it = std::find_if(orders.begin(), orders.end(), [&](const Order &order) {
        return order.getId() == orderId;
    });
    return it != orders.end() ? &(*it) : nullptr;
}

std::vector<Order> OrderService::findOrdersByUserId(const std::string &userId) const {
    std::vector<Order> result;
    for (const auto &order: orders) {
        if (order.getClientId() == userId) {
            result.push_back(order);
        }
    }
    return result;
}

std::vector<Order> OrderService::findOrdersByCarId(const std::string &carId) const {
    std::vector<Order> result;
    for (const auto &order: orders) {
        if (order.getCarId() == carId) {
            result.push_back(order);
        }
    }
    return result;
}

std::vector<Order> OrderService::findOrdersByStartDate(const std::chrono::system_clock::time_point &startDate) const {
    std::vector<Order> result;
    for (const auto &order: orders) {
        if (order.getStartDate() == startDate) {
            result.push_back(order);
        }
    }
    return result;
}

std::vector<Order> OrderService::findOrdersByEndDate(const std::chrono::system_clock::time_point &endDate) const {
    std::vector<Order> result;
    for (const auto &order: orders) {
        if (order.getEndDate() == endDate) {
            result.push_back(order);
        }
    }
    return result;
}

void OrderService::retrieveOrderData(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    orders.clear();

    std::string line;
    while (std::getline(file, line)) {
        orders.push_back(OrderMapper::deserialize(line));
    }

    file.close();
}

void OrderService::saveOrderData(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing" << std::endl;
        return;
    }

    for (const auto& order : orders) {
        file << OrderMapper::serialize(order) << '\n';
    }

    file.close();
}
