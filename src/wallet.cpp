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

Wallet::Wallet() {}

Category& Wallet::getCategory(const std::string& categoryIdentifier) {
    if (categories.count(categoryIdentifier) == 1) {
        return categories.at(categoryIdentifier);
    } else {
        throw std::out_of_range(
            "Unable to get category. Item with the identifier " 
                + categoryIdentifier + " does not exist");
    }
}

void Wallet::load(const std::string& filename) {
    std::ifstream databaseFile;
    databaseFile.open(filename + ".json");
    if (!databaseFile.is_open()) {
        std::cerr << filename << ".json could not be open or does not exist\n";
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

void Wallet::save(const std::string& filename) {
    std::ofstream databaseFile;
    databaseFile.open(filename + ".json");
    if (!databaseFile.is_open()) {
        std::cerr << filename << ".json could not be open or does not exist\n";
        std::exit(1);
    }
    databaseFile << json().dump(2);
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
        Category chosenCategory = categories.at(category.getIdent());
        for (auto& item : category.getItems()) {
            chosenCategory.addItem(item.second);
        }
        return false;
    }
}

bool Wallet::deleteCategory(const std::string& categoryIdentifier) {
    if (categories.count(categoryIdentifier) == 1) {
        return categories.erase(categoryIdentifier);
    } else {
        throw std::out_of_range(
            "Unable to delete category. Category with the identifier " 
                + categoryIdentifier + " does not exist");
    }
}

unsigned int Wallet::size() {
    return categories.size();
}

bool Wallet::empty() {
    return categories.empty();
}

std::string Wallet::str() {
    std::stringstream ss;
    ss << json();
    return ss.str();
}

nlohmann::json Wallet::json() {
    nlohmann::json json;
    for (auto& category : categories) {
        json[category.second.getIdent()] = category.second.json();
    }
    return json;
}

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