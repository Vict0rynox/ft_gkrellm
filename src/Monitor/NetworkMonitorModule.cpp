//
// Created by Victor Vasiliev on 11/12/17.
//

#include <sstream>
#include "NetworkMonitorModule.hpp"

const ModuleData NetworkMonitorModule::update() {
    ModuleData data;

    FILE *in;
    std::string info;
    char buffer[1024];
    if (!(in = popen("top -l 1 | grep -E \"^Networks\"", "r"))) {
        throw std::exception();
    }
    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        info = std::string(buffer);
        break ;
    }
    pclose(in);
    //"Networks: packets: 7514990/9118M in, 7169235/2066M out.\n"
    std::istringstream netStream(info);
    std::string tmp;

    netStream >> tmp; //skip name
    netStream >> tmp; //skip packets;

    netStream >> tmp;//get in packets
    data.addLabel("Packets in", tmp);
    netStream >> tmp; //skip in

    netStream >> tmp; //get out packets
    data.addLabel("Packets out", tmp);
    return data;
}

NetworkMonitorModule::NetworkMonitorModule() : AMonitorModule::AMonitorModule("Network Monitor") {

}

NetworkMonitorModule::~NetworkMonitorModule() {

}

NetworkMonitorModule::NetworkMonitorModule(const NetworkMonitorModule &rhs) : AMonitorModule::AMonitorModule(rhs.name){

}

NetworkMonitorModule& NetworkMonitorModule::operator=(const NetworkMonitorModule &rhs)
{
    name = rhs.name;
    return *this;
}
