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

// TODO Write a constructor that takes one parameter, a string identifier
//  and initialises the object and member data.
//
// Example:
//  Item iObj{"identIdent"};
Item::Item(const std::string& identifier) : ident(identifier) {}

// TODO Write a function, size, that takes no parameters and returns an unsigned
//  int of the number of entries in the Item contains.
//
// Example:
//  Item iObj{"identIdent"};
//  auto size = iObj.size();
const unsigned int Item::size() const {
    return entries.size();
}

// TODO Write a function, empty, that takes no parameters and returns true
//  if the number of entries in the Item is zero, false otherwise.
//
// Example:
//  Item iObj{"identIdent"};
//  auto empty = iObj.empty();
const bool Item::empty() const {
    return entries.empty();
}

// TODO Write a function, setIdent, that takes one parameter, a string for a new
//  Item identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.setIdent("identIdent2");
void Item::setIdent(const std::string& identifier) {
    ident = identifier;
}

// TODO Write a function, getIdent, that returns the identifier for the Item.
//
// Example:
//  Item iObj{"identIdent"};
//  auto ident = iObj.getIdent();
const std::string& Item::getIdent() {
    return ident;
}

// TODO Write a function, addEntry, that takes two parameters, an entry
//  key and value and returns true if the entry was inserted into the
//  container or false if the entry already existed and was replaced.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.addEntry("key", "value");
const bool Item::addEntry(const std::string& key, const std::string& value) {
    if (key == "") {
        throw std::out_of_range("Error: invalid entry argument(s).");
    }
    bool newEntry = entries.count(key) != 1;
    if (!newEntry) {
        deleteEntry(key);
    }
    entries.emplace(key, value);
    return newEntry;
}

//Gets all the entries from the item
std::map<std::string, std::string>& Item::getEntries() {
    return entries;
}

// TODO Write a function, getEntry, that takes one parameter, an entry
//  key and returns it's value. If no entry exists, throw an appropriate
//  exception.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.addEntry("key", "value");
//  auto value = iObj.getEntry("key");
const std::string& Item::getEntry(const std::string& key) {
    if (entries.count(key) == 1) {
        return entries.at(key);
    } else {
        throw std::out_of_range("Error: invalid entry argument(s).");
    }
}

//Updates the entry with the given key with the new key and new value
const bool Item::updateEntry(const std::string& oldKey, 
    const std::string& newKey, 
    const std::string& newValue) {
    if (entries.count(oldKey) == 1) {
        deleteEntry(oldKey);
        return addEntry(newKey, newValue);
    } else {
        throw std::out_of_range("Error: invalid entry argument(s).");
    }
}

//Updates the entry with the given key with the new key
const bool Item::updateEntryKey(const std::string& oldKey, 
    const std::string& newKey) {
    if (entries.count(oldKey) == 1) {
        std::string value = getEntry(oldKey);
        deleteEntry(oldKey);
        return addEntry(newKey, value);
    } else {
        throw std::out_of_range("Error: invalid entry argument(s).");
    }
}

//Updates the entry with the given key with the new value
const bool Item::updateEntryValue(const std::string& key, 
    const std::string& newValue) {
    if (entries.count(key) == 1) {
        return addEntry(key, newValue);
    } else {
        throw std::out_of_range("Error: invalid entry argument(s).");
    }
}

// TODO Write a function, deleteEntry, that takes one parameter, an entry
//  key, deletes it from the container, and returns true if the Item was
//  deleted. If no entry exists, throw an appropriate exception.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.addEntry("key", "value");
//  iObj.deleteEntry("key");
const bool Item::deleteEntry(const std::string& key) {
    if (entries.count(key) == 1) {
        entries.erase(key);
        return true;
    } else {
        throw std::out_of_range("Error: invalid entry argument(s).");
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

// TODO Write an == operator overload for the Item class, such that two
//  Item objects are equal only if they have the same identifier and same
//  entries.
//
// Example:
//  Item iObj1{"identIdent"};
//  iObj1.addEntry("key", "value");
//  Item iObj2{"identIdent2"};
//  if(iObj1 == iObj2) {
//    ...
//  }
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

// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the Item.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Item iObj{"itemIdent"};
//  std::string s = iObj.str();
const std::string Item::str() const {
    std::stringstream ss;
    ss << json();
    return ss.str();
}

//Gets the item in JSON format
const nlohmann::json Item::json() const {
    nlohmann::json json;
    for (const auto& entry : entries) {
        json[entry.first] = entry.second;
    }
    return json;
}
