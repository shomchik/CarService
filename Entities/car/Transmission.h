#ifndef OP_PROJ_CONSOLE_TRANSMISSION_H
#define OP_PROJ_CONSOLE_TRANSMISSION_H

#include "string"
#include "QString"
using namespace std;

enum Transmission {
    MANUAL,
    AUTOMATIC,
    VARIATOR,
    UNDEF
};

inline const char * toString(Transmission trsmn) {
    switch (trsmn) {
        case MANUAL:
            return "MANUAL";
        case AUTOMATIC:
            return "AUTOMATIC";
        case VARIATOR:
            return "VARIATOR";
        default:
            return "UNDEF";
    }
}

// string to transmission
static Transmission stot(const QString& str) {
    if (str == "MANUAL") {
        return MANUAL;
    } else if (str == "AUTOMATIC") {
        return AUTOMATIC;
    } else if (str == "VARIATOR") {
        return VARIATOR;
    }else{
        return UNDEF;
    }
}


#endif //OP_PROJ_CONSOLE_TRANSMISSION_H
