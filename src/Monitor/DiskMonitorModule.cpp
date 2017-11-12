//
// Created by Victor Vasiliev on 11/12/17.
//

#include <sstream>
#include "DiskMonitorModule.hpp"

const ModuleData DiskMonitorModule::update() {
    ModuleData data;

    FILE *in;
    std::string info;
    char buffer[1024];
    if (!(in = popen("top -l 1 | grep -E \"^Disks\"", "r"))) {
        throw std::exception();
    }
    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        info = std::string(buffer);
        break ;
    }
    pclose(in);
    //Disks: 996317/27G read, 604026/19G written.
    std::istringstream netStream(info);
    std::string tmp;

    netStream >> tmp; //skip name

    netStream >> tmp;//get in read
    data.addLabel("Disks read", tmp);
    netStream >> tmp; //skip in

    netStream >> tmp; //get out written
    data.addLabel("Disks written", tmp);
    return data;
}

DiskMonitorModule::~DiskMonitorModule() {

}

DiskMonitorModule::DiskMonitorModule() : AMonitorModule::AMonitorModule("Disk Info Module") {

}

DiskMonitorModule::DiskMonitorModule(const DiskMonitorModule &rhs) : AMonitorModule::AMonitorModule(rhs) {

}

DiskMonitorModule &DiskMonitorModule::operator=(const DiskMonitorModule &rhs) {
    name = rhs.name;
    return *this;
}
