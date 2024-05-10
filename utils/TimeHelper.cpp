//
// Created by Norik Saroyan on 02.05.24.
//

#include "TimeHelper.h"

//bool TimeHelper::compareDates(const tm &date1, const tm &date2) {
//    return mktime(const_cast<std::tm *>(&date1)) == mktime(const_cast<std::tm *>(&date2));
//}
//
//static QString tmToQString(const tm& timeStruct) {
//    const QString& format = "Year: %Y, Month: %m, Day: %d";
//    char buffer[80];
//    std::strftime(buffer, sizeof(buffer), format.toStdString().c_str(), &timeStruct);
//    return QString::fromUtf8(buffer);
//}

QString TimeHelper::tmToQString(const tm &timeStruct) {
    const QString& format = "Year: %Y, Month: %m, Day: %d";
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), format.toStdString().c_str(), &timeStruct);
    return QString::fromUtf8(buffer);
}

bool TimeHelper::compareDates(const tm &date1, const tm &date2) {
        return mktime(const_cast<std::tm *>(&date1)) == mktime(const_cast<std::tm *>(&date2));
}