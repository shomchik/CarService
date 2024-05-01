#ifndef OP_PROJ_CONSOLE_CAR_H
#define OP_PROJ_CONSOLE_CAR_H


#include <ostream>
#include "string"
#include "QString"
#include "BodyType.h"
#include "Transmission.h"
class Car {
private:
    QString id;
    QString brand;
    QString model;
    QString volume;
    BodyType bodyType;
    Transmission transmission;
    double rate;
public:
    double getRate() const;

    void setRate(double rate);

private:
    bool hasCarSeat;

public:
    Car(QString id, QString brand, QString model, QString volume, BodyType bodyType, Transmission transmission,
        bool hasCarSeat);

    Car();

    const QString &getId() const;

    void setId(const QString &id);

    const QString &getBrand() const;

    void setBrand(const QString &brand);

    const QString &getModel() const;

    void setModel(const QString &model);

    const QString &getVolume() const;

    void setVolume(const QString &volume);

    BodyType getBodyType() const;

    void setBodyType(BodyType bodyType);

    Transmission getTransmission() const;

    void setTransmission(Transmission transmission);

    bool isHasCarSeat() const;

    void setHasCarSeat(bool hasCarSeat);

    virtual ~Car();
};


#endif //OP_PROJ_CONSOLE_CAR_H
