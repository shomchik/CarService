#include "CarService.h"
#include <algorithm>
#include <fstream>

using namespace std;

#include "iostream"

void CarService::insertCar(Car &car) {
    string carData = CarSerializer::serialize(car);
    ofstream file(path, ios_base::app);
    file << carData;
    file.close();
}

void CarService::editCar(Car &car) {
    ifstream inFile(path);
    ofstream outFile("temp.txt");
    string line;
    while (getline(inFile, line)) {
        Car currentCar = CarSerializer::deserialize(line);
        if (currentCar.getId().toStdString() == car.getId().toStdString()) {
            outFile << CarSerializer::serialize(car) << endl;
        } else {
            outFile << line << endl;
        }
    }

    inFile.close();
    outFile.close();

    remove(path.c_str());
    rename("temp.txt", path.c_str());
}

void CarService::deleteCar(Car &car) {
    ifstream inFile(path);
    ofstream outFile("temp.txt");
    string line;

    while (getline(inFile, line)) {
        Car currentCar = CarSerializer::deserialize(line);
        if (currentCar.getId().toStdString() != car.getId().toStdString()) {
            outFile << line << endl;
        }
    }

    inFile.close();
    outFile.close();

    remove(path.c_str());
    rename("temp.txt", path.c_str());
}

vector<Car> CarService::getAllCars() {
    vector<Car> cars;
    ifstream file(path);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Car car = CarSerializer::deserialize(line);
            cars.push_back(car);
        }
        file.close();
    } else {
        cerr << "Unable to open file: " << path << endl;
    }
    return cars;
}

optional<Car> CarService::getCarById(string id) {
    Car car;
    ifstream file(path);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
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
    ifstream file(path);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
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
    ifstream file(path);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
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
    ifstream file(path);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Car car = CarSerializer::deserialize(line);
            if (car.getVolume() == volume) {
                cars.push_back(car);
            }
        }
        file.close();
    }
    return cars;
}
