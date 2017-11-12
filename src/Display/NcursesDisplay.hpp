//
// Created by Victor Vasiliev on 11/12/17.
//

#ifndef FT_GKRELLM_NCURSESDISPLAY_HPP
#define FT_GKRELLM_NCURSESDISPLAY_HPP


#include "IMonitorDisplay.hpp"
#include "AMonitorDisplay.hpp"
#include <ncurses.h>

struct Widget
{
    WINDOW *window;
    IMonitorModule *module;
};

class NcursesDisplay : public AMonitorDisplay {
protected:
    std::map<std::string, Widget> modulesWidget;
    bool isExit;
    void _init();
    void update();
    int moduleHeihgtCalc(IMonitorModule *module);
public:
    NcursesDisplay();
    ~NcursesDisplay();
    int run();
};


#endif //FT_GKRELLM_NCURSESDISPLAY_HPP
