//
// Created by Victor Vasiliev on 11/12/17.
//

#ifndef FT_GKRELLM_NETWORKMONITORMODULE_HPP
#define FT_GKRELLM_NETWORKMONITORMODULE_HPP

#include "AMonitorModule.hpp"

class NetworkMonitorModule : public AMonitorModule {
public:
    NetworkMonitorModule();
    NetworkMonitorModule(const NetworkMonitorModule &rhs);
    NetworkMonitorModule&operator=(const NetworkMonitorModule &rhs);
    ~NetworkMonitorModule();
    const ModuleData update();
};


#endif //FT_GKRELLM_NETWORKMONITORMODULE_HPP
