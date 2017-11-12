//
// Created by Victor Vasiliev on 11/12/17.
//

#ifndef FT_GKRELLM_NETWORKMONITORMODULE_HPP
#define FT_GKRELLM_NETWORKMONITORMODULE_HPP

#include "AMonitorModule.hpp"

class NetworkMonitorModule : public AMonitorModule {
protected:

public:
    NetworkMonitorModule();
    ~NetworkMonitorModule();
    const ModuleData update();
};


#endif //FT_GKRELLM_NETWORKMONITORMODULE_HPP
