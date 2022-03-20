// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 1910397
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
// A category contains one or more Items, each with
// their own identifier ('ident').
// -----------------------------------------------------

#ifndef CATEGORY_H
#define CATEGORY_H

#include <map>
#include <string>
#include "item.h"

class Category {

    //Attributes
    private:
        std::string ident;
        std::map<std::string, Item> items;

    //Constructors & Destructors
    public:
        Category(const std::string& identifier);
        ~Category() = default;

    //Methods
    public:
        const unsigned int size() const;
        const bool empty() const;
        const std::string& getIdent();
        void setIdent(const std::string& identifier);
        Item& newItem(const std::string& itemIdentifier);
        const bool addItem(Item& item);
        std::map<std::string, Item>& getItems();
        Item& getItem(const std::string& itemIdentifier);
        const bool deleteItem(const std::string& itemIdentifier);
        void load(nlohmann::json::iterator& category);
        friend bool operator==(const Category& lhs, const Category& rhs);
        const std::string str();
        const nlohmann::json json();
        
};

#endif // CATEGORY_H
