#ifndef UNTITLED4_ORDERMAPPER_H
#define UNTITLED4_ORDERMAPPER_H

#include "../../Entities/order/Order.h"
#include "string"

using namespace std;

class OrderMapper {
    string mapOrderToString(Order order);

    Order mapStringToOrder(string data);

};


#endif //UNTITLED4_ORDERMAPPER_H
