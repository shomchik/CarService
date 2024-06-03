//
// Created by Norik Saroyan on 03.06.24.
//

#ifndef CARSERVICETEST_H
#define CARSERVICETEST_H

#include "Entities/car/Car.h"
#include <sstream>

class MockCarSerializer {
public:
    static std::string serialize(const Car &car) {
        std::ostringstream oss;
        oss << car.getId().toStdString() << ","
            << car.getBrand().toStdString() << ","
            << car.getModel().toStdString() << ","
            << car.getVolume().toStdString() << ","
            << static_cast<int>(car.getBodyType()) << ","
            << static_cast<int>(car.getTransmission()) << ","
            << car.getRate() << ","
            << car.getHasCarSeat();
        return oss.str();
    }

    static Car deserialize(const std::string &data) {
        std::istringstream iss(data);
        std::string id, brand, model, volume;
        int bodyTypeInt, transmissionInt;
        double rate;
        bool hasCarSeat;

        std::getline(iss, id, ',');
        std::getline(iss, brand, ',');
        std::getline(iss, model, ',');
        std::getline(iss, volume, ',');
        iss >> bodyTypeInt >> std::ws;
        iss.ignore(1);
        iss >> transmissionInt >> std::ws;
        iss.ignore(1);
        iss >> rate >> std::ws;
        iss.ignore(1);
        iss >> hasCarSeat;

        return Car(QString::fromStdString(id), QString::fromStdString(brand), QString::fromStdString(model),
                   QString::fromStdString(volume), static_cast<BodyType>(bodyTypeInt),
                   static_cast<Transmission>(transmissionInt), hasCarSeat, rate);
    }

};


#endif //CARSERVICETEST_H
