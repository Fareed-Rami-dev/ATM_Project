#include "strOperations.h"
namespace strOperations {
	vector<std::string> splitStringIntoWordsAndStoreToVector(string text, string delimeter)
	{
		vector<string> strVector; size_t pos; string sWord;
		while ((pos = text.find(delimeter)) != std::string::npos)
		{
			sWord = text.substr(0, pos);
			if (sWord != "")
			{
				strVector.push_back(sWord);
			}
			text.erase(0, pos + delimeter.length());
		}
		if (text != "")
		{
			strVector.push_back(text);
		}
		return strVector;
	}
}