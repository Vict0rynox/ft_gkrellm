//
// Created by Victor Vasiliev on 11.11.2017.
//

#ifndef FT_GKRELLM_CPUMONITORMODULE_HPP
#define FT_GKRELLM_CPUMONITORMODULE_HPP


#include "AMonitorModule.hpp"


class CPUMonitorModule : public AMonitorModule {
private:
    unsigned long long _previousTotalTicks;
    unsigned long long _previousIdleTicks;
protected:
    std::map<std::string, std::string> cpuInfos;

    float getLoadCPU();

    float calculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks);

public:
    typedef std::map<std::string, std::string>::const_iterator const_iterator;

    CPUMonitorModule();

    ~CPUMonitorModule();

    const ModuleData update();

    void addCpuInfo(const std::string &fieldName, const std::string &statsName);
};


#endif //FT_GKRELLM_CPUMONITORMODULE_HPP
