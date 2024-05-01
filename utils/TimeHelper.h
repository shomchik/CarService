//
// Created by Norik Saroyan on 02.05.24.
//

#ifndef CARSERVICE_TIMEHELPER_H
#define CARSERVICE_TIMEHELPER_H

#include "iostream"
#include "string"

using namespace std;

class TimeHelper {
public:
    static bool compareDates(const tm &date1, const tm &date2);
};


#endif //CARSERVICE_TIMEHELPER_H
