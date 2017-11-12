//
// Created by Victor Vasiliev on 11/10/17.
//

#ifndef FT_GKRELLM_IMONITORDISPLAY_HPP
#define FT_GKRELLM_IMONITORDISPLAY_HPP


#include <string>
#include <map>
#include "../Monitor/IMonitorModule.hpp"

class IMonitorDisplay {
public:
    virtual ~IMonitorDisplay(){};
    virtual void addMonitorModule(IMonitorModule *monitorModule) = 0;
    virtual void removeMonitorModule(std::string monitorModuleName) = 0;
    virtual int run() = 0;

};


#endif //FT_GKRELLM_IMONITORDISPLAY_HPP
