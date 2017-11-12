//
// Created by Victor Vasiliev on 11/12/17.
//

#ifndef FT_GKRELLM_MEMORYMONITORMODULE_HPP
#define FT_GKRELLM_MEMORYMONITORMODULE_HPP

#include "AMonitorModule.hpp"

class MemoryMonitorModule : public AMonitorModule {
protected:
    int64_t totalMemory;
    int64_t freeMemory;
    int64_t usedMemory;
    int64_t wiredMemory;
    void updateMemory();
    std::string getSwapMemory() const;
public:
    MemoryMonitorModule();
    MemoryMonitorModule(const MemoryMonitorModule &rhs);
    MemoryMonitorModule&operator=(const MemoryMonitorModule &rhs);
    ~MemoryMonitorModule();
    const ModuleData update();
    int64_t getTotalMemory() const;
};


#endif //FT_GKRELLM_MEMORYMONITORMODULE_HPP
