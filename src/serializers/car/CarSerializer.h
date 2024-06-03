#ifndef CARSERIALIZER_H
#define CARSERIALIZER_H

#include "../../Entities/car/Car.h"
#include <string>

class CarSerializer {
public:
    static string serialize(const Car &car);

    static Car deserialize(const string &data);

    static string bodyTypeToString(BodyType bodyType);

    static string transmissionToString(Transmission transmission);

    static BodyType stringToBodyType(const string &bodyTypeStr);

    static Transmission stringToTransmission(const string &transmissionStr);
};

#endif // CARSERIALIZER_H
