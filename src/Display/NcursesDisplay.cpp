//
// Created by Victor Vasiliev on 11/12/17.
//

#include <unistd.h>
#include <tgmath.h>
#include "NcursesDisplay.hpp"

int NcursesDisplay::run() {
    _init();
    while (!isExit) {
        time_t startTime = clock();
        update();
        time_t endTime = clock();
        time_t delay = endTime - startTime;
        useconds_t sleepTime = static_cast<useconds_t>(static_cast<float>(delay) / CLOCKS_PER_SEC);
        usleep(sleepTime);
    }
    return 0;
}

NcursesDisplay::NcursesDisplay() : AMonitorDisplay::AMonitorDisplay(), isExit(false) {

}

NcursesDisplay::~NcursesDisplay() {
    endwin();
}

void NcursesDisplay::_init() {
    initscr();
    curs_set(0);
    //raw();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    halfdelay(1);

    //init module
    int y = 0;
    std::map<std::string, IMonitorModule *>::iterator itr = monitorModules.begin();
    for (; itr != monitorModules.end(); itr++) {
        //height;width|y;x
        Widget widget = {};
        int height = moduleHeihgtCalc(itr->second);
        WINDOW *win = newwin(height, (getmaxx(stdscr) - 20), y, 5);
        y += height;
        widget.window = win;
        widget.module = itr->second;
        modulesWidget[itr->first] = widget;
    }
}

void NcursesDisplay::update() {
    std::map<std::string, Widget>::iterator itr = modulesWidget.begin();
    for (; itr != modulesWidget.end(); itr++) {
        WINDOW *window = itr->second.window;
        IMonitorModule *module = itr->second.module;
        ModuleData data = module->update();

        werase(window);
        box(window, 0, 0);
        ModuleData::labels_const_iterator clitr = data.getLabelsIterator();
        int y = 1;
        for (;clitr != data.getLabelsIteratorEnd(); clitr++) {
            mvwprintw(window,y,2, "%s: %s", clitr->first.c_str(), clitr->second.c_str());
            y += 2;
        }
        ModuleData::datums_const_iterator cditr = data.getDatumsIterator();
        for (;cditr != data.getDatumsIteratorEnd(); cditr++) {
            int fill = static_cast<int>(std::roundf(cditr->second * 100));
            int maxSize = getmaxx(window) - 5;
            char *progBar = new char[maxSize + 1]();
            progBar[maxSize] = '\0';
            for (int i = 0; i <fill; ++i) {
                progBar[i] = '*';
            }
            for (int i = fill; i < maxSize; ++i) {
                progBar[i] = '_';
            }
            mvwprintw(window,y,2, "%s", progBar);
            y += 2;
            delete[](progBar);
        }
        wrefresh(window);
    }
}

int NcursesDisplay::moduleHeihgtCalc(IMonitorModule *module) {
    float height = 0;
    ModuleData data = module->update();
    //calc lable
    ModuleData::labels_const_iterator clitr = data.getLabelsIterator();
    for (;clitr != data.getLabelsIteratorEnd(); clitr++) {
        height += 2.5;
    }
    ModuleData::datums_const_iterator cditr = data.getDatumsIterator();
    for (;cditr != data.getDatumsIteratorEnd(); cditr++) {
        height += 2.5;
    }
    //calc dynamic;
    return static_cast<int>(std::roundf(height));
}

