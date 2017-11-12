//
// Created by Victor Vasiliev on 11.11.2017.
//

#ifndef FT_GKRELLM_GTKMMDISPLAY_HPP
#define FT_GKRELLM_GTKMMDISPLAY_HPP


#include "IMonitorDisplay.hpp"
#include "AMonitorDisplay.hpp"
#include <gtk/gtk.h>

struct WidgetMonitorModule
{
    GtkWidget *moduleWidget;
    GtkWidget *dataWidget;
    IMonitorModule *module;
};

class Gtk3Display : public AMonitorDisplay{
protected:
    std::map<std::string, WidgetMonitorModule> widgetMonitorModules;

    GtkApplication *app;
    GtkWidget *mainWindow;
public:
    Gtk3Display();

    ~Gtk3Display();

    void appActivate();

    void update();

    int run();
};


#endif //FT_GKRELLM_GTKMMDISPLAY_HPP
