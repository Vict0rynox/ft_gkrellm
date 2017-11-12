//
// Created by Victor Vasiliev on 11.11.2017.
//

#ifndef FT_GKRELLM_OSINFOMONITORMODULE_HPP
#define FT_GKRELLM_OSINFOMONITORMODULE_HPP


#include "IMonitorModule.hpp"
#include "AMonitorModule.hpp"

class OSInfoMonitorModule : public AMonitorModule {
public:
    ~OSInfoMonitorModule();
    OSInfoMonitorModule();
    OSInfoMonitorModule(const OSInfoMonitorModule &rhs);
    OSInfoMonitorModule&operator=(const OSInfoMonitorModule &rhs);
    const ModuleData update();
};

#endif //FT_GKRELLM_OSINFOMONITORMODULE_HPP
