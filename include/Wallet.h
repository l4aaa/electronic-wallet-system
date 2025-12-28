#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#include "Card.h"

class Wallet
{
public:
    void loadFromFile(const std::string &);
    void saveToFile(const std::string &) const;
    void addCard(const Card &);
    void removeCard(const std::string &);
    Card *findCard(const std::string &);
    void listCards() const;
    void viewCard(const std::string &);

private:
    std::vector<Card> cards;
};

#endif