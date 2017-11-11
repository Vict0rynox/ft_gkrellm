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
    float cpuIdle = getLoadCPU() * 100;
    data.addLabel("CPU Idle", Utils::to_string(cpuIdle));
    data.addDatum("CPU Idle", cpuIdle);
    return data;
}

CPUMonitorModule::CPUMonitorModule()
        : AMonitorModule::AMonitorModule("CPU Info"), cpuInfos(), _previousTotalTicks(), _previousIdleTicks() {
    cpuInfos["Name"] = "machdep.cpu.brand_string";
    cpuInfos["Core"] = "machdep.cpu.core_count";
    cpuInfos["Thread"] = "machdep.cpu.thread_count";
    cpuInfos["Cache size"] = "machdep.cpu.cache.size";
}

CPUMonitorModule::~CPUMonitorModule() {
    cpuInfos.clear();
}

float CPUMonitorModule::getLoadCPU() {
    host_cpu_load_info_data_t cpuinfo = {};
    mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
    if (host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (host_info_t) &cpuinfo, &count) == KERN_SUCCESS) {
        unsigned long long totalTicks = 0;
        for (int i = 0; i < CPU_STATE_MAX; i++) {
            totalTicks += cpuinfo.cpu_ticks[i];
        }
        return calculateCPULoad(cpuinfo.cpu_ticks[CPU_STATE_IDLE], totalTicks);
    } else return -1.0f;
}

float CPUMonitorModule::calculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks) {
    unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
    unsigned long long idleTicksSinceLastTime = idleTicks - _previousIdleTicks;
    float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? ((float) idleTicksSinceLastTime) / totalTicksSinceLastTime : 0);
    _previousTotalTicks = totalTicks;
    _previousIdleTicks = idleTicks;
    return ret;
}

void CPUMonitorModule::addCpuInfo(const std::string &fieldName, const std::string &statsName) {
    cpuInfos[fieldName] = statsName;
}
