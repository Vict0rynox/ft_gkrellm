//
// Created by Victor Vasiliev on 11.11.2017.
//

#ifndef FT_GKRELLM_CPUMONITORMODULE_HPP
#define FT_GKRELLM_CPUMONITORMODULE_HPP


#include "AMonitorModule.hpp"


class CPUMonitorModule : public AMonitorModule {
private:
    unsigned long long _previousTotalTicks[3];
    unsigned long long _previousStateTicks[3];
protected:
    std::map<std::string, std::string> cpuInfos;
    float getLoadCPU(int stateType);
    float calculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks, int stateType);
public:
    typedef std::map<std::string, std::string>::const_iterator const_iterator;

    CPUMonitorModule();

    ~CPUMonitorModule();

    const ModuleData update();

    void addCpuInfo(const std::string &fieldName, const std::string &statsName);
};


#endif //FT_GKRELLM_CPUMONITORMODULE_HPP
