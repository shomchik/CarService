#include "ClientService.h"
#include <fstream>
#include <stdexcept>
#include "../../serializers/client/ClientMapper.h"

void ClientService::insertClient(const Client &client) const {
    std::ofstream outFile(path, std::ios::app);
    if (!outFile.is_open()) {
        throw std::runtime_error("Failed to open clients file for writing.");
    }
    outFile << ClientMapper::mapToString(client);
    outFile.close();
}


Client ClientService::getClient(const std::string &clientId) const {
    std::ifstream inFile(path);
    if (!inFile.is_open()) {
        throw std::runtime_error("Failed to open clients file for reading.");
    }

    std::string line;
    while (std::getline(inFile, line)) {
        optional<Client> client = ClientMapper::mapToClient(line);
        if (client.has_value()) {
            if (client.value().getId() == clientId) {
                inFile.close();
                return client.value();
            }
        }
    }

    inFile.close();
    throw std::runtime_error("Client with ID " + clientId + " not found.");
}
