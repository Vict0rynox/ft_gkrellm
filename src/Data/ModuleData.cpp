//
// Created by Victor Vasiliev on 11.11.2017.
//

#include "ModuleData.hpp"



void ModuleData::addLabel(std::string name, std::string value) {
    labels[name] = value;
}

ModuleData::ModuleData() :labels(), datums(){

}

std::map<std::string, std::string>::const_iterator ModuleData::getLabelsIterator() const {
    return labels.begin();
}

ModuleData::labels_const_iterator ModuleData::getLabelsIteratorEnd() const {
    return labels.end();
}

void ModuleData::addDatum(std::string name, float value) {
    datums[name] = value;
}

ModuleData::datums_const_iterator ModuleData::getDatumsIterator() const {
    return datums.begin();
}

ModuleData::datums_const_iterator ModuleData::getDatumsIteratorEnd() const {
    return datums.end();
}
