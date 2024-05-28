//
// Created by Norik Saroyan on 02.05.24.
//

#include "TimeHelper.h"

QDate TimeHelper::tmToQDate(const tm &timeStruct) {
    return QDate(timeStruct.tm_year + 1900, timeStruct.tm_mon + 1, timeStruct.tm_mday);
}

QString TimeHelper::tmToQString(const tm &timeStruct) {
    const QString &format = "Year: %Y, Month: %m, Day: %d";
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), format.toStdString().c_str(), &timeStruct);
    return QString::fromUtf8(buffer);
}

bool TimeHelper::compareDates(const tm &date1, const tm &date2) {
    return mktime(const_cast<std::tm *>(&date1)) == mktime(const_cast<std::tm *>(&date2));
}

tm TimeHelper::QDateToTm(const QDate &date) {
    tm timeStruct;
    timeStruct.tm_year = date.year() - 1900;  // Years since 1900
    timeStruct.tm_mon = date.month() - 1;     // Month (0 - 11)
    timeStruct.tm_mday = date.day();          // Day of the month (1 - 31)
    timeStruct.tm_hour = 0;                   // Hour (0 - 23)
    timeStruct.tm_min = 0;                    // Minute (0 - 59)
    timeStruct.tm_sec = 0;                    // Second (0 - 60)

    // Not setting other fields like tm_wday, tm_yday, tm_isdst to avoid ambiguity

    return timeStruct;
}
