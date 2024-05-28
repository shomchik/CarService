#include "PathMapper.h"
#include <sstream>

string PathMapper::mapToDbString(const string &path, const string &carId) {
    stringstream ss;
    ss << carId << "|" << path << "\n";
    return ss.str();
}

unordered_map<string, string> PathMapper::mapFromDbString(const string &data) {
    unordered_map<string, string> result;

    stringstream ss(data);
    string carId, path;
    while (getline(ss, carId, '|')) {
        getline(ss, path);
        path.erase(path.begin(), find_if(path.begin(), path.end(), [](unsigned char ch) {
            return !isspace(ch);
        }));
        result[carId] = path;
    }
    return result;
}
