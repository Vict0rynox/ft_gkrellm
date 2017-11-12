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


int main(int argc, char *argv[]) {

    Gtk3Display gtk3Display;
    gtk3Display.addMonitorModule(new DateTimeMonitorModule());
    gtk3Display.addMonitorModule(new OSInfoMonitorModule());
    gtk3Display.addMonitorModule(new CPUMonitorModule());
    gtk3Display.addMonitorModule(new MemoryMonitorModule());
    gtk3Display.addMonitorModule(new NetworkMonitorModule());
    gtk3Display.addMonitorModule(new DiskMonitorModule());
    gtk3Display.addMonitorModule(new NameMonitorModule());
    gtk3Display.run();

    return 0;
}