//
// Created by Victor Vasiliev on 11/10/17.
//

#include "DateTimeMonitorModule.hpp"


DateTimeMonitorModule::DateTimeMonitorModule() : AMonitorModule::AMonitorModule("DateTime") {

}

DateTimeMonitorModule::~DateTimeMonitorModule() {
}

DateTimeMonitorModule::DateTimeMonitorModule(const DateTimeMonitorModule &rhs) : AMonitorModule::AMonitorModule(rhs.name) {

}

DateTimeMonitorModule &DateTimeMonitorModule::operator=(const DateTimeMonitorModule &rhs) {
    name = rhs.name;
    return *this;
}

const ModuleData DateTimeMonitorModule::update()  {
    time_t tmpTime = time(nullptr);
    std::string currentTime(ctime(&tmpTime));
    ModuleData data;
    data.addLabel("Date/Time", currentTime);
    return data;
}

