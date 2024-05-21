//
// Created by Norik Saroyan on 21.05.24.
//

#ifndef CLIENTMAPPER_H
#define CLIENTMAPPER_H


#include "string"
#include "../../../Entities/client/Client.h"

class ClientMapper {
public:
    static string mapToString(const Client &client);

    static Client mapToClient(const string &line);
};


#endif //CLIENTMAPPER_H
