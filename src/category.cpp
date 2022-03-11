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

Category::Category() {}

Category::Category(const std::string& identifier) : ident(identifier) {}

void Category::setIdent(const std::string& identifier) {
    ident = identifier;
}

std::string& Category::getIdent() {
    return ident;
}


std::map<std::string, Item>& Category::getItems() {
    return items;
}

Item& Category::getItem(const std::string& itemIdentifier) {
    if (items.count(itemIdentifier) == 1) {
        return items.at(itemIdentifier);
    } else {
        throw std::out_of_range(
            "Unable to get item. Item with the identifier " + itemIdentifier 
                + " does not exist");
    }
}

void Category::load(nlohmann::json::iterator& category) {
    nlohmann::json categoryJSON = category.value();
    nlohmann::json::iterator item;
    for (item = categoryJSON.begin(); item != categoryJSON.end(); ++item) {
        newItem(item.key()).load(item);
    }
}

Item& Category::newItem(const std::string& itemIdentifier) {
    if (items.count(itemIdentifier) != 1) {
        Item item(itemIdentifier);
        try {
            addItem(item);
        } catch(const std::exception& ex) {
            throw std::runtime_error("Unable to add item with identifer "
                + item.getIdent());
        }
    } 
    return items.at(itemIdentifier);
}

bool Category::addItem(Item& item) {
    if (items.count(item.getIdent()) != 1) {
        try {
            items.emplace(item.getIdent(), item);
        } catch(const std::exception& ex) {
            throw std::runtime_error("Unable to add item with identifer "
                + item.getIdent());
        }
        return true;
    } else {
        Item chosenItem = items.at(item.getIdent());
        for (auto& entry : item.getEntries()) {
            chosenItem.addEntry(entry);
        }
        return false;
    }
}

bool Category::deleteItem(const std::string& itemIdentifier) {
    if (items.count(itemIdentifier) == 1) {
        return items.erase(itemIdentifier);
    } else {
        throw std::out_of_range(
            "Unable to delete item. Item with the identifier " + itemIdentifier 
                + " does not exist");
    }
}

unsigned int Category::size() {
    return items.size();
}

bool Category::empty() {
    return items.empty();
}

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

std::string Category::str() {
    std::stringstream ss;
    ss << json();
    return ss.str();
}

nlohmann::json Category::json() {
    nlohmann::json json;
    for (auto& item : items) {
        json[item.second.getIdent()] = item.second.json(); 
    }
    return json;
}
