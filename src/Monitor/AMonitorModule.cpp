//
// Created by Victor Vasiliev on 11.11.2017.
//

#include "AMonitorModule.hpp"

const std::string &AMonitorModule::getName() const {
    return name;
}

AMonitorModule::AMonitorModule(std::string name) : name(name) {

}

AMonitorModule::AMonitorModule() : name() {

}

AMonitorModule::~AMonitorModule() {

}

AMonitorModule::AMonitorModule(const AMonitorModule &rhs) : name(rhs.name){

}

AMonitorModule &AMonitorModule::operator=(const AMonitorModule &rhs) {
    name = rhs.name;
    return *this;
}
