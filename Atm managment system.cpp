#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector> 
#include <map>
#include <fstream>
using namespace std;

class Account {
public:
    int accountNumber;
    int pin;
    long balance;
    string accountHolderName;
    string registeredMobile;
    
    Account(int accNum, int p, long bal, string name, string mobile) {
        accountNumber = accNum;
        pin = p;
        balance = bal;
        accountHolderName = name;
        registeredMobile = mobile;
    }
};

class ATM {
private:
    vector<Account> accounts;
    map<string, bool> usedMobileNumbers;
    Account* currentAccount;
    
    int wrongAttempts;
    bool cardBlocked;
    
    long dailyWithdrawn;
    const long DAILY_LIMIT = 100000;
    
    vector<string> transactions;
    
    string bankName;

public:
    ATM() {
        bankName = "NEPAL BANK LIMITED (NBL)";
        loadAccounts();
        
        if(accounts.empty()) {
            accounts.push_back(Account(12345, 1111, 500000, "PUSOE", "9841234567"));
            accounts.push_back(Account(12346, 2222, 250000, "RAM", "9852345678"));
            accounts.push_back(Account(12347, 3333, 750000, "SITA", "9863456789"));
            accounts.push_back(Account(12348, 4444, 120000, "HARI", "9814567890"));
            
            usedMobileNumbers["9841234567"] = true;
            usedMobileNumbers["9852345678"] = true;
            usedMobileNumbers["9863456789"] = true;
            usedMobileNumbers["9814567890"] = true;
            saveAccounts();
        }
        
        currentAccount = nullptr;
        wrongAttempts = 0;
        cardBlocked = false;
        dailyWithdrawn = 0;
        srand(time(0));
    }

    void saveAccounts() {
        ofstream file("accounts.txt");
        if(file.is_open()) {
            for(const auto& acc : accounts) {
                file << acc.accountNumber << " "
                     << acc.pin << " "
                     << acc.balance << " "
                     << acc.accountHolderName << " "
                     << acc.registeredMobile << endl;
            }
            file.close();
        }
    }

    void loadAccounts() {
        ifstream file("accounts.txt");
        if(file.is_open()) {
            int accNum, pin;
            long balance;
            string name, mobile;
            
            while(file >> accNum >> pin >> balance >> name >> mobile) {
                accounts.push_back(Account(accNum, pin, balance, name, mobile));
                usedMobileNumbers[mobile] = true;
            }
            file.close();
        }
    }

    bool isAccountExists(int accNum) {
        for(const auto& acc : accounts) {
            if(acc.accountNumber == accNum) return true;
        }
        return false;
    }

    bool isMobileUsed(string mobile) {
        return usedMobileNumbers.find(mobile) != usedMobileNumbers.end();
    }

    void storeTransaction(string t) {
        transactions.push_back(t);
    }

    void showMiniStatement() {
        cout << "\n------ MINI STATEMENT ------\n";
        if(transactions.empty()) {
            cout << "No transactions yet.\n";
        } else {
            for(const auto& t : transactions) {
                cout << t << endl;
            }
        }
    }

    void header() {
        cout << "\n--------------------------------------------\n";
        cout << "           ATM MANAGEMENT SYSTEM\n";
        cout << "        " << bankName << "\n";
        cout << "--------------------------------------------\n";
    }

    bool isCardBlocked() {
        return cardBlocked;
    }

    int getPIN() {
        int enteredPin = 0;
        cout << "Enter PIN :  ";
        cin >> enteredPin;
        return enteredPin;
    }

    bool verifyCardAndPin() {
        int enteredPin;
        
        cout << "\nINSERT YOUR CARD" << endl;
        cout << "Card inserted successfully!" << endl;
        enteredPin = getPIN();
        
        for(auto& account : accounts) {
            if(account.pin == enteredPin) {
                currentAccount = &account;
                wrongAttempts = 0;
                dailyWithdrawn = 0;
                transactions.clear();
                cout << "\nPIN VERIFIED SUCCESSFULLY" << endl;
                cout << "Welcome " << account.accountHolderName << endl;
                cout << "Account: " << account.accountNumber << endl;
                return true;
            }
        }
        
        wrongAttempts++;
        cout << "\nWRONG PIN ATTEMPT (" << wrongAttempts << "/3)\n";
        if (wrongAttempts >= 3) {
            cardBlocked = true;
            cout << "\nCARD BLOCKED AFTER 3 WRONG ATTEMPTS\n";
        }
        return false;
    }

    void showDateTime() {
        time_t now = time(0);
        cout << "Date & Time : " << ctime(&now);
    }

    void receiptHeader() {
        cout << "\n--------------------------------------------\n";
        cout << "           NBL OFFICIAL RECEIPT\n";
        cout << "--------------------------------------------\n";
        cout << "Account Holder : " << currentAccount->accountHolderName << endl;
        cout << "Account Number : " << currentAccount->accountNumber << endl;
        showDateTime();
        cout << "--------------------------------------------\n";
    }

    void receiptFooter() {
        cout << "--------------------------------------------\n";
    }

