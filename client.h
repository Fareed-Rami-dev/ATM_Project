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
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

struct clientRecord {
    string accountNumber;
    string PIN_CODE;
    string FullName;
    string phone;
    double accountBalance;
    bool markedForDeletion;
};

namespace client_Op {
    vector<clientRecord> gatherRecordsFromFormattedClientRecordsFile(string filename);
    clientRecord convertLineDataToRecord(string lineData, string delimeter = "#//#");
    bool doesClientExistsByAccountNumber(string accountNumber, vector<clientRecord>& v, clientRecord*&);
    string boolToString(bool value);
    string readAccountNumber();
    void printClientRecord(const clientRecord client);
    string generateClientRecordString(const clientRecord client, string delimeter = "#//#");
    void saveNonMarkedClientsForDeletionDataToFile(string, vector<clientRecord>&);
}