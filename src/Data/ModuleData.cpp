//
// Created by Victor Vasiliev on 11.11.2017.
//

#include "ModuleData.hpp"

const ModuleData::Data &ModuleData::getData() const {
    return dynamicData;
}

void ModuleData::addLabel(std::string name, std::string value) {
    labels[name] = value;
}

ModuleData::ModuleData() :dynamicData(), labels() {

}

std::map<std::string, std::string>::const_iterator ModuleData::getLabelsIterator() const {
    return labels.begin();
}

ModuleData::const_iterator ModuleData::getLabelsIteratorEnd() const {
    return labels.end();
}
