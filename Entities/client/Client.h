#ifndef UNTITLED4_PERSON_H
#define UNTITLED4_PERSON_H

#include <string>
using namespace std;

class Client {
    std::string id;
    std::string passportNumber;
    std::string licenseNumber;

public:
    Client(const std::string &id, const std::string &passportNumber, const std::string &licenseNumber);

    void setId(const std::string &id);

    void setPassportNumber(const std::string &passportNumber);

    void setLicenseNumber(const std::string &licenseNumber);

    string getId() const;

    string getPassportNumber() const;

    string getLicenseNumber() const;
};

#endif // UNTITLED4_PERSON_H
