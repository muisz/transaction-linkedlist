/*
by Muhamad Abdul Muis
github: https://github.com/muisz
*/

#include <iostream>
#include <ctime>

// #include "wallet.cpp"

using namespace std;

class Transaction {
private:
  string name;
  float amount;
  float balance;
  time_t date;
  char transaction_type;
  Transaction *next;

public:
  static char IN;
  static char OUT;

  Transaction() {
    name = "Initial Transaction";
    amount = 0;
    balance = 0;
    date = time(0);
    transaction_type = Transaction::IN;
    next = NULL;
  }

  ~Transaction() { destroy(); }

  void destroy() {
    if (next != NULL) {
      delete next;
    }
  }

  Transaction(string name, float amount, float balance, char transaction_type) {
    this->name = name;
    this->amount = amount;
    this->balance = balance;
    this->transaction_type = transaction_type;
    this->date = time(0);
    this->next = NULL;
  }

  string getTransactionType() {
    if (transaction_type == Transaction::IN) {
      return "In";
    }
    return "Out";
  }

  void show() {
    cout << "=============" << endl;
    cout << "Date\t\t\t\t: " << ctime(&date) << endl;
    cout << "Name\t\t\t\t: " << name << endl;
    cout << "Amount\t\t\t\t: " << amount << endl;
    cout << "Balance\t\t\t\t: " << balance << endl;
    cout << "Transaction Type\t\t: " << getTransactionType() << endl;
    cout << "=============" << endl;
  }

  void showAllTransaction() {
    show();
    if (next != NULL) {
      next->showAllTransaction();
    }
  }

  void earn(string name, float amount, float balance) {
    if (next == NULL) {
      next = new Transaction(name, amount, balance, Transaction::IN);
    } else {
      next->earn(name, amount, balance);
    }
  }

  void paid(string name, float amount, float balance) {
    if (next == NULL) {
      next = new Transaction(name, amount, balance, Transaction::OUT);
    } else {
      next->paid(name, amount, balance);
    }
  }
};

char Transaction::IN = 'I';
char Transaction::OUT = 'O';

class Wallet {
private:
  string name;
  float balance;
  Transaction *transaction;

public:
  Wallet() = default;

  Wallet(string name, float amount) {
    this->name = name;
    this->balance = amount;
    this->transaction =
        new Transaction("Initial Wallet", amount, amount, Transaction::IN);
  }

  ~Wallet() { delete transaction; }

  void addMoney(string name, float amount) {
    balance += amount;
    transaction->earn(name, amount, balance);
  }

  void paid(string name, float amount) {
    if (amount > balance) {
      throw invalid_argument("no balance left");
    }
    balance -= amount;
    transaction->paid(name, amount, balance);
  }

  void showTransaction() { transaction->showAllTransaction(); }
};

int main() {
  Wallet wallet("My Wallet", 100000);
  wallet.addMoney("Salary", 200000);
  wallet.addMoney("Bonus", 500000);
  wallet.paid("Flight Ticket", 700000);
  wallet.showTransaction();
  return 0;
}