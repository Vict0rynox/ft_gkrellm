//
// Created by Victor Vasiliev on 11.11.2017.
//

#include <fstream>
#include "OSInfoMonitorModule.hpp"



const ModuleData OSInfoMonitorModule::update() const {
    ModuleData data;

    std::string name;
    std::string value;

    std::ifstream swVerStream;
    swVerStream.open("sw_vers", std::ios::in);
    while (!swVerStream.eof()){
        swVerStream >> name;
        swVerStream >> value;
        data.addLabel(name, value);
    }
    swVerStream.close();
    return data;
}

OSInfoMonitorModule::~OSInfoMonitorModule() {

}

OSInfoMonitorModule::OSInfoMonitorModule() : AMonitorModule::AMonitorModule("OS Info") {

}
