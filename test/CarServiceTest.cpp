//
// Created by Norik Saroyan on 03.06.24.
//

#include "CarServiceTest.h"

TEST_F(CarServiceTest, InsertCarTest) {
    Car car3(QString("3"), QString("BrandC"), QString("ModelC"), QString("1.8"), BodyType::COUPE, Transmission::MANUAL, false, 4.0);
    carService.insertCar(car3);

    std::vector<Car> cars = carService.getAllCars();
    ASSERT_EQ(cars.size(), 3);
}

TEST_F(CarServiceTest, EditCarTest) {
    car1.setBrand(QString("BrandX"));
    carService.editCar(car1);

    std::optional<Car> car = carService.getCarById("1");
    ASSERT_TRUE(car.has_value());
    EXPECT_EQ(car->getBrand(), QString("BrandX"));
}

TEST_F(CarServiceTest, DeleteCarTest) {
    carService.deleteCar(car1);

    std::vector<Car> cars = carService.getAllCars();
    ASSERT_EQ(cars.size(), 1);
}

TEST_F(CarServiceTest, GetCarByIdTest) {
    std::optional<Car> car = carService.getCarById("1");
    ASSERT_TRUE(car.has_value());
    EXPECT_EQ(car->getId(), QString("1"));
}

TEST_F(CarServiceTest, FindAllByBrandTest) {
    std::vector<Car> cars = carService.findAllByBrand(QString("BrandA"));
    ASSERT_EQ(cars.size(), 1);
    EXPECT_EQ(cars[0].getBrand(), QString("BrandA"));
}
