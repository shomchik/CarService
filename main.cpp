#include <QApplication>
#include <QPushButton>
#include "UI/cars/catalog/carcatalogpage.h"

int main(int argc, char *argv[]) {
//    CarService carService;
//    vector<Car> cars = {
//            Car("1", "Mercedes", "G63", "2.0L", SEDAN, AUTOMATIC, true, 1500.0),
//            Car("2", "BMW", "X5", "3.0L", SUV, AUTOMATIC, true, 1200.0),
//            Car("3", "Audi", "A4", "1.8L", SEDAN, MANUAL, false, 1000.0),
//            Car("4", "Toyota", "Camry", "2.5L", SEDAN, AUTOMATIC, true, 900.0),
//            Car("5", "Ford", "Mustang", "5.0L", COUPE, MANUAL, true, 2000.0),
//            Car("6", "Tesla", "Model S", "Electric", SEDAN, AUTOMATIC, false, 2500.0),
//            Car("7", "Chevrolet", "Tahoe", "5.3L", SUV, AUTOMATIC, true, 1800.0),
//            Car("8", "Honda", "Civic", "1.5L", SEDAN, AUTOMATIC, true, 8500.0),
//            Car("9", "Jeep", "Wrangler", "3.6L", SUV, MANUAL, true, 1600.0),
//            Car("10", "Volkswagen", "Golf", "1.4L", HATCHBACK, MANUAL, false, 9500.0),
//            Car("11", "Mercedes", "C-Class", "2.0L", SEDAN, AUTOMATIC, true, 1100.0),
//            Car("12", "BMW", "3 Series", "2.0L", SEDAN, AUTOMATIC, true, 1050.0),
//            Car("13", "Audi", "Q7", "3.0L", SUV, AUTOMATIC, true, 1350.0),
//            Car("14", "Toyota", "Corolla", "1.6L", SEDAN, MANUAL, true, 8000.0),
//            Car("15", "Ford", "Explorer", "3.5L", SUV, AUTOMATIC, true, 1700.0),
//            Car("16", "Tesla", "Model 3", "Electric", SEDAN, AUTOMATIC, false, 2200.0),
//            Car("17", "Chevrolet", "Camaro", "6.2L", COUPE, MANUAL, true, 2300.0),
//            Car("18", "Honda", "Accord", "2.0L", SEDAN, AUTOMATIC, true, 9500.0),
//            Car("19", "Jeep", "Grand Cherokee", "3.6L", SUV, AUTOMATIC, true, 1850.0),
//            Car("20", "Volkswagen", "Passat", "2.0L", SEDAN, AUTOMATIC, false, 1000.0)
//    };
//
//    for (const Car& car : cars) {
//        carService.insertCar(const_cast<Car &>(car));
//    }

    QApplication a(argc, argv);
    CarCatalogPage home;
    home.show();
    return QApplication::exec();
}
