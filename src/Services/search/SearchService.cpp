#include "SearchService.h"
#include "../../serializers/car/CarSerializer.h"
#include "../../serializers/order/OrderMapper.h"
#include <future>

pair<vector<Order>, vector<Car> > SearchService::searchByKeyword(const string &keyword) {
    auto searchOrders = [this, &keyword]() -> vector<Order> {
        vector<Order> matchedOrders;
        auto allOrders = order_service_.getAllOrders();
        for (const auto &order: allOrders) {
            string orderStr = OrderMapper::mapOrderToString(order);
            if (orderStr.find(keyword) != string::npos) {
                matchedOrders.push_back(order);
            }
        }
        return matchedOrders;
    };

    auto searchCars = [this, &keyword]() -> vector<Car> {
        vector<Car> matchedCars;
        auto allCars = car_service_.getAllCars();
        for (const auto &car: allCars) {
            string carStr = CarSerializer::serialize(car);
            if (carStr.find(keyword) != string::npos) {
                matchedCars.push_back(car);
            }
        }
        return matchedCars;
    };

    auto ordersFuture = async(launch::async, searchOrders);
    auto carsFuture = async(launch::async, searchCars);

    vector<Order> matchedOrders = ordersFuture.get();
    vector<Car> matchedCars = carsFuture.get();

    return {matchedOrders, matchedCars};
}
