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
        control();
        update();
        time_t endTime = clock();
        time_t delay = endTime - startTime;
        useconds_t sleepTime = static_cast<useconds_t>(static_cast<float>(delay) / CLOCKS_PER_SEC);
        usleep(sleepTime);
    }
    return 0;
}

NcursesDisplay::NcursesDisplay() : AMonitorDisplay::AMonitorDisplay(), isExit(false), isSelect(false), modulesWidget() {
    currWidget = modulesWidget.begin();
}

NcursesDisplay::~NcursesDisplay() {
    endwin();
}

void NcursesDisplay::_init() {
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    init_pair(3, COLOR_WHITE, COLOR_RED);

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
        modulesWidget.push_back(widget);
    }
}

void NcursesDisplay::update() {
    std::list<Widget>::iterator itr = modulesWidget.begin();
    for (; itr != modulesWidget.end(); itr++) {
        WINDOW *window = itr->window;
        IMonitorModule *module = itr->module;
        ModuleData data = module->update();
        werase(window);
        box(window, 0, 0);

        if (itr->module->getName() == currWidget->module->getName()) {
            if (isSelect) {
                wbkgd(window, COLOR_PAIR(3));
            } else {
                wbkgd(window, COLOR_PAIR(2));
            }
        }

        mvwprintw(window, 0, static_cast<int>(getmaxx(window) / 2 - std::strlen(itr->module->getName().c_str())), "%s",
                  itr->module->getName().c_str());

        ModuleData::labels_const_iterator clitr = data.getLabelsIterator();
        int y = 1;
        for (; clitr != data.getLabelsIteratorEnd(); clitr++) {
            mvwprintw(window, y, 2, "%s: %s", clitr->first.c_str(), clitr->second.c_str());
            y += 2;
        }
        ModuleData::datums_const_iterator cditr = data.getDatumsIterator();
        for (; cditr != data.getDatumsIteratorEnd(); cditr++) {
            int fill = static_cast<int>(std::roundf(cditr->second * 100));
            int maxSize = getmaxx(window) - 5;
            char *progBar = new char[maxSize + 1]();
            progBar[maxSize] = '\0';
            for (int i = 0; i < fill; ++i) {
                progBar[i] = '*';
            }
            for (int i = fill; i < maxSize; ++i) {
                progBar[i] = '_';
            }
            mvwprintw(window, y, static_cast<int>(getmaxx(window) / 2 - std::strlen(cditr->first.c_str())), "%s:",
                      cditr->first.c_str());
            y += 2;
            mvwprintw(window, y, 2, "%s", progBar);
            y += 2;
            delete[](progBar);
        }
        wrefresh(window);
        wbkgd(window, COLOR_PAIR(1));
    }
    refresh();
}

int NcursesDisplay::moduleHeihgtCalc(IMonitorModule *module) {
    float height = 0;
    ModuleData data = module->update();
    //calc lable
    ModuleData::labels_const_iterator clitr = data.getLabelsIterator();
    for (; clitr != data.getLabelsIteratorEnd(); clitr++) {
        height += 2.5;
    }
    ModuleData::datums_const_iterator cditr = data.getDatumsIterator();
    for (; cditr != data.getDatumsIteratorEnd(); cditr++) {
        height += 4.5;
    }
    //calc dynamic;
    return static_cast<int>(std::roundf(height));
}

void NcursesDisplay::redrowWindows() {
    erase();
    int y = 0;
    std::list<Widget>::iterator itr = modulesWidget.begin();
    for (; itr != modulesWidget.end(); itr++) {
        //height;width|y;x
        delwin(itr->window);
        int height = moduleHeihgtCalc(itr->module);
        WINDOW *win = newwin(height, (getmaxx(stdscr) - 20), y, 5);
        y += height;
        itr->window = win;
    }
}

void NcursesDisplay::control() {
    int btnCmd = getch();
    if (btnCmd == KEY_UP) {
        if (currWidget != modulesWidget.begin()) {
            if (isSelect) {
                std::list<Widget>::iterator prewWidget = currWidget;
                prewWidget--;
                std::swap(*prewWidget, *currWidget);
                currWidget = prewWidget;
                redrowWindows();
            } else {
                currWidget--;
            }
        }
    } else if (btnCmd == KEY_DOWN) {
        if (currWidget->module->getName() != modulesWidget.back().module->getName()) {
            if (isSelect) {
                std::list<Widget>::iterator nextWidget = currWidget;
                nextWidget++;
                std::swap(*nextWidget, *currWidget);
                currWidget = nextWidget;
                redrowWindows();
            } else {
                currWidget++;
            }
        }
    } else if (btnCmd == 32) {
        if (isSelect) {
            isSelect = false;
        } else {
            isSelect = true;
        }
    } else if (btnCmd == KEY_F(1) && isSelect) {
        if (modulesWidget.size() > 1) {
            modulesWidget.erase(currWidget);
            currWidget = modulesWidget.begin();
            isSelect = false;
            redrowWindows();
        }
    } else if (btnCmd == KEY_F(2)) {
        std::list<Widget>::iterator witr = modulesWidget.begin();
        for (; witr != modulesWidget.end(); witr++) {
            delwin(witr->window);
        }
        modulesWidget.clear();

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
            modulesWidget.push_back(widget);
        }
        currWidget = modulesWidget.begin();
        redrowWindows();
    } else if (btnCmd == 27) {
        isExit = true;
    }
}

NcursesDisplay::NcursesDisplay(const NcursesDisplay &rhs) :
        isExit(rhs.isExit),
        currWidget(rhs.currWidget),
        isSelect(rhs.isSelect),
        modulesWidget(rhs.modulesWidget) {
}

NcursesDisplay &NcursesDisplay::operator=(const NcursesDisplay &rhs) {
    isExit = rhs.isExit;
    currWidget = rhs.currWidget;
    isSelect = rhs.isSelect;
    modulesWidget = rhs.modulesWidget;
    return *this;
}


