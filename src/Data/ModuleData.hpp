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
    std::map<std::string, float> datums;
public:
    typedef std::map<std::string, std::string>::const_iterator labels_const_iterator;
    typedef std::map<std::string, float>::const_iterator datums_const_iterator;
    ModuleData();
    void addLabel(std::string name, std::string value);
    void addDatum(std::string name, float value);

    labels_const_iterator getLabelsIterator() const;
    labels_const_iterator getLabelsIteratorEnd() const;

    datums_const_iterator getDatumsIterator() const;
    datums_const_iterator getDatumsIteratorEnd() const;

};


#endif //FT_GKRELLM_MODULEDATA_HPP
