//
// Created by Victor Vasiliev on 11/10/17.
//

#ifndef FT_GKRELLM_DATETIMEMONITORMODULE_HPP
#define FT_GKRELLM_DATETIMEMONITORMODULE_HPP


#include "IMonitorModule.hpp"
#include "../Data/ModuleData.hpp"
#include "AMonitorModule.hpp"

class DateTimeMonitorModule : public AMonitorModule {
public:
    DateTimeMonitorModule();
    DateTimeMonitorModule(const DateTimeMonitorModule &rhs);
    DateTimeMonitorModule&operator=(const DateTimeMonitorModule &rhs);
    ~DateTimeMonitorModule();
    virtual const ModuleData update() const;
};


#endif //FT_GKRELLM_DATETIMEMONITORMODULE_HPP
