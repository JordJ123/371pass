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
        Item(const std::string& identifier);
        ~Item() = default;

    //Methods
    public:
        const unsigned int size() const;
        const bool empty() const;
        void setIdent(const std::string& identifier);
        const std::string& getIdent();
        const bool addEntry(const std::string& key, const std::string& value);
        std::map<std::string, std::string>& getEntries();
        const std::string& getEntry(const std::string& key);
        const bool updateEntry(const std::string& oldKey, 
            const std::string& newKey, const std::string& newValue);
        const bool updateEntryKey(const std::string& oldKey, 
            const std::string& newKey);
        const bool updateEntryValue(const std::string& key, 
            const std::string& newValue);
        const bool deleteEntry(const std::string& key);
        void load(nlohmann::json::iterator& item);
        friend bool operator==(const Item& lhs, const Item& rhs);
        const std::string str() const;
        const nlohmann::json json() const;
        
};

#endif // ITEM_H
