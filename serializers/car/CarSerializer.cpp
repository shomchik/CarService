#include "CarSerializer.h"

#include <iomanip>
#include <sstream>
#include "../../../Entities/car/BodyType.h"
#include "../../../Entities/car/Transmission.h"

string CarSerializer::serialize(const Car &car) {
    ostringstream oss;
    oss << "ID:" << car.getId().toStdString() << ",";
    oss << "Brand:" << car.getBrand().toStdString() << ",";
    oss << "Model:" << car.getModel().toStdString() << ",";
    oss << "Volume:" << car.getVolume().toStdString() << ",";
    oss << "BodyType:" << bodyTypeToString(car.getBodyType()) << ",";
    oss << "Transmission:" << transmissionToString(car.getTransmission()) << ",";
    oss << "Rate:" << fixed << setprecision(2) << car.getRate() << ",";
    oss << "HasCarSeat:" << (car.isHasCarSeat() ? "true" : "false") << ",";
    oss << "Path:" << car.getPath().toStdString() << "\n";
    return oss.str();
}

Car CarSerializer::deserialize(const string &data) {
    istringstream iss(data);
    string idStr, brandStr, modelStr, volumeStr, bodyTypeStr, transmissionStr, rateStr, hasCarSeatStr;

    getline(iss, idStr, ',');
    getline(iss, brandStr, ',');
    getline(iss, modelStr, ',');
    getline(iss, volumeStr, ',');
    getline(iss, bodyTypeStr, ',');
    getline(iss, transmissionStr, ',');
    getline(iss, rateStr, ',');
    getline(iss, hasCarSeatStr);

    QString id = QString::fromStdString(idStr.substr(3));
    QString brand = QString::fromStdString(brandStr.substr(6));
    QString model = QString::fromStdString(modelStr.substr(6));
    QString volume = QString::fromStdString(volumeStr.substr(7));
    BodyType bodyType = stringToBodyType(bodyTypeStr.substr(9));
    Transmission transmission = stringToTransmission(transmissionStr.substr(13));
    double rate = stod(rateStr.substr(5));
    bool hasCarSeat = (hasCarSeatStr.substr(10) == "true");

    return Car(id, brand, model, volume, bodyType, transmission, hasCarSeat, rate);
}

string CarSerializer::bodyTypeToString(BodyType bodyType) {
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

string CarSerializer::transmissionToString(Transmission transmission) {
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

BodyType CarSerializer::stringToBodyType(const string &bodyTypeStr) {
    if (bodyTypeStr == "SEDAN") return SEDAN;
    if (bodyTypeStr == "COUPE") return COUPE;
    if (bodyTypeStr == "HATCHBACK") return HATCHBACK;
    if (bodyTypeStr == "CONVERTIBLE") return CONVERTIBLE;
    if (bodyTypeStr == "SUV") return SUV;
    if (bodyTypeStr == "TRUCK") return TRUCK;
    if (bodyTypeStr == "VAN") return VAN;
    return UNKNOWN_BODY_TYPE;
}

Transmission CarSerializer::stringToTransmission(const string &transmissionStr) {
    if (transmissionStr == "MANUAL") return MANUAL;
    if (transmissionStr == "AUTOMATIC") return AUTOMATIC;
    if (transmissionStr == "VARIATOR") return VARIATOR;
    return UNKNOWN_TRANSMISSION;
}
