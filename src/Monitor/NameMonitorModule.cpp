//
// Created by Victor Vasiliev on 11.11.2017.
//

#include <zconf.h>
#include "NameMonitorModule.hpp"

NameMonitorModule::NameMonitorModule() : NameMonitorModule::AMonitorModule("Name Monitor") {

}

const ModuleData NameMonitorModule::update() {
    ModuleData data;

    char tmp[1024];

    gethostname(tmp, 1024);
    std::string hostname(tmp);

    getlogin_r(tmp, 1024);
    std::string username(tmp);

    data.addLabel("Hostname", hostname);
    data.addLabel("Username", username);

    return data;
}

NameMonitorModule::~NameMonitorModule() {

}

NameMonitorModule::NameMonitorModule(const NameMonitorModule &rhs) : AMonitorModule::AMonitorModule(rhs.name){

}

NameMonitorModule& NameMonitorModule::operator=(const NameMonitorModule &rhs)
{
    name = rhs.name;
    return *this;
}
