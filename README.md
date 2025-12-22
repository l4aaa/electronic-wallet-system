# 💳 Electronic Wallet System

![C++](https://img.shields.io/badge/Language-C%2B%2B17-blue.svg)
![Build](https://img.shields.io/badge/Build-Make%20%7C%20Batch-orange)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey)
![License](https://img.shields.io/badge/license-MIT-green.svg)

A robust, console-based electronic wallet system implemented in **C++17**. This project demonstrates bidirectional data flow between two distinct applications acting on a shared financial database.

It simulates a real-world financial ecosystem where a central management system issues cards and loads funds, while a remote terminal handles user transactions and transfers.

---

## ✨ Key Features

### 🏢 Wallet Manager (`wallet_manager`)
* **Card Issuance**: Create new cards with owner details, expiration dates, and unique card numbers.
* **Fund Management**: Load money directly onto existing cards.
* **Persistence**: Automatically saves all card data to `cards.csv` to ensure data retention between sessions.
* **System Overview**: List and inspect all issued cards within the system.

### 🏧 Remote Wallet (`remote_wallet`)
* **Transaction Processing**: Simulate spending money at a point-of-sale.
* **P2P Transfers**: Securely transfer funds between two distinct cards.
* **Live Validations**: Real-time checks for sufficient balances and card validity before processing.
* **Activity Logging**: Every action (Transfer, Load, Spend) is timestamped and recorded in `transactions.txt`.

### 🛠️ Core Architecture
* **Shared Database**: Both applications operate on a synchronized `cards.csv` file.
* **Transaction Logger**: A dedicated logging module tracks the history of all financial movements.
* **Formatted Output**: Utilizes ANSI color codes for clear, readable terminal output.

---

## 🛠️ Tech Stack

* **Language**: C++17
* **Build Tools**: Windows Batch Script (`build.bat`) & GNU Make (`makefile`)
* **Data Storage**: CSV (Comma-Separated Values) & Plain Text Logs
* **Standard Library**: `<fstream>`, `<vector>`, `<algorithm>`, `<iostream>`

---

## 🚀 Getting Started

### 1. Prerequisites
* **g++ Compiler**: Ensure you have a C++ compiler installed that supports C++17.
* **Terminal**: Command Prompt, PowerShell, or a Unix terminal.

### 2. Compilation

You can compile the system automatically using the provided scripts.

**For Windows Users:**
Run the batch file to build both executables in the `bin/` directory:
```bash
.\build.bat
```

**For Linux/Unix Users:**
Use the makefile to build the project:
```bash
make
```

### 3. Usage

The system consists of two separate executables located in the `bin/` folder.

#### 🔧 Using the Wallet Manager
Use this application to administer cards and funds.

```bash
# Add a new card
./bin/wallet_manager.exe add_card "Visa" "1001-2002-3003-4004" "John-Doe" "12/28"

# Load money onto a card
./bin/wallet_manager.exe load_money "1001-2002-3003-4004" 500.00

# List all cards
./bin/wallet_manager.exe list_cards
```

#### 💸 Using the Remote Wallet
Use this application to perform user transactions.

```bash
# Spend money from a card
./bin/remote_wallet.exe spend "1001-2002-3003-4004" 25.50

# Transfer money between cards
./bin/remote_wallet.exe transfer "1001-2002-3003-4004" "2002-3003-4004-5005" 100.00

# View card details
./bin/remote_wallet.exe view_card "1001-2002-3003-4004"
```

---

## 📂 Project Structure

```bash
l4aaa-electronic_wallet_system/
├── bin/                 # Compiled executables (generated)
├── include/             # Header files
│   ├── Card.h           # Card class definition
│   ├── TransactionLogger.h
│   └── Wallet.h         # Wallet management logic
├── src/                 # Source code
│   ├── Card.cpp         # Card implementation
│   ├── remote_wallet.cpp# Main entry for Remote App
│   ├── wallet_manager.cpp# Main entry for Manager App
│   ├── Wallet.cpp       # Wallet implementation
│   └── TransactionLogger.cpp
├── cards.csv            # Persistent card database
├── transactions.txt     # Transaction history log
├── build.bat            # Windows build script
├── makefile             # Linux build script
└── README.md            # Documentation
```

---

## 📝 License

Distributed under the MIT License. See `LICENSE` for more information.

> **Disclaimer**: This software is provided "as is", without warranty of any kind.
