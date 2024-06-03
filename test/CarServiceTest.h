//
// Created by Norik Saroyan on 03.06.24.
//

#ifndef CARSERVICETEST_H
#define CARSERVICETEST_H

#include <QString>

#include "gtest/gtest.h"
#include "../src/Services/car/CarService.h"

class CarServiceTest : public ::testing::Test {
protected:
    CarService carService;
    Car car1;
    Car car2;

    void SetUp() override {
        car1 = Car(QString("1"), QString("BrandA"), QString("ModelA"), QString("1.6"), BodyType::SEDAN, Transmission::MANUAL, true, 4.5);
        car2 = Car(QString("2"), QString("BrandB"), QString("ModelB"), QString("2.0"), BodyType::SUV, Transmission::AUTOMATIC, false, 3.9);

        carService.insertCar(car1);
        carService.insertCar(car2);
    }

    void TearDown() override {
    }
};

#endif
