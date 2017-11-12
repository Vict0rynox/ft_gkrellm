//
// Created by Victor Vasiliev on 11.11.2017.
//

#include <iostream>
#include "Gtk3Display.hpp"

Gtk3Display::~Gtk3Display() {
    g_object_unref(app);
}

static gboolean monitorModuleCallback(Gtk3Display *display) {

    display->update();
    return true;
}

Gtk3Display::Gtk3Display() : AMonitorDisplay::AMonitorDisplay(), widgetMonitorModules() {
    app = gtk_application_new("org.ft_gkrellm.unit", G_APPLICATION_FLAGS_NONE);
}

static void activate(GtkApplication *app, Gtk3Display *display) {
    (void) app;
    display->appActivate();
}

int Gtk3Display::run() {
    int status;
    g_signal_connect(app, "activate", G_CALLBACK(activate), this);
    status = g_application_run(G_APPLICATION(app), 0, NULL);
    return status;
}


void Gtk3Display::appActivate() {
    this->mainWindow = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(this->mainWindow), "Ft_Gkrellm");
    gtk_window_set_default_size(GTK_WINDOW(this->mainWindow), 300, 200);
    gtk_container_set_border_width(GTK_CONTAINER(this->mainWindow), 10);

    //GtkWidget *mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    GtkWidget *mainBox = gtk_flow_box_new();
    gtk_flow_box_set_selection_mode(GTK_FLOW_BOX(mainBox), GTK_SELECTION_NONE);
    gtk_container_add(GTK_CONTAINER (this->mainWindow), mainBox);

    std::cout << "Start Gtk+3 application" << std::endl;

    std::map<std::string, IMonitorModule *>::iterator itr = monitorModules.begin();
    for (; itr != monitorModules.end(); itr++) {

        //create module tab
        GtkWidget *moduleBox = gtk_flow_box_child_new();

        //create module box
        GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        GtkWidget *widgetDataBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        gtk_container_add(GTK_CONTAINER(moduleBox), hbox);

        GtkWidget *moduleName = gtk_label_new(itr->first.c_str());
        gtk_box_pack_start(GTK_BOX(hbox), moduleName, false, false, 0);

        gtk_container_add(GTK_CONTAINER(hbox), widgetDataBox);
        gtk_container_add(GTK_CONTAINER (mainBox), moduleBox);

        // add widgetModuleBind
        WidgetMonitorModule widgetMonitorModule = {};
        widgetMonitorModule.module = itr->second;
        widgetMonitorModule.moduleWidget = moduleBox;
        widgetMonitorModule.dataWidget = widgetDataBox;
        widgetMonitorModules[itr->second->getName()] = widgetMonitorModule;
    }
    g_timeout_add(1200, reinterpret_cast<GSourceFunc>(monitorModuleCallback), this);
    gtk_widget_show_all(this->mainWindow);
}

void gtk_remove_child_recursive(GtkWidget *widget) {
    if (GTK_IS_CONTAINER(widget)) {
        GList *childList = gtk_container_get_children(GTK_CONTAINER(widget));
        while (childList != nullptr) {
            //TODO: add remove recursive
            gtk_remove_child_recursive(GTK_WIDGET(childList->data));
            gtk_container_remove(GTK_CONTAINER(widget), GTK_WIDGET(childList->data));
            childList = childList->next;
        }
    }
}

void Gtk3Display::update() {
    std::map<std::string, WidgetMonitorModule>::iterator itr = widgetMonitorModules.begin();
    for (; itr != widgetMonitorModules.end(); itr++) {
        GtkWidget *widget = itr->second.dataWidget;
        IMonitorModule *module = itr->second.module;

        ModuleData data = module->update();
        gtk_remove_child_recursive(widget);

        ModuleData::labels_const_iterator clitr = data.getLabelsIterator();
        for (; clitr != data.getLabelsIteratorEnd(); clitr++) {
            GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
            std::string nameVal = clitr->first + ": " + clitr->second;
            gtk_box_pack_start(GTK_BOX(box), gtk_label_new(nameVal.c_str()), false, true, 0);
            gtk_container_add(GTK_CONTAINER(widget), box);
        }

        ModuleData::datums_const_iterator cditr = data.getDatumsIterator();
        for (; cditr != data.getDatumsIteratorEnd(); cditr++) {
            GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
            gtk_box_pack_start(GTK_BOX(box), gtk_label_new(cditr->first.c_str()), false, true, 0);

            GtkWidget *progress = gtk_progress_bar_new();
            gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(progress), 1);
            gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress), (cditr->second));

            gtk_box_pack_start(GTK_BOX(box), progress, false, true, 0);
            gtk_container_add(GTK_CONTAINER(widget), box);
        }

        gtk_widget_show_all(this->mainWindow);
    }
}

Gtk3Display::Gtk3Display(const Gtk3Display &rhs) :
        widgetMonitorModules(rhs.widgetMonitorModules), app(rhs.app), mainWindow(rhs.mainWindow) {
}

Gtk3Display &Gtk3Display::operator=(const Gtk3Display &rhs) {
    widgetMonitorModules = rhs.widgetMonitorModules;
    app = rhs.app;
    mainWindow = rhs.mainWindow;
    return *this;
}
