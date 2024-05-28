#include "OrderMapper.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>

string OrderMapper::mapOrderToString(const Order &order) {
    ostringstream oss;
    oss << order.getId().toStdString() << "|"
            << put_time(&order.getStartDate(), "%H:%M %d/%m/%Y") << "|"
            << put_time(&order.getEndDate(), "%H:%M %d/%m/%Y") << "|"
            << order.getCarId().toStdString() << "|"
            << order.getClientId().toStdString() << "|"
            << order.getPrice();
    return oss.str();
}

Order OrderMapper::mapStringToOrder(const string &data) {
    istringstream iss(data);
    string id, startDateStr, endDateStr, carId, clientId, priceStr;

    if (!getline(iss, id, '|') ||
        !getline(iss, startDateStr, '|') ||
        !getline(iss, endDateStr, '|') ||
        !getline(iss, carId, '|') ||
        !getline(iss, clientId, '|') ||
        !getline(iss, priceStr, '|')) {
        throw invalid_argument("Invalid order data format");
    }

    tm startDate = {};
    tm endDate = {};
    istringstream(startDateStr) >> get_time(&startDate, "%H:%M %d/%m/%Y");
    istringstream(endDateStr) >> get_time(&endDate, "%H:%M %d/%m/%Y");
    double price = stod(priceStr);

    return {
        QString::fromStdString(id), startDate, endDate, QString::fromStdString(carId),
        QString::fromStdString(clientId), price
    };
}
