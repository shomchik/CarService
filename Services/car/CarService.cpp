#include "CarService.h"
#include <algorithm>
#include <fstream>

using namespace std;

#include "iostream"

void CarService::insertCar(Car &car) {
    std::string carData = CarSerializer::serialize(car);
    std::ofstream file(path, std::ios_base::app);
    file << carData;
    file.close();
}

void CarService::editCar(Car &car) {
    std::ifstream inFile(path);
    std::ofstream outFile("temp.txt");
    std::string line;
    while (std::getline(inFile, line)) {

        Car currentCar = CarSerializer::deserialize(line);
        if (currentCar.getId().toStdString() == car.getId().toStdString()) {
            outFile << CarSerializer::serialize(car) << std::endl;
        } else {
            outFile << line << std::endl;
        }
    }

    inFile.close();
    outFile.close();

    std::remove(path.c_str());
    std::rename("temp.txt", path.c_str());
}

void CarService::deleteCar(Car &car) {
    std::ifstream inFile(path);
    std::ofstream outFile("temp.txt");
    std::string line;

    while (std::getline(inFile, line)) {
        Car currentCar = CarSerializer::deserialize(line);
        if (currentCar.getId().toStdString() != car.getId().toStdString()) {
            outFile << line << std::endl;
        }
    }

    inFile.close();
    outFile.close();

    std::remove(path.c_str());
    std::rename("temp.txt", path.c_str());
}

vector<Car> CarService::getAllCars() {
    vector<Car> cars;
    std::ifstream file(path);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            Car car = CarSerializer::deserialize(line);
            cars.push_back(car);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << path << std::endl;
    }
    return cars;
}

Car CarService::getCarById(string id) {
    Car car;
    std::ifstream file(path);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            Car currentCar = CarSerializer::deserialize(line);
            if (currentCar.getId().toStdString() == id) {
                car = currentCar;
                break;
            }
        }
        file.close();
    }
    return car;
}

vector<Car> CarService::findAllByBrand(QString brand) {
    vector<Car> cars;
    std::ifstream file(path);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            Car car = CarSerializer::deserialize(line);
            if (car.getBrand() == brand) {
                cars.push_back(car);
            }
        }
        file.close();
    }
    return cars;
}

vector<Car> CarService::findAllByModel(QString model) {
    vector<Car> cars;
    std::ifstream file(path);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            Car car = CarSerializer::deserialize(line);
            if (car.getModel() == model) {
                cars.push_back(car);
            }
        }
        file.close();
    }
    return cars;
}

vector<Car> CarService::findAllByVolume(QString volume) {
    vector<Car> cars;
    std::ifstream file(path);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            Car car = CarSerializer::deserialize(line);
            if (car.getVolume() == volume) {
                cars.push_back(car);
            }
        }
        file.close();
    }
    return cars;
}
