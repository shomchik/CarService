//
// Created by Norik Saroyan on 17.04.24.
//

#ifndef UNTITLED4_CARMAPPER_H
#define UNTITLED4_CARMAPPER_H

#include "string"
#include "../../Entities/car/Car.h"

using namespace std;

class CarMapper {
public:

    string mapObjectToString(const Car &car);
    Car mapStringToObject(const string &data);

};


#endif //UNTITLED4_CARMAPPER_H
