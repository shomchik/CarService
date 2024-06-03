#ifndef UNTITLED4_PERSON_H
#define UNTITLED4_PERSON_H

#include <string>
using namespace std;

class Client {
    string id;
    string passportNumber;
    string licenseNumber;

public:
    Client(const string &id, const string &passportNumber, const string &licenseNumber);

    void setId(const string &id);

    void setPassportNumber(const string &passportNumber);

    void setLicenseNumber(const string &licenseNumber);

    string getId() const;

    string getPassportNumber() const;

    string getLicenseNumber() const;
};

#endif // UNTITLED4_PERSON_H
