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
#include <sstream>
#include "lib_json.hpp"
#include "category.h"
#include "item.h"
#include "wallet.h"

//Creates a wallet
Wallet::Wallet() {}

//Gets all the categories from the wallet
std::map<std::string, Category>& Wallet::getCategories() {
    return categories;
}

//Gets the category with the given identifier from the wallet
Category& Wallet::getCategory(const std::string& categoryIdentifier) {
    if (categories.count(categoryIdentifier) == 1) {
        return categories.at(categoryIdentifier);
    } else {
        throw std::out_of_range(
            "Unable to get category. Item with the identifier " 
                + categoryIdentifier + " does not exist");
    }
}

//Loads categories into the wallet from the given file
void Wallet::load(const std::string& filename) {
    std::ifstream databaseFile;
    databaseFile.open(filename);
    if (!databaseFile.is_open()) {
        std::cerr << filename << " could not be open or does not exist\n";
        std::exit(1);
    }
    nlohmann::json walletJSON = nlohmann::json::parse(databaseFile);
    nlohmann::json::iterator category;
    for (category = walletJSON.begin(); category != walletJSON.end();
        ++category) {
        newCategory(category.key()).load(category);
    }
    databaseFile.close();
}

//Saves the wallet data into the given file in JSON format
void Wallet::save(const std::string& filename) {
    std::ofstream databaseFile;
    databaseFile.open(filename);
    if (!databaseFile.is_open()) {
        std::cerr << filename << " could not be open or does not exist\n";
        std::exit(1);
    }
    databaseFile << json().dump();
    databaseFile.close();
}

//Creates a new category with the given identifier and adds it to the wallet
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

//Adds the category given to the wallet
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
        Category chosenCategory = categories.at(category.getIdent());
        for (auto& item : category.getItems()) {
            chosenCategory.addItem(item.second);
        }
        return false;
    }
}

//Deletes the category with the given identifier from the wallet
bool Wallet::deleteCategory(const std::string& categoryIdentifier) {
    if (categories.count(categoryIdentifier) == 1) {
        return categories.erase(categoryIdentifier);
    } else {
        throw std::out_of_range(
            "Unable to delete category. Category with the identifier " 
                + categoryIdentifier + " does not exist");
    }
}

//Gets how many categories are in the wallet
unsigned int Wallet::size() {
    return categories.size();
}

//Gets true if there are no categories in the wallet
bool Wallet::empty() {
    return categories.empty();
}

//Gets the wallet in JSON string format
std::string Wallet::str() {
    std::stringstream ss;
    ss << json();
    return ss.str();
}

//Gets the wallet in JSON format
nlohmann::json Wallet::json() {
    nlohmann::json json;
    for (auto& category : categories) {
        json[category.second.getIdent()] = category.second.json();
    }
    return json;
}

//Compares the given wallets based on their identifiers and categories
bool operator==(const Wallet& lhs, const Wallet& rhs) {
    for (const auto& lhsCategory : lhs.categories) {
        for (const auto& rhsCategory : rhs.categories) {
            if (!(lhsCategory == rhsCategory)) {
                return false;        
            }
        }
    }
    return true;
}
