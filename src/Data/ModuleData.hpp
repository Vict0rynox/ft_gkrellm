//
// Created by Victor Vasiliev on 11.11.2017.
//

#ifndef FT_GKRELLM_MODULEDATA_HPP
#define FT_GKRELLM_MODULEDATA_HPP


#include <string>
#include <map>

class ModuleData {
protected:
    std::map<std::string, std::string> labels;
    struct Data {
        int x;
    } dynamicData;
public:
    typedef std::map<std::string, std::string>::const_iterator const_iterator;
    ModuleData();
    const Data& getData() const;
    void addLabel(std::string name, std::string value);
    const_iterator getLabelsIterator() const;
    const_iterator getLabelsIteratorEnd() const;

};


#endif //FT_GKRELLM_MODULEDATA_HPP
