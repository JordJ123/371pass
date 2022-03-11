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

    const std::string STUDENT_NUMBER = "1910397";

    enum Action { 
        CREATE, 
        READ, 
        UPDATE, 
        DELETE 
    };

    int run(int argc, char *argv[]);

    cxxopts::Options cxxoptsSetup();

    std::string parseDatabaseArgument(cxxopts::ParseResult &args);
    App::Action parseActionArgument(cxxopts::ParseResult &args);
    std::string parseCategoryArgument(cxxopts::ParseResult &args);

    void readWallet(Wallet& wObj);
    void readCategory(Wallet& wObj, const std::string& categoryIdentifier);
    void updateCategory(Wallet& wObj, const std::string& categoryIdent);

    std::string getJSON(Wallet &w);
    std::string getJSON(Wallet &w, const std::string &c);
    std::string getJSON(Wallet &w, const std::string &c, const std::string &i);
    std::string getJSON(Wallet &wObj, const std::string &c, const std::string &i,
                        const std::string &e);

}

#endif // _371PASS_H