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

#include <string>
#include <iostream>
using namespace std;
namespace UserInput {
	double readPositivedouble(string message);
	int readIntegerNumberInRange(int from, int to, string message);
}