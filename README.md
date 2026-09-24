# ATM Management System

A console-based ATM Management System developed in C++. This project simulates common ATM operations such as PIN authentication, balance inquiry, cash withdrawal, fast cash, account registration, and transaction history.

## Features

- Card and PIN authentication
- Maximum of three incorrect PIN attempts
- Card blocking after three incorrect attempts
- Balance inquiry
- Fast cash withdrawal
- Custom cash withdrawal
- Daily withdrawal limit
- Mini statement and transaction history
- New account registration
- Mobile number validation
- Account data saved in `accounts.txt`
- Receipt-style transaction output
- Date and time displayed on receipts

## Technologies Used

- C++
- Object-oriented programming
- File handling
- STL containers:
  - `vector`
  - `map`
- Standard C++ libraries

## Requirements

- A C++ compiler such as:
  - GCC
  - MinGW
  - Visual Studio
  - Code::Blocks
- C++11 or later

## How to Run

### Using g++

Open a terminal in the project directory and run:

```bash
g++ "Atm managment system.cpp" -o atm
```

Then start the application:

```bash
./atm
```

On Windows, run:

```bash
atm.exe
```

## How to Use

When the program starts, choose an option from the main menu:

1. Card Transaction
2. Register New Account
3. Exit

After successful PIN authentication, you can:

1. Withdraw fast cash
2. Check your balance
3. Withdraw a custom amount
4. View your mini statement
5. Exit the card menu

## Default Test Accounts

| Account Holder | Account Number | PIN |
|---|---:|---:|
| PUSOE | 12345 | 1111 |
| RAM | 12346 | 2222 |
| SITA | 12347 | 3333 |
| HARI | 12348 | 4444 |

> These are demonstration accounts for testing only. Do not use real banking information.

## Data Storage

The application automatically creates and uses an `accounts.txt` file to save account information. This file should remain in the same directory as the executable.

The stored data includes:

- Account number
- PIN
- Balance
- Account holder name
- Registered mobile number

## Important Security Notice

This project is created for learning and demonstration purposes. It is not suitable for real banking use because account data and PINs are stored in a plain text file.

## Project Structure

```text
ATM-Management-system/
├── Atm managment system.cpp
│   └── Main C++ source file
│       ├── New account registration
│       ├── Card and PIN authentication
│       ├── Balance inquiry
│       ├── Fast cash withdrawal
│       ├── Custom cash withdrawal
│       ├── Mini statement and transaction history
│       └── File-based account data management
│
├── README.md
│   └── Project documentation
│       ├── Features and technologies
│       ├── Requirements
│       ├── Compilation and run instructions
│       ├── Usage instructions
│       ├── Demo accounts
│       └── Security notes
│
├── accounts.example.txt
│   └── Example account data file for testing and demonstration
│
└── accounts.txt
    └── Runtime-generated account data file
        ├── Account number
        ├── PIN
        ├── Balance
        ├── Account holder name
        └── Registered mobile number
```

> `accounts.txt` is created by the application at runtime and may not exist in a fresh clone of the repository. Keep it in the same directory as the executable.

## Future Improvements

- Hide PIN input while typing
- Encrypt account data
- Add fund transfer functionality
- Add deposit functionality
- Add administrator login
- Add persistent transaction history
- Improve input validation
- Add a graphical user interface
- Use a database instead of a text file

## Author

**Avishek007549**

## License

This project is available for educational and personal use.
