#ifndef MOCKCARSERIALIZER_H
#define MOCKCARSERIALIZER_H


#include <gtest/gtest.h>
#include "Services/car/CarService.h"
#include "MockCarSerializer.h"
#include <fstream>

class CarServiceTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::ofstream outFile("cars.txt");
        outFile << "1,Toyota,Corolla,1.8,0,0,4.5,1\n";
        outFile << "2,Honda,Civic,1.6,1,1,4.0,0\n";
        outFile << "3,Ford,Mustang,5.0,2,0,4.8,0\n";
        outFile.close();
    }

    void TearDown() override {
        std::remove("cars.txt");
    }

    CarService carService{"cars.txt"};
};

TEST_F(CarServiceTest, TestInsertCar) {
    Car newCar("4", "Chevrolet", "Camaro", "6.2", BodyType::COUPE, Transmission::AUTOMATIC, true, 4.6);
    carService.insertCar(newCar);

    std::ifstream inFile("cars.txt");
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    ASSERT_EQ(lines.size(), 4);
    EXPECT_EQ(lines.back(), "4,Chevrolet,Camaro,6.2,3,1,4.6,1");
}

TEST_F(CarServiceTest, TestEditCar) {
    Car editedCar("2", "Honda", "Accord", "2.0", BodyType::SEDAN, Transmission::AUTOMATIC, false, 4.2);
    carService.editCar(editedCar);

    std::ifstream inFile("cars.txt");
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    ASSERT_EQ(lines.size(), 3);
    EXPECT_EQ(lines[1], "2,Honda,Accord,2.0,1,1,4.2,0");
}

TEST_F(CarServiceTest, TestDeleteCar) {
    Car carToDelete("3", "", "", "", BodyType::UNKNOWN, Transmission::UNKNOWN, false, 0);
    carService.deleteCar(carToDelete);

    std::ifstream inFile("cars.txt");
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    ASSERT_EQ(lines.size(), 2);
    EXPECT_EQ(lines[0], "1,Toyota,Corolla,1.8,0,0,4.5,1");
    EXPECT_EQ(lines[1], "2,Honda,Civic,1.6,1,1,4.0,0");
}

TEST_F(CarServiceTest, TestGetAllCars) {
    std::vector<Car> cars = carService.getAllCars();

    ASSERT_EQ(cars.size(), 3);
    EXPECT_EQ(cars[0].getId().toStdString(), "1");
    EXPECT_EQ(cars[1].getId().toStdString(), "2");
    EXPECT_EQ(cars[2].getId().toStdString(), "3");
}

TEST_F(CarServiceTest, TestGetCarById) {
    auto car = carService.getCarById("2");

    ASSERT_TRUE(car.has_value());
    EXPECT_EQ(car->getId().toStdString(), "2");
    EXPECT_EQ(car->getBrand().toStdString(), "Honda");
    EXPECT_EQ(car->getModel().toStdString(), "Civic");
    EXPECT_EQ(car->getVolume().toStdString(), "1.6");
    EXPECT_EQ(car->getBodyType(), BodyType::SEDAN);
    EXPECT_EQ(car->getTransmission(), Transmission::AUTOMATIC);
    EXPECT_EQ(car->getRate(), 4.0);
    EXPECT_FALSE(car->getHasCarSeat());
}

TEST_F(CarServiceTest, TestFindAllByBrand) {
    std::vector<Car> cars = carService.findAllByBrand("Toyota");

    ASSERT_EQ(cars.size(), 1);
    EXPECT_EQ(cars[0].getId().toStdString(), "1");
}

TEST_F(CarServiceTest, TestFindAllByModel) {
    std::vector<Car> cars = carService.findAllByModel("Civic");

    ASSERT_EQ(cars.size(), 1);
    EXPECT_EQ(cars[0].getId().toStdString(), "2");
}

TEST_F(CarServiceTest, TestFindAllByVolume) {
    std::vector<Car> cars = carService.findAllByVolume("1.8");

    ASSERT_EQ(cars.size(), 1);
    EXPECT_EQ(cars[0].getId().toStdString(), "1");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


#endif //MOCKCARSERIALIZER_H
