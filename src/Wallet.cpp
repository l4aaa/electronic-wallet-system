#include "Wallet.h"
#include <vector>
#include <sstream>

void Wallet::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::ofstream out(filename);
        out << "cardName,cardNumber,name,expirationDate,moneyAmount,viewCount\n";
        out.close();
        std::cout << "Info: Created new database file: " << filename << "\n";
        return;
    }
    
    std::string line;
    if (!std::getline(file, line)) {
        return;
    }

    int lineNumber = 1;
    while (std::getline(file, line)) {
        lineNumber++;
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> row;

        while (std::getline(ss, segment, ',')) {
            row.push_back(segment);
        }

        if (row.size() != 6) {
            std::cerr << "Warning: Skipping malformed line " << lineNumber 
                      << " in CSV (found " << row.size() << " columns, expected 6).\n";
            continue;
        }

        try {
            std::string cName = row[0];
            std::string cNum = row[1];
            std::string owner = row[2];
            std::string exp = row[3];
            
            double amount = std::stod(row[4]);
            int views = std::stoi(row[5]);

            if (amount < 0) amount = 0; 
            if (views < 0) views = 0;

            Card newCard(cName, cNum, owner, exp, amount, views);
            cards.push_back(newCard);

        } catch (const std::exception& e) {
            std::cerr << "Warning: Skipping line " << lineNumber 
                      << " due to invalid numeric data (Money/Views must be numbers).\n";
            continue;
        }
    }
    file.close();
}