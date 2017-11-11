//
// Created by Victor Vasiliev on 11.11.2017.
//

#ifndef FT_GKRELLM_ABSTRACTMONITORMODULE_HPP
#define FT_GKRELLM_ABSTRACTMONITORMODULE_HPP


#include "IMonitorModule.hpp"

class AMonitorModule : public IMonitorModule {
protected:
    std::string name;
public:
    AMonitorModule();
    virtual ~AMonitorModule();
    AMonitorModule(std::string name);
    AMonitorModule(const AMonitorModule &rhs);
    AMonitorModule&operator=(const AMonitorModule &rhs);
    const std::string &getName() const;
};


#endif //FT_GKRELLM_ABSTRACTMONITORMODULE_HPP
