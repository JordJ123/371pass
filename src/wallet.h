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

    //Methods
    public:
        const unsigned int size() const;
        const bool empty() const;
        Category& newCategory(const std::string& categoryIdentifier);
        const bool addCategory(Category& category);
        Category& getCategory(const std::string& categoryIdentifier);
        const bool deleteCategory(const std::string& categoryIdentifier);
        void load(const std::string& filename);
        void save(const std::string& filename);
        friend bool operator==(const Wallet& lhs, const Wallet& rhs);
        const std::string str();
        const nlohmann::json json();
  
};

#endif // WALLET_H
