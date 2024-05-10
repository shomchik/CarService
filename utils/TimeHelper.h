#ifndef CARSERVICE_TIMEHELPER_H
#define CARSERVICE_TIMEHELPER_H

#include "iostream"
#include "string"
#include "QString"

using namespace std;

class TimeHelper {
public:
    static bool compareDates(const tm &date1, const tm &date2);
    static QString tmToQString(const tm &timeStruct);
};
#endif //CARSERVICE_TIMEHELPER_H
