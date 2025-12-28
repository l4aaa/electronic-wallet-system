#ifndef CARD_H
#define CARD_H

#include <string>

class Card
{
public:
    Card(std::string, std::string, std::string, std::string);
    Card(std::string, std::string, std::string, std::string, double, int);
    void addMoney(double);
    bool removeMoney(double);
    bool transferTo(Card &, double);
    double getBalance() const;
    std::string getCard() const;
    std::string getNumber() const;
    std::string getName() const;
    std::string getDate() const;
    int getView() const;
    void incrementViewCount();
    void displayCard() const;
    void displayCardDetails() const;

private:
    std::string cardName, cardNumber, name, expirationDate;
    double moneyAmount;
    int viewCount;
};

#endif