#pragma once
#ifndef ATM_SYSTEM_H
#define ATM_SYSTEM_H
#endif

#ifndef CLIENT_H
#define CLIENT_H
#endif

#ifndef STROPERATIONS_H
#define STROPERATIONS_H
#endif

#ifndef USER_INPUT_H
#define USER_INPUT_H
#endif

#include <vector>
#include <string>
#include "client.h"
extern std::vector<clientRecord> s;
extern const int32_t numberOfClientFieldsInfo;
extern const std::string currClientFileName;
extern const double LowerAmmountByFactor;
class LogoutException : public std::runtime_error {
public:
	LogoutException(const std::string& message = "User logged out.")
		: std::runtime_error(message) {}
};

enum ATM_operations
{
	QuickWithdraw = 1, NormalWithdraw = 2, Deposit = 3, CheckBalance = 4, Logout = 5
};
using namespace std;
namespace ATM_Op {

	void printATM_MainMenuScreenHeader();
	void performChosenATM_OperationsBasedOnChoice(ATM_operations op, clientRecord*& currClient);
	void print_ATM_MainMenuScreen(clientRecord*& currClient);
	void printQuickWithdrawScreen();
	void withdrawFromAccount(clientRecord*& currClient, const double amount);
	const bool validateAccountBalance(const clientRecord*& w, const double withdrawAmount);
	void printNormalWithdrawScreenHeader();
	void NormalWithdraw(clientRecord*& currClient);
	void printCheckBalanceScreenHeader();
	void checkBalance(clientRecord*& currClient);
	void deposit(clientRecord*& currClient);
	void QuickWithdraw(clientRecord*& currClient);
	void logoutFromUser(clientRecord*&);
	void printLoginScreenHeader();

}