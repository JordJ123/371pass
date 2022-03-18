// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 1910397
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------

#include <iostream>
#include <sstream>
#include <string>
#include "lib_json.hpp"
#include "category.h"

//Creates a category with no identifier
Category::Category() {}

//Creates a category with the given identifier
Category::Category(const std::string& identifier) : ident(identifier) {}

//Sets the identifer of the category
void Category::setIdent(const std::string& identifier) {
    ident = identifier;
}

//Gets the identifier of the category
std::string& Category::getIdent() {
    return ident;
}

//Gets all the items from the category
std::map<std::string, Item>& Category::getItems() {
    return items;
}

//Gets the item with the given identifier from the category
Item& Category::getItem(const std::string& itemIdentifier) {
    if (items.count(itemIdentifier) == 1) {
        return items.at(itemIdentifier);
    } else {
        throw std::out_of_range("Error: invalid item argument(s).");
    }
}

//Loads items into the category from the given database json
void Category::load(nlohmann::json::iterator& category) {
    nlohmann::json categoryJSON = category.value();
    nlohmann::json::iterator item;
    for (item = categoryJSON.begin(); item != categoryJSON.end(); ++item) {
        newItem(item.key()).load(item);
    }
}

//Creates a new item with the given identifier and adds it to the category
Item& Category::newItem(const std::string& itemIdentifier) {
    if (items.count(itemIdentifier) != 1) {
        Item item(itemIdentifier);
        try {
            addItem(item);
        } catch(const std::exception& ex) {
            throw std::runtime_error("Error: Unable to add item with identifer "
                + item.getIdent() + ".");
        }
    } 
    return items.at(itemIdentifier);
}

//Adds the item given to the category
bool Category::addItem(Item& item) {
    if (items.count(item.getIdent()) != 1) {
        try {
            items.emplace(item.getIdent(), item);
        } catch(const std::exception& ex) {
            throw std::runtime_error("Error: Unable to add item with identifer "
                + item.getIdent() + ".");
        }
        return true;
    } else {
        Item chosenItem = items.at(item.getIdent());
        for (auto& entry : item.getEntries()) {
            chosenItem.addEntry(entry.first, entry.second);
        }
        return false;
    }
}

//Deletes the item with the given identifier from the category
bool Category::deleteItem(const std::string& itemIdentifier) {
    if (items.count(itemIdentifier) == 1) {
        return items.erase(itemIdentifier);
    } else {
        throw std::out_of_range("Error: invalid item argument(s).");
    }
}

//Gets how many items are in the category
unsigned int Category::size() {
    return items.size();
}

//Gets true if there are no items in the category
bool Category::empty() {
    return items.empty();
}

//Gets the category in JSON string format
std::string Category::str() {
    std::stringstream ss;
    ss << json();
    return ss.str();
}

//Gets the category in JSON format
nlohmann::json Category::json() {
    nlohmann::json json;
    for (auto& item : items) {
        json[item.second.getIdent()] = item.second.json(); 
    }
    return json;
}

//Checks if the two categories are equal based on thier identifiers and items
bool operator==(const Category& lhs, const Category& rhs) {
    if (lhs.ident.compare(rhs.ident) == 0) {
        for (const auto& lhsItem : lhs.items) {
            for (const auto& rhsItem : rhs.items) {
                if (!(lhsItem == rhsItem)) {
                    return false;        
                }
            }
        }
    }
    return true;
}
