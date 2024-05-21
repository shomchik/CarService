#include "OrderMapper.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <iostream>  // For debugging

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
    std::tm startDate = {};
    std::tm endDate = {};
    double price;

    // Helper lambda to get the next field
    auto getNextField = [&iss](std::string &field) {
        if (!std::getline(iss, field, '|')) {
            throw std::invalid_argument("Failed to parse order data");
        }
    };

    getNextField(id);
    getNextField(startDateStr);
    getNextField(endDateStr);
    getNextField(carId);
    getNextField(clientId);
    getNextField(priceStr);

    std::istringstream startDateStream(startDateStr);
    startDateStream >> std::get_time(&startDate, "%H:%M %d/%m/%Y");
    if (startDateStream.fail()) {
        throw std::invalid_argument("Failed to parse start date");
    }

    // Parse end date
    std::istringstream endDateStream(endDateStr);
    endDateStream >> std::get_time(&endDate, "%H:%M %d/%m/%Y");
    if (endDateStream.fail()) {
        throw std::invalid_argument("Failed to parse end date");
    }

    // Parse price
    try {
        price = std::stod(priceStr);
    } catch (const std::invalid_argument &e) {
        throw std::invalid_argument("Failed to parse price");
    } catch (const std::out_of_range &e) {
        throw std::out_of_range("Price out of range");
    }

    return Order(QString::fromStdString(id), startDate, endDate, QString::fromStdString(carId),
                 QString::fromStdString(clientId), price);
}
