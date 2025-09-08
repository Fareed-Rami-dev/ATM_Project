#include "ATM_System.h"
#include "User_Input.h"
#include <thread>
#include <chrono>
 std::vector<clientRecord> s=vector<clientRecord>();
const int32_t numberOfClientFieldsInfo=6;
 const std::string currClientFileName="clientDataRecords.txt";
 const double LowerAmmountByFactor=1e-6;
namespace ATM_Op {
	void logoutFromUser(clientRecord*& currClient)
	{
		currClient = nullptr;
		throw LogoutException();
	}
	void printQuickWithdrawScreen()
	{
		printf_s("============================================================\n");
		printf_s("\t\t\t Quick Withdraw\n");
		printf_s("============================================================\n");
		printf_s("\t\t\t [1] 20\t\t\t[2] 50\n");
		printf_s("\t\t\t[3] 100\t\t\t [4] 200\n");
		printf_s("\t\t\t[5] 400\t\t\t[6] 600\n");
		printf_s("\t\t\t[7] 800\t\t\t[6] 1000\n");
		printf_s("\t\t\t[9] Exit\n");
		printf_s("============================================================\n");
	}
	void withdrawFromAccount(clientRecord*& currClient, const double amount)
	{

		if (currClient == nullptr)
		{
			throw std::invalid_argument("Trying to withdraw before logging in\n");
		}
		if (currClient->accountBalance < amount)
		{
			cerr << "The amount exceeds your balance...";
			cerr << " you will be returned to ATM Main Menu Screen Soon\n";
			this_thread::sleep_for(chrono::seconds(4));
			return;
		}
		else
		{
			char choice = 'n';
			cout << "Are you sure you want to perform this transaction y/n?\n";
			cin >> choice;
			if (choice == 'y')
			{
				currClient->accountBalance -= amount;
				client_Op::saveNonMarkedClientsForDeletionDataToFile(currClientFileName, s);
				cout << "Done Successfully.. New Balance is: " << currClient->accountBalance << endl;
				cout << "You will be redirected to ATM Main Menu Screen Soon\n";
				this_thread::sleep_for(chrono::seconds(4));
			}
			else
			{
				clog << "Trying to withdraw from account number: " << currClient->accountNumber << " has been rejected by user\n";
				cout << "You will be redirected to ATM Main Menu Screen Soon\n";
				this_thread::sleep_for(chrono::seconds(4));
			}
		}
	}
	const bool validateAccountBalance( clientRecord*& w, const double withdrawAmount)
	{
		return ((withdrawAmount) <= (w->accountBalance));
	}
	void printNormalWithdrawScreenHeader()
	{
		printf_s("============================================================\n");
		printf_s("\t\t\t Normal Withdraw\n");
		printf_s("============================================================\n");
	}
	void NormalWithdraw(clientRecord*& currClient)
	{
		system("cls");
		if (currClient == nullptr)
		{
			throw std::invalid_argument("Trying to withdraw before logging in\n");
		}
		printNormalWithdrawScreenHeader();
		double amount=0;
		do
		{
			cout << "Enter an amount multiple of 5's.. Max amount is: " << UINT16_MAX << endl;
			cin >> amount;
		} while (amount <= 0 || amount>UINT16_MAX || !(fmod(amount,5)==0));
		if (!validateAccountBalance(currClient, amount))
		{
			cerr << "The amount exceeds your balance.. Make another choice\n";
			cout << "You will be redirected to ATM Main Menu Sceen Soon\n";
			this_thread::sleep_for(chrono::seconds(4));
			return;
		}
		withdrawFromAccount(currClient, amount);
	}
	void printCheckBalanceScreenHeader()
	{
		printf_s("============================================================\n");
		printf_s("\t\t\t Check Balance Screen\n");
		printf_s("============================================================\n");
	}
	void checkBalance(clientRecord*& currClient)
	{
		if (currClient == nullptr)
		{
			throw std::runtime_error("Trying to check balance before logging in\n");
		}
		system("cls");
		printCheckBalanceScreenHeader();
		cout << "Your balance is: " << currClient->accountBalance;
		putchar('\n'); putchar('\n'); putchar('\n');
		cout << "You will be redirected to ATM Main Menu Screen Soon\n";
		this_thread::sleep_for(chrono::seconds(3));
	}
	void deposit(clientRecord*& currClient)
	{
		if (currClient == nullptr)
		{
			throw std::invalid_argument("Trying to deposit before logging in\n");
		}
		double amountToDeposit = 0;
		amountToDeposit = UserInput::readPositivedouble("Enter a positive deposit amount\n");
		char choice = 'n';
		cout << "Are you sure you want to perform this transaction? y/n\n";
		cin >> choice;
		if (choice == 'y')
		{
			currClient->accountBalance += amountToDeposit;
			client_Op::saveNonMarkedClientsForDeletionDataToFile(currClientFileName, s);
			cout << "Amount deposited Successfully.. New balance is: " << currClient->accountBalance << endl;
		}
		else
		{
			clog << "Deposit attempt for client account number: " << currClient->accountNumber << " has been cancelled by user\n";
			this_thread::sleep_for(chrono::seconds(2));
			return;
		}
		cout << "You will be returned to ATM Main Menu Screen Soon\n";
		this_thread::sleep_for(chrono::seconds(4));
	}
	void QuickWithdraw(clientRecord*& currClient)
	{
		if (currClient == nullptr)
		{
			throw std::invalid_argument("Trying to withdraw before logging in\n");
		}
		system("cls");
		printQuickWithdrawScreen();
		printf_s("Your balance is %.3lf\n", currClient->accountBalance);
		int choice;
		choice = UserInput::readIntegerNumberInRange(1, 9, "Choose [1,9]\n");
		uint16_t values[] = { 20,50,100,200,400,600,800,1000 };
		const uint16_t sz_Values = sizeof(values) / sizeof(values[0]);
		switch (choice)
		{
		case 1:
			withdrawFromAccount(currClient, values[0]);
			break;
		case 2:
			withdrawFromAccount(currClient, values[1]);
			break;
		case 3:
			withdrawFromAccount(currClient, values[2]);
			break;
		case 4:
			withdrawFromAccount(currClient, values[3]);
			break;
		case 5:
			withdrawFromAccount(currClient, values[4]);
			break;
		case 6:
			withdrawFromAccount(currClient, values[5]);
			break;
		case 7:
			withdrawFromAccount(currClient, values[6]);
			break;
		case 8:
			withdrawFromAccount(currClient, values[7]);
			break;
		case 9:
			return;
		default:
			throw std::invalid_argument("Invalid Choice!\n");
		}
	}
	void LoggingOut(clientRecord*& currClient)
	{
		currClient = nullptr;
		throw LogoutException();
	}
	void performChosenATM_OperationsBasedOnChoice(ATM_operations op, clientRecord*& currClient)
	{
		switch (op)
		{
		case ATM_operations::QuickWithdraw:
			QuickWithdraw(currClient);
			print_ATM_MainMenuScreen(currClient);
			break;
		case ATM_operations::NormalWithdraw:
			NormalWithdraw(currClient);
			print_ATM_MainMenuScreen(currClient);
			break;

		case ATM_operations::Deposit:
			deposit(currClient);
			print_ATM_MainMenuScreen(currClient);
			break;
		case ATM_operations::CheckBalance:
			checkBalance(currClient);
			print_ATM_MainMenuScreen(currClient);
			break;

		case ATM_operations::Logout:
			LoggingOut(currClient);
			break;
		default:
			throw std::invalid_argument("Program Failure!\n");
		}
	}
	void print_ATM_MainMenuScreen(clientRecord*& currClient)
	{
		system("cls");
		int choice;
		printATM_MainMenuScreenHeader();
		cout << "\t\t[1] Quick Withdraw\n";
		cout << "\t\t[2] Normal Withdraw\n";
		cout << "\t\t[3] Deposit\n";
		cout << "\t\t[4] Check Balance\n";
		cout << "\t\t[5] Logout\n";
		printf_s("============================================================\n");
		choice = UserInput::readIntegerNumberInRange(1, 5, "Choose what do you want to do? [1 to 5]\n");
		cin.ignore(1, '\n');
		performChosenATM_OperationsBasedOnChoice(static_cast<ATM_operations>(choice),currClient);
	}
	
	void printATM_MainMenuScreenHeader()
	{
		printf_s("============================================================\n");
		printf_s("\t\t\t ATM Main Menu Screen\n");
		printf_s("============================================================\n");
	}
	void printLoginScreenHeader()
	{
		printf_s("============================================================\n");
		printf_s("\t\t\t Login Screen\n");
		printf_s("============================================================\n");
	}

}