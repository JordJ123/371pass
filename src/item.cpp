// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 1910397
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include "lib_json.hpp"
#include "item.h"

Item::Item() {}

Item::Item(const std::string& identifier) : ident(identifier) {}

void Item::setIdent(const std::string& identifier) {
    ident = identifier;
}

std::string& Item::getIdent() {
    return ident;
}

std::map<std::string, std::string>& Item::getEntries() {
    return entries;
}

std::string& Item::getEntry(const std::string& key) {
    if (entries.count(key) == 1) {
        return entries.at(key);
    } else {
        throw std::out_of_range("Unable to get entry. Entry with the key " 
            + key + " does not exist");
    }
}

void Item::load(nlohmann::json::iterator& item) {
    nlohmann::json itemJSON = item.value();
    nlohmann::json::iterator entry;
    for (entry = itemJSON.begin(); entry != itemJSON.end(); ++entry) {
        std::string key = entry.key();
        std::string value = entry.value();
        addEntry(key, value);
    }
}

bool Item::addEntry(const std::string& key, const std::string& value) {
    if (entries.count(key) != 1) {
        entries.emplace(key, value);
        return true;
    } else {
        entries.emplace(key, value);
        return false;
    }
}

bool Item::deleteEntry(std::string& key) {
    if (entries.count(key) == 1) {
        entries.erase(key);
        return true;
    } else {
        throw std::out_of_range("Unable to delete entry. Entry with the key " 
            + key + " does not exist");
        return false;
    }
}

unsigned int Item::size() {
    return entries.size();
}

bool Item::empty() {
    return entries.empty();
}

bool operator==(const Item& lhs, const Item& rhs) {
    if (lhs.ident.compare(rhs.ident) == 0) {
        for (const auto& lhsEntry : lhs.entries) {
            for (const auto& rhsEntry : rhs.entries) {
                if (lhsEntry.first.compare(rhsEntry.first) != 0
                    && lhsEntry.second.compare(rhsEntry.second) != 0) {
                    return false;        
                }
            }
        }
    }
    return true;
}

std::string Item::str() {
    std::stringstream ss;
    ss << json();
    return ss.str();
}

nlohmann::json Item::json() {
    nlohmann::json json;
    for (const auto& entry : entries) {
        json[entry.first] = entry.second;
    }
    return json;
}

