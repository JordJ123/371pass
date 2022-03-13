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
	cxxopts::ParseResult args;
	try {
		args = options.parse(argc, argv);
	} catch (cxxopts::OptionException& exception) {
		std::cerr << exception.what() << "\n";
		exit(1);
	}

    // Print the help usage if requested
    if (args.count("help")) {
		std::cout << options.help() << '\n';
		return 0;
    }

    //Parses the command line arguments
	std::string database = parseDatabaseArgument(args);
	Action action;
	try {
		action = parseActionArgument(args);
	} catch (std::invalid_argument& exception) {
		exit(1);
	}
	std::string categoryIdent = parseCategoryArgument(args);
	std::string itemIdent = parseItemArgument(categoryIdent, args);

	//Updates data based on the command line arguments
	Wallet wObj{};
    wObj.load(database);
    switch (action) {
		case Action::CREATE:
			if (itemIdent.compare("") != 0) {
				createItem(wObj, categoryIdent, itemIdent);
			} else if (categoryIdent.compare("") != 0) {
				createCategory(wObj, categoryIdent);
			} else {
				std::cerr << "Please provide arguments on what to create in "
					"terms of category or item. Use -h or --help for more "
					"information\n";
				exit(1);
			}
			wObj.save(database);
			break;
		case Action::READ:
			if (categoryIdent.compare("") != 0) {
				readCategory(wObj, categoryIdent);
			} else {
				readWallet(wObj);
			}
			break;
		case Action::UPDATE:
			if (categoryIdent.compare("") != 0) {
				updateCategory(wObj, categoryIdent);
			} else {
				std::cerr << "Please provide arguments on what to update in "
					"terms of category or item. Use -h or --help for more "
					"information\n";
				exit(1);
			}
			wObj.save(database);
			break;
		case Action::DELETE:
			if (categoryIdent.compare("") != 0) {
				deleteCategory(wObj, categoryIdent);
			} else {
				std::cerr << "Please provide arguments on what to delete in "
					"terms of category or item. Use -h or --help for more "
					"information\n";
				exit(1);
			}
			wObj.save(database);
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
	cxxopts::value<std::string>()->default_value(""))(

	"category",
	"Apply action to a category (e.g., if you want to add a category, set "
	"the"
	" action argument to 'add' and the category argument to your chosen"
	" category identifier).",
	cxxopts::value<std::string>()->default_value(""))(

	"item",
	"Apply action to an item (e.g., if you want to add an item, set the "
	"action argument to 'add', the category argument to your chosen "
	"category "
	"identifier and the item argument to the item identifier).",
	cxxopts::value<std::string>()->default_value(""))(

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
	cxxopts::value<std::string>()->default_value(""))(

	"h,help", "Print usage.");

    return cxxopts;
}

//Gets the database filename from the command line if one is given 
//(database.json if not)
std::string App::parseDatabaseArgument(cxxopts::ParseResult &args) {
	return args["db"].as<std::string>();
}

//Gets the action argument from the command line if one is given
App::Action App::parseActionArgument(cxxopts::ParseResult &args) {
	Action a;
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
	} else if (input.compare("") == 0) {
		std::cerr << "Error: missing action argument(s).\n";
		throw std::invalid_argument("action");
	} else {
		std::cerr << "Error: invalid action argument(s).\n";
		throw std::invalid_argument("action");
	}
	return a;
}

//Gets the category argument from the command line if one is give
std::string App::parseCategoryArgument(cxxopts::ParseResult &args) {
	return args["category"].as<std::string>();
}

//Gets the item argument from the command line if one is give
std::string App::parseItemArgument(std::string& categoryIdent, 
	cxxopts::ParseResult &args) {
	std::string item = args["item"].as<std::string>();
	if (categoryIdent.compare("") == 0 && item.compare("") != 0) {
		std::cerr << "Error: Unable to parse item argument. Needs category "
			"argument that the item argument resides in.\n";
		exit(1);
	}
	return item;
}

//Creates the category in the given wallet with the given categoryIdentifier
void App::createCategory(Wallet& wObj, const std::string& categoryIdent) {
	wObj.newCategory(categoryIdent);
}

//Creates the item in the given category with the given itemIdentifier
void App::createItem(Wallet& wObj, const std::string& categoryIdent,
    const std::string& itemIdent) {
	wObj.newCategory(categoryIdent).newItem(itemIdent);
}

//Reads the given wallet
void App::readWallet(Wallet& wObj) {
	std::cout << getJSON(wObj) << "\n";
}

//Reads the category from the given wallet and categoryIdentifier
void App::readCategory(Wallet& wObj, const std::string& categoryIdent) {
	try {
		std::cout << getJSON(wObj, categoryIdent) << "\n";	
	} catch (std::out_of_range& exception) {
		std::cerr << exception.what() << "\n";
		exit(1);
	}
}

//Updates the category name from the given wallet and category identifiers
void App::updateCategory(Wallet& wObj, const std::string& categoryIdent) {
	try {
		int index = categoryIdent.find(":");
		if (index != -1 && index == (int) categoryIdent.find_last_of(":")) {
			std::string oldIdent = categoryIdent.substr(0, index);
			std::string newIdent = categoryIdent.substr(index + 1);
			wObj.getCategory(oldIdent).setIdent(newIdent);
		} else {
			std::cerr << "Category argument must be in the format "
				"oldIdentifier:newIdentifier\n";
			exit(1);
		}
	} catch (std::invalid_argument& exception) {
		std::cerr << exception.what() << "\n";
		exit(1);
	}
}

//Deletes the category based on the given wallet and category identifier
void App::deleteCategory(Wallet& wObj, const std::string& categoryIdent) {
	try {
		wObj.deleteCategory(categoryIdent);
	} catch (std::out_of_range& exception) {
		std::cerr << exception.what() << "\n";
		exit(1);
	}
}

//Gets the JSON string of a wallet object
std::string App::getJSON(Wallet &wObj) {
    return wObj.str();
}

//Gets the JSON string of a category object
std::string App::getJSON(Wallet &wObj, const std::string &c) {
    auto cObj = wObj.getCategory(c);
    return cObj.str();
}

//Gets the JSON string of a item object
std::string App::getJSON(Wallet &wObj, const std::string &c,
	const std::string &i) {
    auto cObj = wObj.getCategory(c);
    auto iObj = cObj.getItem(i);
    return iObj.str();
}

//Gets the JSON string of a item entry
std::string App::getJSON(Wallet &wObj, const std::string &c,
	const std::string &i, const std::string &e) {
    auto cObj = wObj.getCategory(c);
    auto iObj = cObj.getItem(i);
    return iObj.getEntry(e);
}
