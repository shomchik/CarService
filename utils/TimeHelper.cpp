//
// Created by Norik Saroyan on 02.05.24.
//

#include "TimeHelper.h"

bool TimeHelper::compareDates(const tm &date1, const tm &date2) {
    return mktime(const_cast<std::tm *>(&date1)) == mktime(const_cast<std::tm *>(&date2));
}
