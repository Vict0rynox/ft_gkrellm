//
// Created by Victor Vasiliev on 11/10/17.
//

#ifndef FT_GKRELLM_IMONITORMODULE_HPP
#define FT_GKRELLM_IMONITORMODULE_HPP

#include <string>
#include "../Data/ModuleData.hpp"

class IMonitorModule {
public:
    virtual const std::string& getName() const = 0;
    virtual const ModuleData update() const = 0;

};


#endif //FT_GKRELLM_IMONITORMODULE_HPP
