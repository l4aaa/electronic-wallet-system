#include "Wallet.h"
#include "TransactionLogger.h"
#include <iostream>
#include <cstring>
#include <stdexcept>

const std::string DB_PATH = "../cards.csv";

void print_help() {
    std::cout << "Usage: remote_wallet <command> [args...]\n"
              << "Commands:\n"
              << "  spend <number> <amount>                                     Deduct money from a card\n"
              << "  transfer <from_number> <to_number> <amount>                 Transfer money between cards\n"
              << "  view_card <number>                                          View a card (increments view count)\n"
              << "  list                                                        List all cards\n"
              << "  --help                                                      Show this help message\n";
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

    if (command == "spend") {
        if (argc != 4) {
            std::cerr << "Usage: spend <number> <amount>\n";
            return 1;
        }
        std::string number = argv[2];
        
        double amount = parseAmount(argv[3]);
        if (amount < 0) return 1;

        if (Card* c = wallet.findCard(number)) {
            if (c->removeMoney(amount)) {
                TransactionLogger::log(number, "USE", amount);
                wallet.saveToFile(DB_PATH);
                std::cout << "Success: Spent " << amount << " from card " << number << ".\n";
            } else {
                std::cerr << "Error: Insufficient balance.\n";
                return 1;
            }
        } else {
            std::cerr << "Error: Card not found.\n";
            return 1;
        }

    } else if (command == "transfer") {
        if (argc != 5) {
            std::cerr << "Usage: transfer <from> <to> <amount>\n";
            return 1;
        }
        std::string from = argv[2];
        std::string to = argv[3];

        if (from == to) {
            std::cerr << "Error: Cannot transfer money to the same card.\n";
            return 1;
        }

        double amount = parseAmount(argv[4]);
        if (amount < 0) return 1;

        Card* c1 = wallet.findCard(from);
        Card* c2 = wallet.findCard(to);

        if (c1 && c2) {
            if (c1->getBalance() >= amount) {
                c1->transferTo(*c2, amount);
                TransactionLogger::log(from, "TRANSFER_OUT", amount);
                TransactionLogger::log(to, "TRANSFER_IN", amount);
                wallet.saveToFile(DB_PATH);
                std::cout << "Success: Transferred " << amount << " from " << from << " to " << to << ".\n";
            } else {
                std::cerr << "Error: Insufficient balance in source card.\n";
                return 1;
            }
        } else {
            if (!c1) std::cerr << "Error: Source card (" << from << ") not found.\n";
            if (!c2) std::cerr << "Error: Target card (" << to << ") not found.\n";
            return 1;
        }

    } else if (command == "view_card") {
        if (argc != 3) {
            std::cerr << "Usage: view_card <number>\n";
            return 1;
        }
        wallet.viewCard(argv[2]);
        wallet.saveToFile(DB_PATH);

    } else if (command == "list") {
        wallet.listCards();

    } else if (command == "--help") {
        print_help();

    } else {
        std::cerr << "Unknown command. Use --help to see available commands.\n";
        return 1;
    }

    return 0;
}