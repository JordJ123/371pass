// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 1910397
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
// This file contains declarations for the helper
// functions used for initialising and running 371pass.
// -----------------------------------------------------

#ifndef _371PASS_H
#define _371PASS_H

#include <string>

#include "lib_cxxopts.hpp"
#include "wallet.h"

namespace App {

    // TODO: Enter your student number here!
    const std::string STUDENT_NUMBER = "1910397";

    // Enums (short for enumerations) are similar to their Java implementation.
    // It is a user-defined type, used to assign names to internal constants
    // in code, instead of simply passing in integers/strings etc.
    //
    // For example, functions can take a value/constant from a specific enum
    // and use it in a switch statement, doing different things
    //
    // As such, it is a useful way for us to specify information in both a
    // machine and human-readable format.
    //
    // Unlike Java, enums in C++ only map to integer values. You can either let
    // the compiler generate the values automatically, in which it allocates a
    // unique integer (0-indexed). Or, you can set the value by giving the name
    // followed by = <value> (e.g. CREATE=0).
    //
    // This enum specifies the four different values we support in the action
    // program argument.
    enum Action { 
        CREATE, 
        READ, 
        UPDATE, 
        DELETE 
    };

    //Main Method
    int run(int argc, char *argv[]);
   
    //Parse Command Line Argument Methods
    cxxopts::Options cxxoptsSetup();
    std::string parseDatabaseArgument(cxxopts::ParseResult& args);
    App::Action parseActionArgument(cxxopts::ParseResult& args);
    std::string parseCategoryArgument(cxxopts::ParseResult& args);
    std::string parseItemArgument(const std::string& categoryIdent, 
        cxxopts::ParseResult& args);
    std::string parseEntryArgument(const std::string& categoryIdent, 
        const std::string& itemIdent, cxxopts::ParseResult& args);

    //Create Methods
    void createAction(const std::string& database, Wallet& wObj, 
        const std::string& categoryIdent, const std::string& itemIdent,
        const std::string& entry);
    void createCategory(Wallet& wObj, const std::string& categoryIdent);
    void createItem(Wallet& wObj, const std::string& categoryIdent,
        const std::string& itemIdent);
    void createEntry(Wallet& wObj, const std::string& categoryIdent,
        const std::string& itemIdent, const std::string& entry);

    //Read Methods
    void readAction(Wallet& wObj, const std::string& categoryIdent,
        const std::string& itemIdent, const std::string& entry);
    void readWallet(Wallet& wObj);
    void readCategory(Wallet& wObj, const std::string& categoryIdentifier);
    void readItem(Wallet& wObj, const std::string& categoryIdent,
        const std::string& itemIdent);
    void readEntry(Wallet& wObj, const std::string& categoryIdent,
        const std::string& itemIdent, const std::string& entry);

    //Update Methods
    void updateAction(const std::string& database, Wallet& wObj, 
        const std::string& categoryIdent, const std::string& itemIdent, 
        const std::string& entry);
    void updateCategory(Wallet& wObj, const std::string& categoryIdent);
    void updateItem(Wallet& wObj, const std::string& categoryIdent,
        const std::string& itemIdent);
    void updateEntry(Wallet& wObj, const std::string& categoryIdent,
        const std::string& itemIdent, const std::string& entry);

    //Delete Methods
    void deleteAction(const std::string& database, Wallet& wObj, 
        const std::string& categoryIdent, const std::string& itemIdent, 
        const std::string& entry);
    void deleteCategory(Wallet& wObj, const std::string& categoryIdent);
    void deleteItem(Wallet& wObj, const std::string& categoryIdent,
        const std::string& itemIdent);
    void deleteEntry(Wallet& wObj, const std::string& categoryIdent,
        const std::string& itemIdent, const std::string& entry);

    //Gets JSON Methods
    std::string getJSON(Wallet &w);
    std::string getJSON(Wallet &w, const std::string &c);
    std::string getJSON(Wallet &w, const std::string &c, const std::string &i);
    std::string getJSON(Wallet &wObj, const std::string &c, 
        const std::string &i, const std::string &e);

} // namespace App

#endif // _371PASS_H
