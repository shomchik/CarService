#ifndef SEARCHSERVICE_H
#define SEARCHSERVICE_H

#include "../car/CarService.h"
#include "../order/OrderService.h"
#include <vector>
#include <string>
#include <utility>
#include <thread>

class SearchService {
private:
    CarService car_service_;
    OrderService order_service_;

public:
    pair<vector<Order>, vector<Car>> searchByKeyword(const string &keyword);
};

#endif //SEARCHSERVICE_H
