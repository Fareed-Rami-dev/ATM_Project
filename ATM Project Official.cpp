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
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <fstream>
#include <string>
#include "strOperations.h"
#include "ATM_System.h"
using namespace std;

void ATM_Login()
{
	std::string accountNum;
	std::string pin;
	clientRecord* ptr = nullptr;
	bool loginSuccess = false;
	do
	{
		s = client_Op::gatherRecordsFromFormattedClientRecordsFile(currClientFileName);
		system("cls");
		ATM_Op::printLoginScreenHeader();
		putchar('\n');
		printf_s("Enter account number\n");
		getline(std::cin, accountNum);
		while (!(client_Op::doesClientExistsByAccountNumber(accountNum, s, ptr)))
		{
			fprintf(stderr, "Invalid Account Number! Please try again\n");
			getline(std::cin, accountNum);
		}
		printf_s("Enter PIN?");
		getline(cin, pin);
		if (ptr == nullptr)
		{
			throw std::runtime_error("System Failure\n");
		}
		if (ptr->PIN_CODE != pin)
		{
			cerr << "Invalid PIN!\n";
			loginSuccess = false;
			this_thread::sleep_for(chrono::seconds(3));
		}
		else
		{
			loginSuccess = true;
			break;
		}
	} while (!loginSuccess);
	ATM_Op::print_ATM_MainMenuScreen(ptr);
}

int main()
{
	do {
		try
		{
			ATM_Login();
		}
		catch (const LogoutException e)
		{
			std::cout << "Logout successful." << std::endl << std::flush;
			this_thread::sleep_for(chrono::seconds(3));
			continue;
		}
	} while (1);
}

