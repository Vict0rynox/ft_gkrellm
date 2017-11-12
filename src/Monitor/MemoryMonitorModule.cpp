//
// Created by Victor Vasiliev on 11/12/17.
//

#include <sys/sysctl.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>
#include "MemoryMonitorModule.hpp"
#include "../Utils/utils.hpp"


const ModuleData MemoryMonitorModule::update() {
    ModuleData data;

    updateMemory();
    data.addLabel("Total Memory", Utils::to_string(static_cast<float>(totalMemory) / (1024 * 1024)) + "Mb");
    data.addLabel("Free Memory", Utils::to_string(static_cast<float>(freeMemory) / (1024 * 1024)) + "Mb");
    data.addLabel("Used Memory", Utils::to_string(static_cast<float>(usedMemory) / (1024 * 1024)) + "Mb");

    data.addLabel("Wired Memory", Utils::to_string(static_cast<float>(wiredMemory) / (1024 * 1024)) + "Mb");
    data.addLabel("Swap Memory", getSwapMemory());

    data.addDatum("Used Memory", static_cast<float>(usedMemory) / totalMemory);
    data.addDatum("Free Memory", static_cast<float>(freeMemory) / totalMemory);
    return data;
}

std::string MemoryMonitorModule::getSwapMemory() const {

    size_t length;
    sysctlbyname("vm.swapusage", NULL, &length, NULL, 0);
    char *swapMemory = new char[length]();
    sysctlbyname("vm.swapusage", swapMemory, &length, NULL, 0);
    std::string str(swapMemory);
    delete[]swapMemory;
    return str;
}


MemoryMonitorModule::MemoryMonitorModule()
        : AMonitorModule::AMonitorModule("Memory monitor"), totalMemory(getTotalMemory()), freeMemory(), usedMemory() {
}

int64_t MemoryMonitorModule::getTotalMemory() const {
    int mib[2];
    size_t length;
    int64_t physical_memory;
    mib[0] = CTL_HW;
    mib[1] = HW_MEMSIZE;
    length = sizeof(int64_t);
    sysctl(mib, 2, &physical_memory, &length, NULL, 0);
    return physical_memory;
}


MemoryMonitorModule::~MemoryMonitorModule() {

}

void MemoryMonitorModule::updateMemory() {
    vm_size_t page_size;
    mach_port_t mach_port;
    mach_msg_type_number_t count;
    vm_statistics64_data_t vm_stats = {};

    mach_port = mach_host_self();
    count = sizeof(vm_stats) / sizeof(natural_t);
    if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
        KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
                                          reinterpret_cast<host_info64_t>(&vm_stats), &count)) {
        usedMemory = (static_cast<int64_t>(vm_stats.active_count) +
                      static_cast<int64_t>( vm_stats.inactive_count)) * static_cast<int64_t>(page_size);
        wiredMemory = static_cast<int64_t>(vm_stats.wire_count) * static_cast<int64_t>(page_size);

        freeMemory = totalMemory - usedMemory;
    }
}

MemoryMonitorModule::MemoryMonitorModule(const MemoryMonitorModule &rhs) :
        AMonitorModule::AMonitorModule(rhs.name),
        totalMemory(rhs.totalMemory),
        freeMemory(rhs.freeMemory),
        usedMemory(rhs.usedMemory),
        wiredMemory(rhs.wiredMemory) {
}

MemoryMonitorModule &MemoryMonitorModule::operator=(const MemoryMonitorModule &rhs) {
    name = rhs.name;
    totalMemory = rhs.totalMemory;
    freeMemory = rhs.freeMemory;
    usedMemory = rhs.usedMemory;
    wiredMemory = rhs.wiredMemory;
    return *this;
}

