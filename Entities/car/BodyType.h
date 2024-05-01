
#ifndef OP_PROJ_CONSOLE_BODYTYPE_H
#define OP_PROJ_CONSOLE_BODYTYPE_H

enum BodyType {
    SEDAN,
    COUPE,
    HATCHBACK,
    CONVERTIBLE,
    SUV,
    TRUCK,
    VAN,
    UNDEFINED
};
inline const char *toString(BodyType bodyType) {
    switch (bodyType) {
        case SEDAN:
            return "SEDAN";
        case COUPE:
            return "COUPE";
        case HATCHBACK:
            return "HATCHBACK";
        case CONVERTIBLE:
            return "CONVERTIBLE";
        case SUV:
            return "SUV";
        case TRUCK:
            return "TRUCK";
        case VAN:
            return "VAN";
        default:
            return "UNDISCLOSED";
    }
}
// string to body type converter
inline const static BodyType stobt(const QString& str) {
    if (str == "SEDAN") {
        return SEDAN;
    } else if (str == "COUPE") {
        return COUPE;
    } else if (str == "HATCHBACK") {
        return HATCHBACK;
    } else if (str == "CONVERTIBLE") {
        return CONVERTIBLE;
    } else if (str == "SUV") {
        return SUV;
    } else if (str == "TRUCK") {
        return TRUCK;
    } else if (str == "VAN") {
        return VAN;
    }else{
        return UNDEFINED;
    }
}


#endif //OP_PROJ_CONSOLE_BODYTYPE_H
