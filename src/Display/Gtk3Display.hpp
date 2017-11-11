//
// Created by Victor Vasiliev on 11.11.2017.
//

#ifndef FT_GKRELLM_GTKMMDISPLAY_HPP
#define FT_GKRELLM_GTKMMDISPLAY_HPP


#include "IMonitorDisplay.hpp"
#include <gtk/gtk.h>

struct WidgetMonitorModule
{
    GtkWidget *moduleWidget;
    GtkWidget *dataWidget;
    IMonitorModule *module;
};

class Gtk3Display : public IMonitorDisplay{
protected:
    std::map<std::string, IMonitorModule*> monitorModules;
    std::map<std::string, WidgetMonitorModule> widgetMonitorModules;

    GtkApplication *app;
    GtkWidget *mainWindow;
public:
    Gtk3Display();

    ~Gtk3Display();

    void addMonitorModule(IMonitorModule *monitorModule);

    void removeMonitorModule(std::string monitorModuleName);

    void appActivate();

    void update();

    int run();
};


#endif //FT_GKRELLM_GTKMMDISPLAY_HPP
