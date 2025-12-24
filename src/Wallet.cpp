#include "Wallet.h"
#include <vector>
#include <sstream>
#include <iomanip>

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
    if (!std::getline(file, line)) return;

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
                      << " due to invalid numeric data.\n";
            continue;
        }
    }
    file.close();
}

void Wallet::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file for saving: " << filename << "\n";
        return;
    }

    file << "cardName,cardNumber,name,expirationDate,moneyAmount,viewCount\n";

    for (const auto& card : cards) {
        file << card.getCard() << ","
             << card.getNumber() << ","
             << card.getName() << ","
             << card.getDate() << ","
             << std::fixed << std::setprecision(2) << card.getBalance() << ","
             << card.getView() << "\n";
    }
    file.close();
}

void Wallet::addCard(const Card& card) {
    cards.push_back(card);
}

void Wallet::removeCard(const std::string& cardNumber) {
    auto it = std::remove_if(cards.begin(), cards.end(),
        [&cardNumber](const Card& c) { return c.getNumber() == cardNumber; });
    
    if (it != cards.end()) {
        cards.erase(it, cards.end());
        std::cout << "Card " << cardNumber << " removed.\n";
    } else {
        std::cerr << "Card not found.\n";
    }
}

Card* Wallet::findCard(const std::string& cardNumber) {
    for (auto& card : cards) {
        if (card.getNumber() == cardNumber) {
            return &card;
        }
    }
    return nullptr;
}

void Wallet::listCards() const {
    if (cards.empty()) {
        std::cout << "No cards in wallet.\n";
        return;
    }
    std::cout << "\n--- Wallet Contents ---\n";
    for (const auto& card : cards) {
        card.displayCardDetails();
    }
    std::cout << "-----------------------\n";
}

void Wallet::viewCard(const std::string& cardNumber) {
    Card* card = findCard(cardNumber);
    if (card) {
        card->incrementViewCount();
        card->displayCardDetails();
    } else {
        std::cerr << "Error: Card " << cardNumber << " not found.\n";
    }
}