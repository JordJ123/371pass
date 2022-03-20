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

// TODO Write a constructor that takes one parameter, a string identifier
//  and initialises the object and member data.
//
// Example:
//  Category c{"categoryIdent"};
Category::Category(const std::string& identifier) : ident(identifier) {}

// TODO Write a function, size, that takes no parameters and returns an unsigned
//  int of the number of Items in the Category contains.
//
// Example:
//  Category c{"categoryIdent"};
//  auto size = c.size();
const unsigned int Category::size() const {
    return items.size();
}

// TODO Write a function, empty, that takes no parameters and returns true
//  if the number of Items in the Category is zero, false otherwise.
//
// Example:
//  Category c{"categoryIdent"};
//  auto empty = c.empty();
const bool Category::empty() const {
    return items.empty();
}

// TODO Write a function, getIdent, that returns the identifier for the
//  Category.
//
// Example:
//  Category cObj{"categoryIdent"};
//  auto ident = cObj.getIdent();
const std::string& Category::getIdent() {
    return ident;
}

// TODO Write a function, setIdent, that takes one parameter, a string for a new
//  Category identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.setIdent("categoryIdent2");
void Category::setIdent(const std::string& identifier) {
    ident = identifier;
}

// TODO Write a function, newItem, that takes one parameter, an Item identifier,
//  (a string) and returns the Item object as a reference. If an object with the
//  same identifier already exists, then the existing object should be returned.
//  Throw a std::runtime_error if the Item object cannot be inserted into the
//  container for whatever reason.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("itemIdent");
Item& Category::newItem(const std::string& itemIdentifier) {
    if (items.count(itemIdentifier) != 1) {
        Item item(itemIdentifier);
        try {
            addItem(item);
        } catch(const std::exception& ex) {
            throw std::runtime_error("Error: unable to add item with identifer "
                + item.getIdent() + ".");
        }
    } 
    return items.at(itemIdentifier);
}

// TODO Write a function, addItem, that takes one parameter, an Item object,
//  and returns true if the object was successfully inserted. If an object with
//  the same identifier already exists, then the contents should be merged and
//  return false.
//
// Example:
//  Category cObj{"categoryIdent"};
//  Item iObj{"itemIdent"};
//  cObj.addItem(iObj);
const bool Category::addItem(Item& item) {
    if (items.count(item.getIdent()) != 1) {
        try {
            items.emplace(item.getIdent(), item);
        } catch(const std::exception& ex) {
            throw std::runtime_error("Error: unable to add item with identifer "
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

//Gets all the items from the category
std::map<std::string, Item>& Category::getItems() {
    return items;
}

// TODO Write a function, getItem, that takes one parameter, an Item
//  identifier (a string) and returns the Item as a reference. If no Item
//  exists, throw an appropriate exception.
//
// Hint:
//  See the test scripts for the exception expected.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("itemIdent");
//  auto iObj = cObj.getItem("itemIdent");
Item& Category::getItem(const std::string& itemIdentifier) {
    if (items.count(itemIdentifier) == 1) {
        return items.at(itemIdentifier);
    } else {
        throw std::out_of_range("Error: invalid item argument(s).");
    }
}

// TODO Write a function, deleteItem, that takes one parameter, an Item
//  identifier (a string), deletes it from the container, and returns true if
//  the Item was deleted. If no Item exists, throw an appropriate exception.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("itemIdent");
//  bool result = cObj.deleteItem("itemIdent");
const bool Category::deleteItem(const std::string& itemIdentifier) {
    if (items.count(itemIdentifier) == 1) {
        return items.erase(itemIdentifier);
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

// TODO Write an == operator overload for the Category class, such that two
//  Category objects are equal only if they have the same identifier and same
//  Items.
//
// Example:
//  Category cObj1{"categoryIdent1"};
//  cObj1.newItem("itemIdent");
//  Category cObj2{"categoryIdent2"};
//  if(cObj1 == cObj2) {
//    ...
//  }
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

// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the Category.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Category cObj{"categoryIdent"};
//  std::string s = cObj.str();
const std::string Category::str() {
    std::stringstream ss;
    ss << json();
    return ss.str();
}

//Gets the category in JSON format
const nlohmann::json Category::json() {
    nlohmann::json json;
    for (auto& item : items) {
        json[item.second.getIdent()] = item.second.json(); 
    }
    return json;
}
