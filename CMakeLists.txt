cmake_minimum_required(VERSION 3.28)
project(CarService)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Set the CMake prefix path for Qt6
set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt")

# Find Qt6 components
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Charts
        REQUIRED
)

# Find Google Test
find_package(GTest REQUIRED)

# Add the executable with all source files
add_executable(CarService
        src/main.cpp
        src/Entities/car/Car.cpp
        src/Entities/car/Car.h
        src/Entities/car/BodyType.h
        src/Entities/car/Transmission.h
        src/Entities/order/Order.cpp
        src/Entities/order/Order.h
        src/Entities/client/Client.cpp
        src/Entities/client/Client.h
        src/Services/car/CarService.cpp
        src/Services/car/CarService.h
        src/Services/order/OrderService.cpp
        src/Services/order/OrderService.h
        src/serializers/car/CarSerializer.cpp
        src/serializers/car/CarSerializer.h
        src/serializers/order/OrderMapper.cpp
        src/serializers/order/OrderMapper.h
        src/UI/cars/catalog/carcatalogpage.cpp
        src/UI/cars/catalog/carcatalogpage.h
        src/UI/cars/reservationDialog/qcarreservationdialog.cpp
        src/UI/cars/reservationDialog/qcarreservationdialog.h
        src/UI/static/header/headerwidget.cpp
        src/UI/static/header/headerwidget.h
        src/utils/TimeHelper.cpp
        src/utils/TimeHelper.h
        src/UI/orders/orderpage.cpp
        src/UI/orders/orderpage.h
        src/UI/orders/orderpage.ui
        src/Services/search/SearchService.cpp
        src/Services/search/SearchService.h
        src/UI/cars/filterdialog.cpp
        src/UI/cars/filterdialog.h
        src/UI/cars/filterdialog.ui
        src/Services/client/ClientService.cpp
        src/Services/client/ClientService.h
        src/serializers/client/ClientMapper.cpp
        src/serializers/client/ClientMapper.h
        src/UI/cars/add/qaddcardialog.cpp
        src/UI/cars/add/qaddcardialog.h
        src/UI/cars/add/qaddcardialog.ui
        src/UI/cars/edit/qeditcardialog.cpp
        src/UI/cars/edit/qeditcardialog.h
        src/UI/cars/edit/qeditcardialog.ui
        src/UI/diagram/transmissionchart.cpp
        src/UI/diagram/transmissionchart.h
        src/serializers/path/PathMapper.cpp
        src/serializers/path/PathMapper.h
        src/Services/path/PathService.cpp
        src/Services/path/PathService.h
        test/CarServiceTest.cpp
        test/CarServiceTest.h
        test/testMain.cpp
)

# Link Qt6 libraries
target_link_libraries(CarService
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Charts
)

# Link Google Test libraries
target_link_libraries(CarService
        GTest::gtest
        GTest::gtest_main
)

# Include the Google Test directories
include_directories(${GTEST_INCLUDE_DIRS})
