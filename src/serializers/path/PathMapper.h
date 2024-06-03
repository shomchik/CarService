//
// Created by Norik Saroyan on 28.05.24.
//

#ifndef PATHMAPPER_H
#define PATHMAPPER_H
#include <string>

using namespace std;

class PathMapper {
public:
    static string mapToDbString(const string &path, const string &carId);

    static unordered_map<string, string> mapFromDbString(const string &data);
};


#endif //PATHMAPPER_H
