//
// Created by Victor Vasiliev on 11.11.2017.
//

#ifndef FT_GKRELLM_NAMEMONITORMODULE_HPP
#define FT_GKRELLM_NAMEMONITORMODULE_HPP


#include "AMonitorModule.hpp"

class NameMonitorModule : public AMonitorModule {
public:
    NameMonitorModule();
    ~NameMonitorModule();
    const ModuleData update();
};


#endif //FT_GKRELLM_NAMEMONITORMODULE_HPP
