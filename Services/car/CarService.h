#ifndef  CARSERVICE_H
#define CARSERVICE_H


#include "../../Entities/car/Car.h"
#include <vector>
#include "sstream"
#include "../../serializers/car/CarSerializer.h"

using namespace std;

class CarService {
private:
    string path = "/Users/noriksaroyan/CLionProjects/CarService/database/cars.txt";
    CarSerializer serializer;
public:
    void insertCar(Car &car);

    void editCar(Car &car);

    void deleteCar(Car &car);

    vector<Car> getAllCars(); ;

    Car getCarById(string id);

    vector<Car> findAllByBrand(QString brand);

    vector<Car> findAllByModel(QString brand);

    vector<Car> findAllByVolume(QString brand);

};

#endif


