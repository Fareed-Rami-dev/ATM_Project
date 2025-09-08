#include "User_Input.h"
namespace UserInput {
	int readIntegerNumberInRange(int from, int to, string message) 
	{
		int x;
		do
		{
			cout << message << '\a' << endl;
			while (std::cin.fail() || !(std::cin >> x))
			{
				cout << "Invalid! Please re-enter\n";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		} while (x < from || x>to);
		return x;
	}
	double readPositivedouble(string message)
	{
		double x;
		do
		{
			cout << message << '\a' << endl;
			cin >> x;
		} while (x <= 0.00000);
		return x;
	}
}