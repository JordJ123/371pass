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

//Creates a item with no identifier
Item::Item() {}

//Creates a item with the given identifier
Item::Item(const std::string& identifier) : ident(identifier) {}

//Sets the identifer of the item
void Item::setIdent(const std::string& identifier) {
    ident = identifier;
}

//Gets the identifier of the item
std::string& Item::getIdent() {
    return ident;
}

//Gets all the entries from the item
std::map<std::string, std::string>& Item::getEntries() {
    return entries;
}

//Gets the entry with the given key from the item
std::string& Item::getEntry(const std::string& key) {
    if (entries.count(key) == 1) {
        return entries.at(key);
    } else {
        throw std::out_of_range("Error: Unable to get entry. Entry with the key" 
            " " + key + " does not exist.");
    }
}

//Loads entries into the item from the given database json
void Item::load(nlohmann::json::iterator& item) {
    nlohmann::json itemJSON = item.value();
    nlohmann::json::iterator entry;
    for (entry = itemJSON.begin(); entry != itemJSON.end(); ++entry) {
        std::string key = entry.key();
        std::string value = entry.value();
        addEntry(key, value);
    }
}

//Creates a new entry with the given key and value and adds it to the item
bool Item::addEntry(const std::string& key, const std::string& value) {
    bool newEntry = entries.count(key) != 1;
    if (!newEntry) {
        deleteEntry(key);
    }
    entries.emplace(key, value);
    return newEntry;
}

//Deletes the entry with the given key from the item
bool Item::deleteEntry(const std::string& key) {
    if (entries.count(key) == 1) {
        entries.erase(key);
        return true;
    } else {
        throw std::out_of_range("Error: Unable to delete entry. Entry with the "
            "key " + key + " does not exist.");
    }
}

//Gets how many entries are in the item
unsigned int Item::size() {
    return entries.size();
}

//Gets true if there are no entries in the item
bool Item::empty() {
    return entries.empty();
}

//Gets the item in JSON string format
std::string Item::str() {
    std::stringstream ss;
    ss << json();
    return ss.str();
}

//Gets the item in JSON format
nlohmann::json Item::json() {
    nlohmann::json json;
    for (const auto& entry : entries) {
        json[entry.first] = entry.second;
    }
    return json;
}

//Checks if the two items are equal based on thier identifiers and entries
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
