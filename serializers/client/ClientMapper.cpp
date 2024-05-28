//
// Created by Norik Saroyan on 21.05.24.
//

#include "ClientMapper.h"
#include "sstream"
string ClientMapper::mapToString(const Client &client) {
    ostringstream oss;
    oss << "ID:" << client.getId() << ",";
    oss << "PassportNumber:" << client.getPassportNumber() << ",";
    oss << "LicenseNumber:" << client.getLicenseNumber() << "\n";
    return oss.str();
}

Client ClientMapper::mapToClient(const string &data) {
    istringstream iss(data);
    string idStr, passportNumberStr, licenseNumberStr;

    getline(iss, idStr, ',');
    getline(iss, passportNumberStr, ',');
    getline(iss, licenseNumberStr);

    string id = idStr.substr(3);
    string passportNumber = passportNumberStr.substr(15);
    string licenseNumber = licenseNumberStr.substr(13);

    return {id, passportNumber, licenseNumber};
}