//
// Created by Victor Vasiliev on 11.11.2017.
//

#include <sys/sysctl.h>
#include <iostream>
#include <mach/host_info.h>
#include <mach/mach_host.h>
#include "CPUMonitorModule.hpp"
#include "../Utils/utils.hpp"

const ModuleData CPUMonitorModule::update() {
    ModuleData data;

    CPUMonitorModule::const_iterator itr = cpuInfos.begin();
    for (; itr != cpuInfos.end(); itr++) {
        std::string value;
        std::string name = itr->first;

        const char *path = itr->second.c_str();

        size_t count_len = 0;
        sysctlbyname(path, NULL, &count_len, NULL, 0);
        void *buffer = new char[count_len]();
        sysctlbyname(path, buffer, &count_len, NULL, 0);
        if (count_len == 4) { //int type
            value = Utils::to_string(*(reinterpret_cast<int *>(buffer)));
        } else {
            value = reinterpret_cast<char *>(buffer);
        }
        delete[] reinterpret_cast<char *>(buffer);
        data.addLabel(name, value);
    }
    float cpuIdle = getLoadCPU(CPU_STATE_IDLE);
    float cpuUser = getLoadCPU(CPU_STATE_USER);
    float cpuSystem = getLoadCPU(CPU_STATE_SYSTEM);
    data.addLabel("CPU Idle", Utils::to_string(cpuIdle * 100));
    data.addLabel("CPU User", Utils::to_string(cpuUser * 100));
    data.addLabel("CPU System", Utils::to_string(cpuSystem * 100));

    data.addDatum("CPU Idle", cpuIdle);
    data.addDatum("CPU User", cpuUser);
    data.addDatum("CPU System", cpuSystem);
    return data;
}

CPUMonitorModule::CPUMonitorModule()
        : AMonitorModule::AMonitorModule("CPU Info"), cpuInfos(), _previousTotalTicks(), _previousStateTicks() {
    _previousStateTicks[0] = 0;
    _previousStateTicks[1] = 0;
    _previousStateTicks[2] = 0;
    _previousTotalTicks[0] = 0;
    _previousTotalTicks[1] = 0;
    _previousTotalTicks[2] = 0;
    cpuInfos["Name"] = "machdep.cpu.brand_string";
    cpuInfos["Core"] = "machdep.cpu.core_count";
    cpuInfos["Thread"] = "machdep.cpu.thread_count";
    cpuInfos["Cache size"] = "machdep.cpu.cache.size";
}

CPUMonitorModule::~CPUMonitorModule() {
    cpuInfos.clear();
}

float CPUMonitorModule::getLoadCPU(int stateType) {
    host_cpu_load_info_data_t cpuinfo = {};
    mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
    if (host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (host_info_t) &cpuinfo, &count) == KERN_SUCCESS) {
        unsigned long long totalTicks = 0;
        for (int i = 0; i < 3; i++) {
            totalTicks += cpuinfo.cpu_ticks[i];
        }
        return calculateCPULoad(cpuinfo.cpu_ticks[stateType], totalTicks, stateType);
        //return calculateCPULoad(cpuinfo.cpu_ticks[CPU_STATE_SYSTEM], totalTicks);
    } else return -1.0f;
}

float CPUMonitorModule::calculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks, int stateType) {
    unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks[stateType];
    unsigned long long idleTicksSinceLastTime = idleTicks - _previousStateTicks[stateType];
    float ret =((totalTicksSinceLastTime > 0) ? (static_cast<float>(idleTicksSinceLastTime) / static_cast<float>(totalTicksSinceLastTime)) : 0);
    _previousTotalTicks[stateType] = totalTicks;
    _previousStateTicks[stateType] = idleTicks;
    return ret;
}

void CPUMonitorModule::addCpuInfo(const std::string &fieldName, const std::string &statsName) {
    cpuInfos[fieldName] = statsName;
}
