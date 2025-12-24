#include "TransactionLogger.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <cstring>

const std::string LOG_PATH = "transactions.txt";

void TransactionLogger::log(const std::string& cardNumber, const std::string& type, double amount) {
    std::ofstream file(LOG_PATH, std::ios::app);
    
    if (!file) {
        std::cerr << "Error: Could not write to transaction log.\n";
        return;
    }

    time_t now;
    time(&now);
    char* dt = ctime(&now);
    if (dt[strlen(dt)-1] == '\n') dt[strlen(dt)-1] = '\0';

    file << dt << " : " 
         << "Card: " << cardNumber 
         << ", Type: " << type 
         << ", Amount: " << amount << "\n";
}

void TransactionLogger::viewLogs() {
    std::ifstream in(LOG_PATH);
    std::string line;
    
    std::cout << "\n--- Transaction History ---\n";
    if (in.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "(No transactions recorded)\n";
    }
    
    while (std::getline(in, line)) {
        std::cout << line << "\n";
    }
    std::cout << "---------------------------\n";
}