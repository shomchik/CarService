#include "SearchService.h"
#include "../../serializers/car/CarSerializer.h"
#include "../../serializers/order/OrderMapper.h"
#include <future>

std::pair<std::vector<Order>, std::vector<Car> > SearchService::searchByKeyword(const std::string &keyword) {
    auto searchOrders = [this, &keyword]() -> std::vector<Order> {
        std::vector<Order> matchedOrders;
        auto allOrders = order_service_.getAllOrders();
        for (const auto &order: allOrders) {
            std::string orderStr = OrderMapper::mapOrderToString(order);
            if (orderStr.find(keyword) != std::string::npos) {
                matchedOrders.push_back(order);
            }
        }
        return matchedOrders;
    };

    auto searchCars = [this, &keyword]() -> std::vector<Car> {
        std::vector<Car> matchedCars;
        auto allCars = car_service_.getAllCars();
        for (const auto &car: allCars) {
            std::string carStr = CarSerializer::serialize(car);
            if (carStr.find(keyword) != std::string::npos) {
                matchedCars.push_back(car);
            }
        }
        return matchedCars;
    };

    auto ordersFuture = std::async(std::launch::async, searchOrders);
    auto carsFuture = std::async(std::launch::async, searchCars);

    std::vector<Order> matchedOrders = ordersFuture.get();
    std::vector<Car> matchedCars = carsFuture.get();

    return {matchedOrders, matchedCars};
}
