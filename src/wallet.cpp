// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 1910397
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------

#include <fstream>
#include <iostream>
#include "lib_json.hpp"
#include "category.h"
#include "item.h"
#include "wallet.h"

using json = nlohmann::json;

Wallet::Wallet() {}

Category& Wallet::getCategory(const std::string& categoryIdentifier) {
    if (categories.count(categoryIdentifier) == 1) {
        return categories.at(categoryIdentifier);
    } else {
        throw std::runtime_error("Unable to get category with identifer "
            + categoryIdentifier);
    }
}

void Wallet::load(const std::string& filename) {
    std::ifstream databaseFile;
    databaseFile.open(filename + ".json");
    if (!databaseFile.is_open()) {
        std::cerr << filename << ".json could not be open or does not exist\n";
        std::exit(1);
    }
    json wallet = json::parse(databaseFile);
    json::iterator category;
    for (category = wallet.begin(); category != wallet.end(); ++category) {
        newCategory(category.key());
    }
    databaseFile.close();
}

Category& Wallet::newCategory(const std::string& categoryIdentifier) {
    if (categories.count(categoryIdentifier) != 1) {
        Category category(categoryIdentifier);
        try {
            addCategory(category);
        } catch(const std::exception& ex) {
            throw std::runtime_error("Unable to add category with identifer "
                + category.getIdent());
        }
    } 
    return categories.at(categoryIdentifier);
}

bool Wallet::addCategory(Category& category) {
    if (categories.count(category.getIdent()) != 1) {
        try {
            categories.emplace(category.getIdent(), category);
        } catch(const std::exception& ex) {
            throw std::runtime_error("Unable to add category with identifer "
                + category.getIdent());
        }
        return true;
    } else {
        //Add Categories Items
        return false;
    }
}

bool Wallet::deleteCategory(const std::string& categoryIdentifier) {
    if (categories.count(categoryIdentifier) == 1) {
        return categories.erase(categoryIdentifier);
    } else {
        throw std::runtime_error("Unable to delete category with identifer "
            + categoryIdentifier);
    }
}

unsigned int Wallet::size() {
    return categories.size();
}

bool Wallet::empty() {
    return categories.empty();
}

// TODO Write a function ,save, that takes one parameter, the path of the file
//  to write the database to. The function should serialise the Wallet object
//  as JSON.
// Example:
//  Wallet wObj{};
//  wObj.load("database.json");
//  wObj.save("database.json");

// TODO Write an == operator overload for the Wallet class, such that two
//  Wallet objects are equal only if they have the exact same data.
// Example:
//  Wallet wObj1{};
//  Wallet wObj2{};
//  if(wObj1 == wObj2) {
//    ...
//  }

// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the Wallet.
// Hint:
//  See the coursework specification for how this JSON should look.
// Example:
//  Wallet wObj{};
//  std::string s = wObj.str();
