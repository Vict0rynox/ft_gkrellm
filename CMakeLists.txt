cmake_minimum_required(VERSION 3.8)
project(ft_gkrellm)

set(CMAKE_CXX_STANDARD 98)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_package(PkgConfig)

pkg_check_modules(GTK3 gtk+-3.0)

link_directories(${GTK3_LIBRARY_DIRS})

include_directories(${GTK3_INCLUDE_DIRS})

set(SOURCE_FILES src/main.cpp
        src/Monitor/IMonitorModule.hpp
        src/Display/IMonitorDisplay.hpp
        src/Monitor/DateTimeMonitorModule.cpp
        src/Monitor/DateTimeMonitorModule.hpp
        src/Data/ModuleData.cpp
        src/Data/ModuleData.hpp
        src/Display/Gtk3Display.cpp
        src/Display/Gtk3Display.hpp src/Monitor/OSInfoMonitorModule.cpp src/Monitor/OSInfoMonitorModule.hpp src/Monitor/AMonitorModule.cpp src/Monitor/AMonitorModule.hpp src/Monitor/NameMonitorModule.cpp src/Monitor/NameMonitorModule.hpp src/Monitor/CPUMonitorModule.cpp src/Monitor/CPUMonitorModule.hpp src/Utils/utils.hpp src/Monitor/MemoryMonitorModule.cpp src/Monitor/MemoryMonitorModule.hpp src/Monitor/NetworkMonitorModule.cpp src/Monitor/NetworkMonitorModule.hpp src/Monitor/DiskMonitorModule.cpp src/Monitor/DiskMonitorModule.hpp src/Display/NcursesDisplay.cpp src/Display/NcursesDisplay.hpp src/Display/AMonitorDisplay.cpp src/Display/AMonitorDisplay.hpp)
add_executable(ft_gkrellm ${SOURCE_FILES})

target_link_libraries(ft_gkrellm -lncurses ${GTK3_LIBRARIES})