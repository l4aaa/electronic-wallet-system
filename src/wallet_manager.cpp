#include "Wallet.h"
#include "TransactionLogger.h"
#include <iostream>
#include <cstring>
#include <stdexcept>


const std::string DB_PATH = "../cards.csv";

void print_help() {
    std::cout << "Usage: wallet_manager <command> [args...]\n"
              << "Commands:\n"
              << "  add_card <card_name> <number> <owner_name> <exp_date>      Add a new card\n"
              << "  view_card <number>                                         View a card (increments view count)\n"
              << "  list_cards                                                 List all cards\n"
              << "  load_money <number> <amount>                               Load money to a card\n"
              << "  save                                                       Save wallet to file\n"
              << "  --help                                                     Show this help message\n";
}

double parseAmount(const std::string& input) {
    try {
        size_t processed;
        double amount = std::stod(input, &processed);
        
        if (processed != input.length()) {
            throw std::invalid_argument("Trailing characters");
        }
        
        if (amount <= 0) {
            std::cerr << "Error: Amount must be a positive value.\n";
            return -1.0;
        }
        return amount;
    } catch (const std::exception& e) {
        std::cerr << "Error: Invalid numeric format for amount '" << input << "'.\n";
        return -1.0;
    }
}

int main(int argc, char* argv[]) {
    Wallet wallet;
    wallet.loadFromFile(DB_PATH);

    if (argc < 2) {
        std::cerr << "Unknown command. Use --help to see available commands.\n";
        return 1;
    }

    std::string command = argv[1];

    if (command == "add_card") {
        if (argc < 6) {
            std::cerr << "Usage: add_card <card_name> <number> <owner_name> <exp_date>\n";
            return 1;
        }
        std::string cardName = argv[2];
        std::string number = argv[3];
        std::string owner = argv[4];
        std::string exp = argv[5];

        if(number.empty() || owner.empty()) {
             std::cerr << "Error: Card details cannot be empty.\n";
             return 1;
        }

        Card newCard(cardName, number, owner, exp);
        wallet.addCard(newCard);
        wallet.saveToFile(DB_PATH);
        std::cout << "Success: Card added.\n";

    } else if (command == "view_card") {
        if (argc != 3) {
            std::cerr << "Usage: view_card <number>\n";
            return 1;
        }
        wallet.viewCard(argv[2]);
        wallet.saveToFile(DB_PATH);

    } else if (command == "list_cards") {
        wallet.listCards();

    } else if (command == "load_money") {
        if (argc != 4) {
            std::cerr << "Usage: load_money <number> <amount>\n";
            return 1;
        }
        std::string number = argv[2];
        
        double amount = parseAmount(argv[3]);
        if (amount < 0) return 1;

        if (Card* c = wallet.findCard(number)) {
            c->addMoney(amount);
            TransactionLogger::log(number, "LOAD", amount);
            wallet.saveToFile(DB_PATH);
            std::cout << "Success: Loaded " << amount << " onto card " << number << ".\n";
        } else {
            std::cerr << "Error: Card not found.\n";
            return 1;
        }

    } else if (command == "save") {
        wallet.saveToFile(DB_PATH);
        std::cout << "Success: Database saved.\n";

    } else if (command == "--help") {
        print_help();

    } else {
        std::cerr << "Unknown command. Use --help to see available commands.\n";
        return 1;
    }

    return 0;
}