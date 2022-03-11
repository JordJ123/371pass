// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 1910397
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
// An Item class contains multiple 'entries' as
// key/value pairs (e.g., a key might be 'username'
// and a value would be the username, another might be
// 'url' and the value is the website address the
// username is for.
// -----------------------------------------------------

#ifndef ITEM_H
#define ITEM_H

#include <map>
#include <string>
#include "lib_json.hpp"

class Item {

    //Attributes
    private:
        std::string ident;
        std::map<std::string, std::string> entries;

    //Constructors & Destructors
    public:
        Item();
        Item(const std::string& identifier);
        ~Item() = default;

    //Setters & Getters
    public:
        void setIdent(const std::string& identifier);
        std::string& getIdent();
        std::map<std::string, std::string>& getEntries();
        std::string& getEntry(const std::string& key);

    //Other Methods
    public:
        void load(nlohmann::json::iterator& item);
        bool addEntry(std::string& key, std::string& value);
        bool addEntry(std::pair<const std::string, std::string>& entry);
        bool deleteEntry(std::string& key);
        unsigned int size();
        bool empty();
        std::string str();
        nlohmann::json json();
        friend bool operator==(const Item& lhs, const Item& rhs);
        

};

#endif // ITEM_H
