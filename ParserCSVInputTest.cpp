#include "Parser.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/* 
	For CSV files, unless the headers are
	removed from the file, the data actually 
	starts on line 2.
*/

int main()
{
	int numData = 51;
	int numField = 6;
	
	Parser* csvInputParser = new Parser(numData, numField);

	ifstream csvFile;
	csvFile.open("db.csv");

	string inputStr;

	if (csvFile.is_open())
	{
		for (int i = 0; i < csvInputParser->getNumData(); i++)
		{
			if (!getline(csvFile, inputStr))
			{
				inputStr = "";
			}
			csvInputParser->append(inputStr);
		}

		for (int i = 0; i < csvInputParser->getNumData(); i++)
		{
			string* curArr = csvInputParser->getData(i);
			cout << "Line " << i + 1 << ": ";
			for (int j = 0; j < csvInputParser->getNumField(); j++)
			{
				string curField = curArr[j];
				cout << "[" << curField << "] ";
			}
			cout << endl;
		}
	}
	else
	{
		cout << "File not found." << endl;
	}
	return 0;
}