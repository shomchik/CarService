#include "CarService.h"
#include "../../mapper/car/CarMapper.h"
#include "QString"

string carsPath = "/Users/noriksaroyan/CLionProjects/CarLeasingService/database/cars.txt";
string errorMsg = "Ошибка подключения к базе";
CarMapper cm;

void CarService::insertCar(Car &car) {
    ofstream out(carsPath);
    if (!out.is_open()) {
        cout << errorMsg;
    }
    string data = cm.mapObjectToString(car);
    out << data << "\n";
    out.close();
}

void CarService::deleteCar(Car &car) {

    QString id = car.getId();
    ifstream in(carsPath);
    string line;
    int deleteIdx = 0;
    while(getline(in,line)){
        Car temp = cm.mapStringToObject(line);
        if(temp.getId() == id){
            break;
        }
        deleteIdx++;
    }
    if(deleteIdx){

    }

}