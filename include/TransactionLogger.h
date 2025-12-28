#ifndef TRANSACTION_LOGGER_H
#define TRANSACTION_LOGGER_H

#include <string>
#include <fstream>
#include <ctime>
#include <iostream>

class TransactionLogger
{
public:
    static void log(const std::string &cardNumber, const std::string &type, double amount);
    static void viewLogs();
};

#endif