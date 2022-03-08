// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 1910397
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include "lib_cxxopts.hpp"
#include "371pass.h"
#include "wallet.h"

//Runs the application
int App::run(int argc, char *argv[]) {

    // Gets the command line arguments
    auto options = App::cxxoptsSetup();
    auto args = options.parse(argc, argv);

    // Print the help usage if requested
    if (args.count("help")) {
		std::cout << options.help() << '\n';
		return 0;
    }

    // Opens the chosen database and construct the wallet using it
    std::string db;
    Wallet wObj{};
    try {
		db = args["database"].as<std::string>();
    } catch (const cxxopts::option_not_present_exception&) {
		db = "database";
    }
    wObj.load(db);

	//Selects the chosen action and updates the data based on it
    const Action a = parseActionArgument(args);
    switch (a) {
	case Action::CREATE:
	    throw std::runtime_error("create not implemented");
	    break;
	case Action::READ:
	    throw std::runtime_error("read not implemented");
	    break;
	case Action::UPDATE:
	    throw std::runtime_error("update not implemented");
	    break;
	case Action::DELETE:
	    throw std::runtime_error("delete not implemented");
	    break;
	default:
	    throw std::runtime_error("Unknown action not implemented");
    }
    return 0;

}

// Create a cxxopts instance
cxxopts::Options App::cxxoptsSetup() {
    cxxopts::Options cxxopts("371pass", "Student ID: " + STUDENT_NUMBER + "\n");

    cxxopts.add_options()(
	"db", "Filename of the 371pass database",
	cxxopts::value<std::string>()->default_value("database.json"))(

	"action",
	"Action to take, can be: 'create', 'read', 'update', 'delete'.",
	cxxopts::value<std::string>())(

	"category",
	"Apply action to a category (e.g., if you want to add a category, set "
	"the"
	" action argument to 'add' and the category argument to your chosen"
	" category identifier).",
	cxxopts::value<std::string>())(

	"item",
	"Apply action to an item (e.g., if you want to add an item, set the "
	"action argument to 'add', the category argument to your chosen "
	"category "
	"identifier and the item argument to the item identifier).",
	cxxopts::value<std::string>())(

	"entry",
	"Apply action to an entry (e.g., if you want to add an entry, set the "
	"action argument to 'add', the category argument to your chosen "
	"category "
	"identifier, the item argument to your chosen item identifier, and the "
	"entry argument to the string 'key,value'). If there is no comma, an "
	"empty entry is inserted. If you are simply retrieving an entry, set "
	"the "
	"entry argument to the 'key'. If you are updating an entry key, use a "
	": "
	"e.g., oldkey:newkey,newvalue.",
	cxxopts::value<std::string>())(

	"h,help", "Print usage.");

    return cxxopts;
}

//Gets the action argument from the command line if one is given
App::Action App::parseActionArgument(cxxopts::ParseResult &args) {
	Action a;
	try {
		std::string input = args["action"].as<std::string>();
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);
		if (input.compare("create") == 0) {
			a = Action::CREATE;
		} else if (input.compare("read") == 0) {
			a = Action::READ;
		} else if (input.compare("update") == 0) {
			a = Action::UPDATE;
		} else if (input.compare("delete") == 0) {
			a = Action::DELETE;
		} else {
			std::fprintf(stderr, "Error: invalid action argument(s).\n");
			throw std::invalid_argument("action");
		}
	} catch (const cxxopts::option_has_no_value_exception& ex) {
		std::fprintf(stderr, "Error: missing action argument(s).\n");
		throw std::invalid_argument("action");
	}
	std::cout << a << std::endl;
    return a;
}

// TODO Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a Wallet object.
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
// Example:
//  Wallet wObj{};
//  std::cout << getJSON(wObj);
std::string App::getJSON(Wallet &wObj) {
    return "{}";
    // Only uncomment this once you have implemented the functions used!
    // return wObj.str();
}

// TODO Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific Category in a Wallet object.
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
// Example:
//  Wallet wObj{};
//  std::string c = "category argument value";
//  std::cout << getJSON(wObj, c);
std::string App::getJSON(Wallet &wObj, const std::string &c) {
    return "{}";
    // Only uncomment this once you have implemented the functions used!
    // auto cObj = wObj.getCategory(c);
    // return cObj.str();
}

// TODO Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific Item in a Wallet object.
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
// Example:
//  Wallet wObj{};
//  std::string c = "category argument value";
//  std::string i = "item argument value";
//  std::cout << getJSON(wObj, c, i);
std::string App::getJSON(Wallet &wObj, const std::string &c,
			 const std::string &i) {
    return "{}";
    // Only uncomment this once you have implemented the functions used!
    // auto cObj = wObj.getCategory(c);
    // const auto iObj = cObj.getItem(i);
    // return iObj.str();
}

// TODO Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific Entry in a Wallet object.
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
// Example:
//  Wallet wObj{};
//  std::string c = "category argument value";
//  std::string i = "item argument value";
//  std::string e = "entry argument value";
//  std::cout << getJSON(wObj, c, i, e);
std::string App::getJSON(Wallet &wObj, const std::string &c,
			 const std::string &i, const std::string &e) {
    return "{}";
    // Only uncomment this once you have implemented the functions used!
    // auto cObj = wObj.getCategory(c);
    // auto iObj = cObj.getItem(i);
    // return iObj.getEntry(e);
}