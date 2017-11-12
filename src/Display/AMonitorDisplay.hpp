//
// Created by Victor Vasiliev on 11/12/17.
//

#ifndef FT_GKRELLM_AMONITORDISPLAY_HPP
#define FT_GKRELLM_AMONITORDISPLAY_HPP


#include "../Monitor/IMonitorModule.hpp"
#include "IMonitorDisplay.hpp"

class AMonitorDisplay : public IMonitorDisplay {
protected:
    std::map<std::string, IMonitorModule*> monitorModules;
public:
    AMonitorDisplay();
    virtual ~AMonitorDisplay();
    void addMonitorModule(IMonitorModule *monitorModule);
    void removeMonitorModule(std::string monitorModuleName);
    virtual int run() = 0;
};


#endif //FT_GKRELLM_AMONITORDISPLAY_HPP
