cmake_minimum_required(VERSION 3.28)
project(CarService)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt@5 ")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(CarService main.cpp
        Entities/car/Car.cpp
        Entities/car/Car.h
        Entities/car/BodyType.h
        Entities/car/Transmission.h
        Entities/order/Order.cpp
        Entities/order/Order.h
        Entities/person/Person.cpp
        Entities/person/Person.h
        Services/car/CarService.cpp
        Services/car/CarService.h
        Services/order/OrderService.cpp
        Services/order/OrderService.h
        mapper/car/CarMapper.cpp
        mapper/car/CarMapper.h
        mapper/order/OrderMapper.cpp
        mapper/order/OrderMapper.h

        UI/cars/carcatalogpage.h
        UI/cars/carcatalogpage.cpp
        UI/cars/carcatalogpage.h
        UI/cars/reservationDialog/qcarreservationdialog.cpp
        UI/cars/reservationDialog/qcarreservationdialog.h

        UI/orders/orderspage.cpp
        UI/orders/orderspage.h

        UI/static/header/headerwidget.cpp
        UI/static/header/headerwidget.h
        utils/TimeHelper.cpp
        utils/TimeHelper.h

)
target_link_libraries(CarService
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

