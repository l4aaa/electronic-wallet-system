#include "Card.h"
#include <iostream>

// ANSI color codes
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_RESET "\033[0m"

Card::Card(std::string cardName, std::string cardNumber, std::string name, std::string expirationDate)
{
    this->cardName = cardName;
    this->cardNumber = cardNumber;
    this->name = name;
    this->expirationDate = expirationDate;
    this->moneyAmount = 0;
    this->viewCount = 0;
}

Card::Card(std::string cardName, std::string cardNumber, std::string name, std::string expirationDate, double amount = 0, int viewCount = 0)
{
    this->cardName = cardName;
    this->cardNumber = cardNumber;
    this->name = name;
    this->expirationDate = expirationDate;
    this->moneyAmount = amount;
    this->viewCount = viewCount;
}

void Card::addMoney(double amount)
{
    moneyAmount += amount;
}

bool Card::removeMoney(double amount)
{
    if (moneyAmount >= amount)
    {
        moneyAmount -= amount;
        return true;
    }
    return false;
}

bool Card::transferTo(Card &target, double amount)
{
    if (moneyAmount >= amount)
    {
        moneyAmount -= amount;
        target.addMoney(amount);
        return true;
    }
    return false;
}

double Card::getBalance() const
{
    return moneyAmount;
}

std::string Card::getCard() const
{
    return cardName;
}

std::string Card::getNumber() const
{
    return cardNumber;
}

std::string Card::getName() const
{
    return name;
}

std::string Card::getDate() const
{
    return expirationDate;
}

int Card::getView() const
{
    return viewCount;
}

void Card::incrementViewCount()
{
    viewCount++;
}

void Card::displayCard() const
{
    std::cout << "Card Name: " << cardName
              << ", Card Number: " << COLOR_GREEN << cardNumber << COLOR_RESET << "\n";
}

void Card::displayCardDetails() const
{
    std::cout << "Card Name: " << cardName
              << ", Card Number: " << COLOR_GREEN << cardNumber << COLOR_RESET
              << ", Name: " << name
              << ", Expiration Date: " << expirationDate
              << ", Balance: " << COLOR_YELLOW << moneyAmount << COLOR_RESET
              << ", View Count: " << viewCount << "\n";
}