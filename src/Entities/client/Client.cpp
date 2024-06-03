//
// Created by Norik Saroyan on 21.04.24.
//

#include "Client.h"

Client::Client(const string &id, const string &passportNumber, const string &licenseNumber)
    : id(id), passportNumber(passportNumber), licenseNumber(licenseNumber) {}

void Client::setId(const string &id) {
    this->id = id;
}

void Client::setPassportNumber(const string &passportNumber) {
    this->passportNumber = passportNumber;
}

void Client::setLicenseNumber(const string &licenseNumber) {
    this->licenseNumber = licenseNumber;
}

string Client::getId() const {
    return id;
}

string Client::getPassportNumber() const {
    return passportNumber;
}

string Client::getLicenseNumber() const {
    return licenseNumber;
}
