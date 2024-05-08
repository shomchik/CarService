#include "CarSerializer.h"
#include <iostream>
#include <sstream>
#include <iomanip>

std::string CarSerializer::serialize(const Car &car) {
    std::ostringstream oss;
    oss << "ID:" << car.getId().toStdString() << ",";
    oss << "Brand:" << car.getBrand().toStdString() << ",";
    oss << "Model:" << car.getModel().toStdString() << ",";
    oss << "Volume:" << car.getVolume().toStdString() << ",";
    oss << "BodyType:" << bodyTypeToString(car.getBodyType()) << ",";
    oss << "Transmission:" << transmissionToString(car.getTransmission()) << ",";
    oss << "Rate:" << std::fixed << std::setprecision(2) << car.getRate() << ",";
    oss << "HasCarSeat:" << (car.isHasCarSeat() ? "true" : "false") << "\n";
    return oss.str();
}

Car CarSerializer::deserialize(const std::string &data) {
    std::istringstream iss(data);
    std::string idStr, brandStr, modelStr, volumeStr, bodyTypeStr, transmissionStr, rateStr, hasCarSeatStr;

    std::getline(iss, idStr, ',');
    std::getline(iss, brandStr, ',');
    std::getline(iss, modelStr, ',');
    std::getline(iss, volumeStr, ',');
    std::getline(iss, bodyTypeStr, ',');
    std::getline(iss, transmissionStr, ',');
    std::getline(iss, rateStr, ',');
    std::getline(iss, hasCarSeatStr);

    QString id = QString::fromStdString(idStr.substr(3));
    QString brand = QString::fromStdString(brandStr.substr(6));
    QString model = QString::fromStdString(modelStr.substr(6));
    QString volume = QString::fromStdString(volumeStr.substr(7));
    BodyType bodyType = stringToBodyType(bodyTypeStr.substr(9));
    Transmission transmission = stringToTransmission(transmissionStr.substr(12));
    double rate = std::stod(rateStr.substr(5));
    bool hasCarSeat = (hasCarSeatStr.substr(10) == "true");

    return Car(id, brand, model, volume, bodyType, transmission, hasCarSeat, rate);
}

std::string CarSerializer::bodyTypeToString(BodyType bodyType) {
    switch (bodyType) {
        case SEDAN:
            return "SEDAN";
        case COUPE:
            return "COUPE";
        case HATCHBACK:
            return "HATCHBACK";
        case CONVERTIBLE:
            return "CONVERTIBLE";
        case SUV:
            return "SUV";
        case TRUCK:
            return "TRUCK";
        case VAN:
            return "VAN";
        default:
            return "UNKNOWN";
    }
}

std::string CarSerializer::transmissionToString(Transmission transmission) {
    switch (transmission) {
        case MANUAL:
            return "MANUAL";
        case AUTOMATIC:
            return "AUTOMATIC";
        case VARIATOR:
            return "VARIATOR";
        default:
            return "UNKNOWN";
    }
}

BodyType CarSerializer::stringToBodyType(const std::string &bodyTypeStr) {
    if (bodyTypeStr == "SEDAN") return SEDAN;
    if (bodyTypeStr == "COUPE") return COUPE;
    if (bodyTypeStr == "HATCHBACK") return HATCHBACK;
    if (bodyTypeStr == "CONVERTIBLE") return CONVERTIBLE;
    if (bodyTypeStr == "SUV") return SUV;
    if (bodyTypeStr == "TRUCK") return TRUCK;
    if (bodyTypeStr == "VAN") return VAN;
    return UNKNOWN_BODY_TYPE;
}

Transmission CarSerializer::stringToTransmission(const std::string &transmissionStr) {
    if (transmissionStr == "MANUAL") return MANUAL;
    if (transmissionStr == "AUTOMATIC") return AUTOMATIC;
    if (transmissionStr == "VARIATOR") return VARIATOR;
    return UNKNOWN_TRANSMISSION;
}
