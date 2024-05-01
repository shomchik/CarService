#include "OrderMapper.h"
#include "ostream"
#include "sstream"
#include "string"
#include <iomanip>

std::string mapOrderToString(const Order &order) {
    std::ostringstream oss;
    oss << "Order ID: " << order.getId().toStdString() << "\n";
    oss << "Start Date: " << std::put_time(&order.getStartDate(), "%H:%M %d/%m/%Y") << "\n";
    oss << "End Date: " << std::put_time(&order.getEndDate(), "%H:%M %d/%m/%Y") << "\n";
    oss << "Car ID: " << order.getCarId().toStdString() << "\n";
    oss << "Client ID: " << order.getClientId().toStdString() << "\n";
    oss << "Price: " << order.getPrice() << "\n";

    return oss.str();
}

Order mapStringToOrder(const std::string &data) {
    std::istringstream iss(data);
    std::string id, startDateStr, endDateStr, carId, clientId, priceStr;

    iss >> id >> startDateStr >> endDateStr >> carId >> clientId >> priceStr;

    std::tm startDate = {};
    std::tm endDate = {};

    std::istringstream startDateStream(startDateStr);
    startDateStream >> std::get_time(&startDate, "%H:%M %d/%m/%Y");

    std::istringstream endDateStream(endDateStr);
    endDateStream >> std::get_time(&endDate, "%H:%M %d/%m/%Y");

    double price = std::stod(priceStr);

    Order order(QString::fromStdString(id), startDate, endDate, QString::fromStdString(carId),
                QString::fromStdString(clientId),
                price);

    return order;
}
