//
// Created by Norik Saroyan on 21.04.24.
//

#include "Client.h"

Client::Client(const std::string &id, const std::string &passportNumber, const std::string &licenseNumber)
    : id(id), passportNumber(passportNumber), licenseNumber(licenseNumber) {}

void Client::setId(const std::string &id) {
    this->id = id;
}

void Client::setPassportNumber(const std::string &passportNumber) {
    this->passportNumber = passportNumber;
}

void Client::setLicenseNumber(const std::string &licenseNumber) {
    this->licenseNumber = licenseNumber;
}

std::string Client::getId() const {
    return id;
}

std::string Client::getPassportNumber() const {
    return passportNumber;
}

std::string Client::getLicenseNumber() const {
    return licenseNumber;
}
