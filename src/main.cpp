#include <iostream>

#include <gtk/gtk.h>
#include <sys/sysctl.h>
#include "Display/Gtk3Display.hpp"
#include "Monitor/DateTimeMonitorModule.hpp"
#include "Monitor/OSInfoMonitorModule.hpp"
#include "Monitor/NameMonitorModule.hpp"
#include "Monitor/CPUMonitorModule.hpp"
#include "Monitor/MemoryMonitorModule.hpp"
#include "Monitor/NetworkMonitorModule.hpp"
#include "Monitor/DiskMonitorModule.hpp"
#include "Display/NcursesDisplay.hpp"


int main(int argc, char *argv[]) {


    IMonitorDisplay *display = nullptr;
    if(argc > 2) {
        if(std::string(argv[1]) == "-n") {
            display = new NcursesDisplay();
        } else{
            std::cout << "Usage: -n flag for run in console mode";
            exit(1);
        }
    } else {
        display = new Gtk3Display();
    }
    display->addMonitorModule(new DateTimeMonitorModule());
    display->addMonitorModule(new OSInfoMonitorModule());
    display->addMonitorModule(new CPUMonitorModule());
    display->addMonitorModule(new MemoryMonitorModule());
    display->addMonitorModule(new NetworkMonitorModule());
    display->addMonitorModule(new DiskMonitorModule());
    display->addMonitorModule(new NameMonitorModule());
    display->run();
    return 0;

}