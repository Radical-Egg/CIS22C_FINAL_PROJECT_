//
//  main.cpp
//  FinalProject
//
//  Created by Kevin Jin on 6/6/20.
//  Copyright © 2020 Kevin Jin. All rights reserved.
//
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <limits>
#include "hash.h"
#include "Parser.h"
#include "House.h"

const int NUM_FIELDS = 6;


using namespace std;

Hash* dataHash = new Hash();

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void createDataFromCSV()
{
    Parser* CSVParser = new Parser(1, NUM_FIELDS);
    House* newHouse = nullptr;
    ifstream csvFile;
    string filePath;
    int numData;

    cout << "Enter CSV file path: ";
    
    do
    {
        cin >> filePath;
        csvFile.open(filePath);
        if (!csvFile.is_open())
        {
            cout << "Invalid file path. Please try again: ";
        }
        clearInput();
    } 
    while (!csvFile.is_open());

    cout << "How many data to read from the CSV file: ";

    while (!(cin >> numData))
    {
        cout << "Invalid input. Please try again: ";
        clearInput();
    }

    for (int i = 0; i < numData; i++)
    {
        try
        {
            string inputStr;
            if (!getline(csvFile, inputStr))
            {
                inputStr = "";
            }
            CSVParser->setData(0, inputStr);
            string* curData = CSVParser->getData(0);
            newHouse = new House(curData[0], stol(curData[1]), stoi(curData[2]), stoi(curData[3]), curData[4], stoi(curData[5]));
            dataHash->addItem(newHouse->getAddress(), newHouse->getPrice(), newHouse->getBeds(), newHouse->getBaths(), newHouse->getType(), newHouse->getArea());
            //dataBST->insert(newHouse);
        }
        catch (const std::invalid_argument& e)
        {
            cout << "Error parsing data " << i + 1 << " (" << e.what() << ")." << endl;
        }

    }

    //dataHash->printTable();

    clearInput();
    delete CSVParser;
    delete newHouse;
}

// main and menu function with input checking
int main() {
    // loading data into hash table
    createDataFromCSV();

    // flag for menu
    bool flag = true;

    // main menu
    while (flag)
    {
        // menu options
        cout << "San Jose Housing Listing Service" << endl;
        cout << "--------------------------------" << endl;
        cout << "A. Add new data" << endl;
        cout << "B. Delete data" << endl;
        cout << "C. Search and display data using the primary key" << endl;
        cout << "D. List data in hash table sequence" << endl;
        cout << "E. List data in sorted key sequence" << endl;
        cout << "F. Print indented tree" << endl;
        cout << "G. Efficiency" << endl;
        // TODO: team choice menu option
        cout << "H. Team choice menu option" << endl;
        cout << "X. Quit" << endl << endl;
        cout << "Enter a Choice: " << endl;

        //clearInput();
        // user response variable, temp node(node is a struct that has the housing data) 
        char userResponse;
        Node temp;
        userResponse = toupper(getchar()); // touppper the response so it is not case sensitive

        switch (userResponse) {
            case 'A': { // adding data to hash table
                cout << "Add data to the Hash Table" << endl;
                clearInput(); // clear buffer and enter values - the while loop makes certain the value is of int

                // key
                cout << "Enter Key Value: ";
                getline(cin, temp.key);

                // price
                cout << "Enter Price: ";
                while (!(cin >> temp.price)) // while loop to ensure user puts in int values
                {
                    cout << "input is not valid, integers only" << endl;
                    cout << "Enter Price: ";
                    cin.clear();
                    cin.ignore(123, '\n');
                }

                // beds
                cout << "Enter Amount of beds: ";
                while (!(cin >> temp.beds)) // while loop to ensure user puts in int values
                {
                    cout << "input is not valid, integers only" << endl;
                    cout << "Enter Beds: ";
                    cin.clear();
                    cin.ignore(123, '\n');
                }

                // baths
                cout << "Enter Amount of Baths: ";
                while (!(cin >> temp.baths)) // while loop to ensure user puts in int values
                {
                    cout << "input is not valid, integers only" << endl;
                    cout << "Enter Baths: ";
                    cin.clear();
                    cin.ignore(123, '\n');
                }

                // prop type
                cout << "Enter Property Type: ";
                clearInput();
                getline(cin, temp.prop_type);
                
                // area
                cout << "Enter Area: ";
                while (!(cin >> temp.area)) // while loop to ensure user puts in int values
                {
                    cout << "input is not valid, integers only" << endl;
                    cout << "Enter Area: ";
                    cin.clear();
                    cin.ignore(123, '\n');
                }

                // add item to hash table
                dataHash->addItem(temp.key, temp.price, temp.beds, temp.baths, temp.prop_type, temp.area);
            
                // getchar() does the same as system("pause") I am on linux and don't have a system pause so please swap this out with system("pause")
                cout << "Press Any Key to Continue" << endl;
                getchar();
                getchar();

                break;
            } case 'B': {
                // deleting items from hash
                cout << "Delete Data from Hash Table" << endl;
                cout << "Enter the key you would like to delete" << endl;
                // enter the key
                clearInput();
                getline(cin, temp.key);

                // remove the data
                dataHash->removeItem(temp.key);
                break;
            } case 'C': {
                cout << "Search for Entry in the Hash Table by Key (Address): " << endl;
                clearInput();
                getline(cin, temp.key);

                dataHash->searchItem(temp.key);

                break;
            } case 'D': {
                // printing options
                cout << "Select from the following:\nA. Print Hash Table\nB. Print Bucket" << endl;

                // get user input for what they want to print
                clearInput();
                userResponse = toupper(getchar());
                // nested menu
                switch(userResponse)
                {
                    // print the whole hash table
                    case 'A':
                        dataHash->printTable();
                        break;
                    case 'B':
                        // print the table by searching for bucket 
                        cout << "Input the Bucket you are looking for: ";
                        clearInput();
                        getline(cin, temp.key);
                        dataHash->printItemsInBucket(temp.key);

                        break;
                    default:
                        cout << "Not a Valid option" << endl;
                        break;
                }
                // getchar() does the same as system("pause") I am on linux and don't have a system pause so please swap this out with system("pause")
                cout << "Press Any Key to go back to Main Menu" << endl;
                getchar();
                getchar();
                break;
            } case 'E': {
                break;
            } case 'F': {
                break;
            } case 'G': {
                break;
            } case 'H': {
                break;
            } case 'X': {
                flag = false;
                break;
            } default: {
                cout << "Input Not Valid!" << endl;
                break;
            }
        }

    }
    return 0;
}
