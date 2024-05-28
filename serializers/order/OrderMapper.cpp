#include "OrderMapper.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>

std::string OrderMapper::mapOrderToString(const Order &order) {
    std::ostringstream oss;
    oss << order.getId().toStdString() << "|"
            << std::put_time(&order.getStartDate(), "%H:%M %d/%m/%Y") << "|"
            << std::put_time(&order.getEndDate(), "%H:%M %d/%m/%Y") << "|"
            << order.getCarId().toStdString() << "|"
            << order.getClientId().toStdString() << "|"
            << order.getPrice();
    return oss.str();
}

Order OrderMapper::mapStringToOrder(const std::string &data) {
    std::istringstream iss(data);
    std::string id, startDateStr, endDateStr, carId, clientId, priceStr;

    if (!std::getline(iss, id, '|') ||
        !std::getline(iss, startDateStr, '|') ||
        !std::getline(iss, endDateStr, '|') ||
        !std::getline(iss, carId, '|') ||
        !std::getline(iss, clientId, '|') ||
        !std::getline(iss, priceStr, '|')) {
        throw std::invalid_argument("Invalid order data format");
    }

    std::tm startDate = {};
    std::tm endDate = {};
    std::istringstream(startDateStr) >> std::get_time(&startDate, "%H:%M %d/%m/%Y");
    std::istringstream(endDateStr) >> std::get_time(&endDate, "%H:%M %d/%m/%Y");
    double price = std::stod(priceStr);

    return {
        QString::fromStdString(id), startDate, endDate, QString::fromStdString(carId),
        QString::fromStdString(clientId), price
    };
}