    void endMessage(bool cashTaken) {
        cout << "--------------------------------------------\n";
        cout << "PLEASE TAKE YOUR CARD\n";
        if (cashTaken)
            cout << "PLEASE COLLECT YOUR CASH\n";
        cout << "THANK YOU FOR USING NBL ATM\n";
        cout << "NAMASTE\n";
        cout << "--------------------------------------------\n";
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
        saveAccounts();
    }

    void balanceEnquiry() {
        receiptHeader();
        cout << "Transaction : BALANCE ENQUIRY\n";
        cout << "Available Funds : NPR " << currentAccount->balance << endl;
        receiptFooter();
        storeTransaction("Balance Enquiry");
        endMessage(false);
    }

    void fastCash() {
        int choice;
        long amounts[4] = {1000,2000,5000,10000};

        cout << "\n------ FAST CASH ------\n";
        cout << "1. NPR 1000\n2. NPR 2000\n3. NPR 5000\n4. NPR 10000\n";
        cin >> choice;

        if(choice < 1 || choice > 4){
            cout << "INVALID OPTION\n";
            endMessage(false);
            return;
        }

        long amount = amounts[choice-1];

        if(amount > currentAccount->balance){
            cout<<"INSUFFICIENT BALANCE\n";
            endMessage(false);
            return;
        }

        if(dailyWithdrawn + amount > DAILY_LIMIT){
            cout<<"DAILY LIMIT EXCEEDED\n";
            endMessage(false);
            return;
        }

        currentAccount->balance -= amount;
        dailyWithdrawn += amount;

        receiptHeader();
        cout<<"Transaction : FAST CASH\n";
        cout<<"Withdrawn : NPR "<<amount<<endl;
        cout<<"Remaining Balance : NPR "<<currentAccount->balance<<endl;
        receiptFooter();

        storeTransaction("Fast Cash NPR "+to_string(amount));
        endMessage(true);
    }

    void cashWithdrawal() {
        long amount;
        cout<<"Enter Amount : ";
        cin>>amount;

        if(amount > currentAccount->balance){
            cout<<"INSUFFICIENT BALANCE\n";
            endMessage(false);
            return;
        }

        if(dailyWithdrawn + amount > DAILY_LIMIT){
            cout<<"DAILY LIMIT EXCEEDED\n";
            endMessage(false);
            return;
        }

        currentAccount->balance -= amount;
        dailyWithdrawn += amount;

        receiptHeader();
        cout<<"Transaction : CASH WITHDRAWAL\n";
        cout<<"Withdrawn : NPR "<<amount<<endl;
        cout<<"Remaining Balance : NPR "<<currentAccount->balance<<endl;
        receiptFooter();

        storeTransaction("Cash Withdrawal NPR "+to_string(amount));
        endMessage(true);
    }

    void cardMenu(){
        int option;
        do{
            cout<<"\n--------------------------------------------\n";
            cout << "CARD MENU\n";
            cout<<"1 Fast Cash\n2 Balance Enquiry\n3 Cash Withdrawal\n4 Mini Statement\n5 Exit\n";
            cout<<"Enter choice: ";
            cin>>option;

            switch(option){
                case 1: fastCash(); break;
                case 2: balanceEnquiry(); break;
                case 3: cashWithdrawal(); break;
                case 4: showMiniStatement(); endMessage(false); break;
                case 5: return;
            }
        }while(option!=5);
    }

    void registerNewAccount() {
        int accNum, pin;
        string name, mobile;
        long balance;
        
        cout << "\nNEW ACCOUNT REGISTRATION\n";
        
        while(true) {
            cout << "Enter 5-digit Account Number: ";
            cin >> accNum;
            if(accNum < 10000 || accNum > 99999)
                cout << "Must be 5-digit number!\n";
            else if(isAccountExists(accNum))
                cout << "Account number exists!\n";
            else break;
        }
        
        cout << "Enter 4-digit PIN: ";
        cin >> pin;
        
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        
        while(true) {
            cout << "Enter Mobile: ";
            cin >> mobile;
            if(mobile.length()!=10 || mobile.substr(0,2)!="98")
                cout<<"Invalid mobile!\n";
            else if(isMobileUsed(mobile))
                cout<<"Already used!\n";
            else break;
        }
        
        do {
            cout << "Enter Balance (Min 1000): ";
            cin >> balance;
        } while(balance < 1000);
        
        accounts.push_back(Account(accNum, pin, balance, name, mobile));
        usedMobileNumbers[mobile] = true;
        saveAccounts();
        
        cout << "\nAccount Created Successfully!\n";
        endMessage(false);
    }
};

int main(){
    ATM user;
    int choice;

    while(true) {
        user.header();

        cout << "\nMAIN MENU\n";
        cout << "1. Card Transaction\n";
        cout << "2. Register New Account\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                bool loggedIn = false;
                while(!loggedIn && !user.isCardBlocked()) {
                    loggedIn = user.verifyCardAndPin();
                }
                if(loggedIn) {
                    user.cardMenu();
                }
                break;
            }
            case 2:
                user.registerNewAccount();
                break;
            case 3:
                cout << "Thank you!\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}