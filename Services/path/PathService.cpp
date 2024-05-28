#include "PathService.h"
#include <fstream>
#include <iostream>
#include <sstream>

void PathService::addPath(const string &path, const string &carId) {
    ofstream file(this->path, ios_base::app);
    if (file.is_open()) {
        file << PathMapper::mapToDbString(path, carId);
        file.close();
    } else {
    }
}

void PathService::deletePath(const string &carId) {
    ifstream inFile(this->path);
    ofstream outFile("temp.txt");
    if (inFile.is_open() && outFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            string currentCarId = line.substr(0, line.find('|'));
            if (currentCarId != carId) {
                outFile << line << endl;
            }
        }
        inFile.close();
        outFile.close();
        remove(this->path.c_str());
        rename("temp.txt", this->path.c_str());
    } else {
        // Handle error opening files
    }
}

void PathService::editPath(const string &newPath, const string &carId) {
    ifstream inFile(this->path);
    ofstream outFile("temp.txt");
    if (inFile.is_open() && outFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            string currentCarId = line.substr(0, line.find('|'));
            if (currentCarId == carId) {
                outFile << carId << " | " << newPath << endl;
            } else {
                outFile << line << endl;
            }
        }
        inFile.close();
        outFile.close();
        remove(this->path.c_str());
        rename("temp.txt", this->path.c_str());
    } else {
    }
}

string PathService::getPathByCarId(const string &carId) {
    ifstream file(path);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            string mappedCarId = line.substr(0, line.find('|'));
            // Trim leading and trailing spaces from mappedCarId
            mappedCarId.erase(0, mappedCarId.find_first_not_of(" "));
            mappedCarId.erase(mappedCarId.find_last_not_of(" ") + 1);
            if (mappedCarId == carId) {
                cout << "Found Car ID: " << carId << ", Line: " << line << endl;
                // Extract the path directly from the line
                size_t startPos = line.find('|') + 2; // Skip '| ' characters
                cout << "Extracted Path: " << line.substr(startPos) << endl;
                return line.substr(startPos); // Return the path
            }
        }
        file.close();
    } else {
        cout << "Unable to open file: " << path << endl;
    }
    return ""; // Return empty string if car ID is not found or file cannot be opened
}
