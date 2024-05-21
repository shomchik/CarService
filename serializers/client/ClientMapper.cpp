//
// Created by Norik Saroyan on 21.05.24.
//

#include "ClientMapper.h"
#include "sstream";
std::string ClientMapper::mapToString(const Client &client) {
    std::ostringstream oss;
    oss << "ID:" << client.getId() << ",";
    oss << "PassportNumber:" << client.getPassportNumber() << ",";
    oss << "LicenseNumber:" << client.getLicenseNumber() << "\n";
    return oss.str();
}

Client ClientMapper::mapToClient(const std::string &data) {
    std::istringstream iss(data);
    std::string idStr, passportNumberStr, licenseNumberStr;

    std::getline(iss, idStr, ',');
    std::getline(iss, passportNumberStr, ',');
    std::getline(iss, licenseNumberStr);

    std::string id = idStr.substr(3);
    std::string passportNumber = passportNumberStr.substr(15);
    std::string licenseNumber = licenseNumberStr.substr(13);

    return {id, passportNumber, licenseNumber};
}