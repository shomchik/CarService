#ifndef CARSERIALIZER_H
#define CARSERIALIZER_H

#include "../../Entities/car/Car.h"
#include <string>

class CarSerializer {
public:
    static std::string serialize(const Car &car);

    static Car deserialize(const std::string &data);

    static std::string bodyTypeToString(BodyType bodyType);

    static std::string transmissionToString(Transmission transmission);

    static BodyType stringToBodyType(const std::string &bodyTypeStr);

    static Transmission stringToTransmission(const std::string &transmissionStr);
};

#endif // CARSERIALIZER_H
