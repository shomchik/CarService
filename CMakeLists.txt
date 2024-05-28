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
        Entities/client/Client.cpp
        Entities/client/Client.h
        Services/car/CarService.cpp
        Services/car/CarService.h
        Services/order/OrderService.cpp
        Services/order/OrderService.h
        serializers/car/CarSerializer.cpp
        serializers/car/CarSerializer.h
        serializers/order/OrderMapper.cpp
        serializers/order/OrderMapper.h

        UI/cars/catalog/carcatalogpage.h
        UI/cars/catalog/carcatalogpage.cpp
        UI/cars/catalog/carcatalogpage.h
        UI/cars/reservationDialog/qcarreservationdialog.cpp
        UI/cars/reservationDialog/qcarreservationdialog.h

        UI/static/header/headerwidget.cpp
        UI/static/header/headerwidget.h
        utils/TimeHelper.cpp
        utils/TimeHelper.h
        UI/orders/orderpage.cpp
        UI/orders/orderpage.h
        UI/orders/orderpage.ui
        UI/orders/orderpage.h
        Services/search/SearchService.cpp
        Services/search/SearchService.h
        Services/search/SearchService.h
        UI/cars/filterdialog.cpp
        UI/cars/filterdialog.h
        UI/cars/filterdialog.ui
        Services/client/ClientService.cpp
        Services/client/ClientService.h
        Services/client/ClientService.h
        serializers/client/ClientMapper.cpp
        serializers/client/ClientMapper.h
        UI/cars/add/qaddcardialog.cpp
        UI/cars/add/qaddcardialog.h
        UI/cars/add/qaddcardialog.ui
        UI/cars/edit/qeditcardialog.cpp
        UI/cars/edit/qeditcardialog.h
        UI/cars/edit/qeditcardialog.ui
        UI/cars/edit/qeditcardialog.h


)
target_link_libraries(CarService
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

