#include "ATM_System.h"
#include "strOperations.h"
namespace client_Op {
	vector<clientRecord> gatherRecordsFromFormattedClientRecordsFile(string filename)
	{
		vector<clientRecord> vecClientsRecord;
		fstream file;
		file.open(filename, ios::in);
		if (!(file.is_open()))
		{
			throw std::runtime_error("Cannot Open File!\n");
		}
		string eachLine;
		while (getline(file, eachLine))
		{
			if (eachLine == "" || eachLine == " ")
				continue;
			clientRecord clientRecord = convertLineDataToRecord(eachLine);
			vecClientsRecord.push_back(clientRecord);
		}
		file.close();
		return vecClientsRecord;
	}

	clientRecord convertLineDataToRecord(string lineData, string delimeter)
	{
		vector<string> strVec = strOperations::splitStringIntoWordsAndStoreToVector(lineData, delimeter);
		if (strVec.size() != numberOfClientFieldsInfo)
		{
			throw std::runtime_error("Can't generate Client Record\n");
		}
		clientRecord client;
		client.accountNumber = strVec[0];
		client.PIN_CODE = strVec[1];
		client.FullName = strVec[2];
		client.phone = strVec[3];
		client.accountBalance = stod(strVec[4]);
		client.markedForDeletion = (strVec[5] == "true" ? true : false);
		return client;
	}


	bool doesClientExistsByAccountNumber(string accountNumber, vector<clientRecord>& v, clientRecord*& cl)
	{
		for (clientRecord& r : v)
		{
			if (r.accountNumber == accountNumber) {
				cl = &r;
				return true;
			}
		}
		return false;
	}
	std::string boolToString(bool value) {
		return value ? "true" : "false";
	}
	string readAccountNumber()
	{
		string accountNo;
		printf_s("Enter the account number\n");
		getline(cin, accountNo);
		return accountNo;
	}
	void printClientRecord(const clientRecord client)
	{
		cout << "Client Info" << endl;
		cout << "Account Number:" << client.accountNumber << endl;
		cout << "PIN CODE: " << client.PIN_CODE << endl;
		cout << "Client Full Name: " << client.FullName << endl;
		cout << "Client Phone Number: " << client.phone << endl;
		cout << "Client Account Balance: " << client.accountBalance << endl;
		cout << "Client To be deleted Status: " << boolToString(client.markedForDeletion) << endl;
	}
	string generateClientRecordString(const clientRecord, string); //Prototype
	void saveNonMarkedClientsForDeletionDataToFile(string fileName, vector<clientRecord>& s)
	{
		fstream file;
		file.open(fileName, ios::out);
		if (!(file.is_open()))
		{
			throw std::runtime_error("File does not exist!\n");
		}
		string clientInfo;
		for (const clientRecord& client : s)
		{
			if (!(client.markedForDeletion))
			{
				clientInfo = generateClientRecordString(client);
				if (clientInfo == " " || clientInfo == "")
					continue;
				file << clientInfo << endl;
			}
		}
		file.close();
	}

	string generateClientRecordString(const clientRecord client, string delimeter)
	{
		string str;
		str.append(client.accountNumber);
		str.append(delimeter);
		str.append(client.PIN_CODE);
		str.append(delimeter);
		str.append(client.FullName);
		str.append(delimeter);
		str.append(client.phone);
		str.append(delimeter);
		str.append(to_string(client.accountBalance));
		str.append(delimeter);
		str.append(boolToString(client.markedForDeletion));
		return str;
	}

}