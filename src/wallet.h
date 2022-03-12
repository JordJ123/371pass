// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 1910397
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
// The root object that holds all data for 371pass. This
// class contains Categories, which in turn hold Items,
// which hold a mapping of entries.
// -----------------------------------------------------

#ifndef WALLET_H
#define WALLET_H

#include <map>
#include <string>
#include "lib_json.hpp"
#include "category.h"

class Wallet {

    //Attributes
    private:
        std::map<std::string, Category> categories;

    //Constructors & Destructors
    public:
        Wallet();
        ~Wallet() = default;

    //Getter Methods
    public:
        std::map<std::string, Category>& getCategories();
        Category& getCategory(const std::string& categoryIdentifier);

    //Other Methods
    public:
        void load(const std::string& filename);
        void save(const std::string& filename);
        Category& newCategory(const std::string& categoryIdentifier);
        bool addCategory(Category& category);
        bool deleteCategory(const std::string& categoryIdentifier);
        unsigned int size();
        bool empty();
        std::string str();
        nlohmann::json json();
        friend bool operator==(const Wallet& lhs, const Wallet& rhs);
  
};

#endif // WALLET_H
