//
// Created by Victor Vasiliev on 11.11.2017.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "OSInfoMonitorModule.hpp"



const ModuleData OSInfoMonitorModule::update() {
    ModuleData data;

    char info[512];

    FILE *sw_vers = popen("sw_vers", "r");
    while (fgets(info, sizeof(info), sw_vers)) {
        std::string name;
        std::string value;
        std::string string(info);
        std::istringstream iss(string);

        iss >> name;
        name = name.substr(0, name.size() - 1);
        while (!iss.eof()) {
            std::string tmp;
            iss >> tmp;
            if(!tmp.empty()) {
                value += (" " + tmp);
            }
        }
        data.addLabel(name, value);
    }
    pclose(sw_vers);
    return data;
}

OSInfoMonitorModule::~OSInfoMonitorModule() {

}

OSInfoMonitorModule::OSInfoMonitorModule() : AMonitorModule::AMonitorModule("OS Info") {

}

OSInfoMonitorModule::OSInfoMonitorModule(const OSInfoMonitorModule &rhs) : AMonitorModule::AMonitorModule(rhs.name){

}

OSInfoMonitorModule& OSInfoMonitorModule::operator=(const OSInfoMonitorModule &rhs)
{
    name = rhs.name;
    return *this;
}
