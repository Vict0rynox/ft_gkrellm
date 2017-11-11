#include <iostream>

#include <gtk/gtk.h>
#include <sys/sysctl.h>
#include "Display/Gtk3Display.hpp"
#include "Monitor/DateTimeMonitorModule.hpp"
#include "Monitor/OSInfoMonitorModule.hpp"


int main(int argc, char *argv[]) {
    Gtk3Display gtk3Display;
    gtk3Display.addMonitorModule(new DateTimeMonitorModule());
    gtk3Display.addMonitorModule(new OSInfoMonitorModule());
    gtk3Display.run();

    return 0;
}