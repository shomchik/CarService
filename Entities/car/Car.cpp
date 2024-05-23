#include "Car.h"

#include <utility>

Car::Car(const QString &id, const QString &brand, const QString &model, const QString &volume, BodyType bodyType,
         Transmission transmission,
         bool hasCarSeat) {
    this->setId(id);
    this->setBrand(brand);
    this->setModel(model);
    this->setVolume(volume);
    this->setBodyType(bodyType);
    this->setTransmission(transmission);
    this->setHasCarSeat(hasCarSeat);
}

Car::Car(QString id, const QString &brand,
         const QString &model, const QString &volume,
         BodyType bodyType, Transmission transmission,
         bool hasCarSeat, double rate) {
    this->setId(id);
    this->setBrand(brand);
    this->setModel(model);
    this->setVolume(volume);
    this->setBodyType(bodyType);
    this->setTransmission(transmission);
    this->setHasCarSeat(hasCarSeat);
    this->setRate(rate);
}

Car::Car(const QString &id, const QString &brand, const QString &model, const QString &volume, BodyType bodyType,
         Transmission transmission, bool hasCarSeat, double rate, const QString &path) {
    this->setId(id);
    this->setBrand(brand);
    this->setModel(model);
    this->setVolume(volume);
    this->setBodyType(bodyType);
    this->setTransmission(transmission);
    this->setHasCarSeat(hasCarSeat);
    this->setRate(rate);
    this->setPath(path);
}


const QString &Car::getBrand() const {
    return this->brand;
}


void Car::setBrand(const QString &brand) {
    this->brand = brand;
}

const QString &Car::getModel() const {
    return this->model;
}

void Car::setModel(const QString &model) {
    this->model = model;
}

const QString &Car::getVolume() const {
    return volume;
}

void Car::setVolume(const QString &volume) {
    this->volume = volume;
}

BodyType Car::getBodyType() const {
    return this->bodyType;
}

void Car::setBodyType(BodyType bodyType) {
    this->bodyType = bodyType;
}

Transmission Car::getTransmission() const {
    return this->transmission;
}

void Car::setTransmission(Transmission transmission) {
    this->transmission = transmission;
}

bool Car::isHasCarSeat() const {
    return this->hasCarSeat;
}

void Car::setHasCarSeat(bool hasCarSeat) {
    this->hasCarSeat = hasCarSeat;
}

Car::Car() {
}

const QString &Car::getId() const {
    return id;
}

void Car::setId(const QString &id) {
    Car::id = id;
}

double Car::getRate() const {
    return rate;
}

void Car::setRate(double rate) {
    Car::rate = rate;
}

void Car::setPath(const QString &path) {
    this->path = path;
}

const QString &Car::getPath() const {
    return path;
}

Car::~Car() {
}
