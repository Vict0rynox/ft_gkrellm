//
// Created by Victor Vasiliev on 11/12/17.
//

#ifndef FT_GKRELLM_NCURSESDISPLAY_HPP
#define FT_GKRELLM_NCURSESDISPLAY_HPP


#include "IMonitorDisplay.hpp"
#include "AMonitorDisplay.hpp"
#include <ncurses.h>
#include <list>

struct Widget
{
    WINDOW *window;
    IMonitorModule *module;
};

class NcursesDisplay : public AMonitorDisplay {
protected:
    bool isExit;
    std::list<Widget>::iterator currWidget;
    bool isSelect;
    std::list<Widget> modulesWidget;
    void _init();
    void update();
    void control();
    void redrowWindows();
    int moduleHeihgtCalc(IMonitorModule *module);
public:
    NcursesDisplay();
    ~NcursesDisplay();
    int run();
};


#endif //FT_GKRELLM_NCURSESDISPLAY_HPP
