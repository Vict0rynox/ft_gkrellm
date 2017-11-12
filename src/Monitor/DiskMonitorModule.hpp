//
// Created by Victor Vasiliev on 11/12/17.
//

#ifndef FT_GKRELLM_DISKMONITORMODULE_HPP
#define FT_GKRELLM_DISKMONITORMODULE_HPP


#include "AMonitorModule.hpp"

class DiskMonitorModule : public AMonitorModule {
public:
    DiskMonitorModule();
    ~DiskMonitorModule();

    const ModuleData update();
};


#endif //FT_GKRELLM_DISKMONITORMODULE_HPP
