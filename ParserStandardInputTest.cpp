#include "Parser.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	int numData = 5;
	int numField = 5;
	
	Parser* standardInputParser = new Parser(numData, numField);
	cout << "Enter " << numData << " lines of data consisting of " << numField << " fields, separated by '" << standardInputParser->getDelimiter() << "'." << endl;
	cout << "Note: excess data and fields are discarded, and missing fields are filled in as empty strings." << endl;
	
	string inputStr;

	for (int i = 0; i < standardInputParser->getNumData(); i++)
	{
		cout << ">> ";
		getline(cin, inputStr);
		standardInputParser->append(inputStr);
	}

	for (int i = 0; i < standardInputParser->getNumData(); i++)
	{
		string* curArr = standardInputParser->getData(i);
		cout << "Line " << i + 1 << ": ";
		for (int j = 0; j < standardInputParser->getNumField(); j++)
		{
			string curField = curArr[j];
			cout << "[" << curField << "] ";
		}
		cout << endl;
	}

	return 0;
}