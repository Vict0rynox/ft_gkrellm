//
// Created by Victor Vasiliev on 11/12/17.
//

#include "AMonitorDisplay.hpp"

void AMonitorDisplay::addMonitorModule(IMonitorModule *monitorModule) {
    //monitor hasen't
    if (monitorModules.find(monitorModule->getName()) == monitorModules.end()) {
        monitorModules[monitorModule->getName()] = monitorModule;
    }
}

void AMonitorDisplay::removeMonitorModule(std::string monitorModuleName) {
    std::map<std::string, IMonitorModule *>::iterator itr = monitorModules.find(monitorModuleName);
    if (itr != monitorModules.end()) {
        monitorModules.erase(itr);
    }
}

AMonitorDisplay::AMonitorDisplay() : monitorModules() {

}

AMonitorDisplay::~AMonitorDisplay() {
    monitorModules.clear();
}

AMonitorDisplay::AMonitorDisplay(const AMonitorDisplay &rhs) : monitorModules(rhs.monitorModules) {

}

AMonitorDisplay &AMonitorDisplay::operator=(const AMonitorDisplay &rhs) {
    monitorModules = rhs.monitorModules;
    return *this;
}
