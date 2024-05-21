#ifndef CLIENTSERVICE_H
#define CLIENTSERVICE_H
#include "../../Entities/client/Client.h"
using namespace std;

#include "string"

class ClientService {
    string const path = "/Users/noriksaroyan/CLionProjects/CarService/database/clients.txt";

public:
    void insertClient(const Client &client) const;

    Client getClient(const string &id) const;
};


#endif //CLIENTSERVICE_H
