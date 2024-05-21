#ifndef ORDERMAPPER_H
#define ORDERMAPPER_H

#include "../../Entities/order/Order.h"
#include "string"

using namespace std;

class OrderMapper {
public:
    static string mapOrderToString(const Order &order);

    static Order mapStringToOrder(const string &data);
};


#endif //ORDERMAPPER_H
