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
        Category();
        Category(const std::string& identifier);
        ~Category() = default;

    //Setters & Getters
    public:
        void setIdent(const std::string& identifier);
        std::string& getIdent();
        std::map<std::string, Item>& getItems();
        Item& getItem(const std::string& itemIdentifier);

    //Other Methods
    public:
        void load(nlohmann::json::iterator& category);
        Item& newItem(const std::string& itemIdentifier);
        bool addItem(Item& item);
        bool deleteItem(const std::string& itemIdentifier);
        unsigned int size();
        bool empty();
        std::string str();
        nlohmann::json json();
        friend bool operator==(const Category& lhs, const Category& rhs);

};

#endif // CATEGORY_H
