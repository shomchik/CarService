#include "CarMapper.h"
#include <sstream>

string CarMapper::mapObjectToString(Car &car) {
    string result = "Car ID: " + string(car.getId().toStdString()) + "\n";
    result += "Brand: " + car.getBrand().toStdString() + "\n";
    result += "Model: " + car.getModel().toStdString() + "\n";
    result += "Volume: " + car.getVolume().toStdString() + "\n";
    result += "Body Type: " + to_string(car.getBodyType()) + "\n";
    result += "Transmission: " + string(toString(car.getTransmission())) + "\n";
    result += "Rate: " + to_string(car.getRate()) + "\n";
    result += "Has Car Seat: " + string((car.isHasCarSeat() ? "Yes" : "No")) + "\n";

    return result;
}

Car CarMapper::mapStringToObject(string &data) {
    std::istringstream iss(data);
    std::string id, brand, model, volume, bodyTypeStr, transmissionStr, rateStr, hasCarSeatStr;

    iss >> id >> brand >> model >> volume >> bodyTypeStr >> transmissionStr >> rateStr >> hasCarSeatStr;

    BodyType bodyType = SEDAN;
    if (bodyTypeStr == "SEDAN") {
        bodyType = SEDAN;
    } else if (bodyTypeStr == "COUPE") {
        bodyType = COUPE;
    } else if (bodyTypeStr == "HATCHBACK") {
        bodyType = HATCHBACK;
    } else if (bodyTypeStr == "CONVERTIBLE") {
        bodyType = CONVERTIBLE;
    } else if (bodyTypeStr == "SUV") {
        bodyType = SUV;
    } else if (bodyTypeStr == "TRUCK") {
        bodyType = TRUCK;
    } else if (bodyTypeStr == "VAN") {
        bodyType = VAN;
    }

    Transmission transmission = MANUAL;
    if (transmissionStr == "MANUAL") {
        transmission = MANUAL;
    } else if (transmissionStr == "AUTOMATIC") {
        transmission = AUTOMATIC;
    } else if (transmissionStr == "VARIATOR") {
        transmission = VARIATOR;
    }

    double rate = stod(rateStr);
    bool hasCarSeat = (hasCarSeatStr == "Yes");

    Car car(QString::fromStdString(id), QString::fromStdString(brand), QString::fromStdString(model),
            QString::fromStdString(volume), bodyType, transmission, hasCarSeat);

    return car;
}
