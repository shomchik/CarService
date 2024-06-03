#ifndef PATHSERVICE_H
#define PATHSERVICE_H

#include <string>
#include <fstream>
#include "../../serializers/path/PathMapper.h"

class PathService {
private:
    std::string path = "/Users/noriksaroyan/CLionProjects/CarService/database/car_logo_paths.txt";

public:
    void addPath(const std::string &path, const std::string &carId);

    void deletePath(const std::string &carId);

    void editPath(const std::string &newPath, const std::string &carId);

    string getPathByCarId(const string &carId);
};

#endif // PATHSERVICE_H
