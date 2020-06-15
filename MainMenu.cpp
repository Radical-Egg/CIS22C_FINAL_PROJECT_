/*
 assumptions:
 1. The CSV file taken in has a header line.
 */
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <limits>
#include "hash.h"
#include "BST.h"
#include "Parser.h"
#include "Inventory.h"

//TODO: delete from file when deleted house
//TODO: add to file when added

using namespace std;

const int NUM_FIELDS = 6;
Hash<House>* dataHash = new Hash<House>();
BST<House> dataTree;

// The following array is for the inventory:
// - doesn't matter what House array size initialized to since addHouse function automatically increments the size, similar to a vector
// - dataInv has empty string which will be changed to filePath in the createData function
House* inventory = new House[25];
Inventory dataInv(25, inventory, 0, "");

/*
 Clears the input and ignores one line of data.
 Pre: None
 Post: input stream skips to next line
 Return: None
 */
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/*
 Reads data from CSV into hash table and bst, skipping the header line.
 Pre: None
 Post: data from CSV in hash table and bst
 Return: None
 */
void createDataFromCSV() {
    Parser* CSVParser = new Parser(1, NUM_FIELDS);  // 1 indicates 1 entry from csv file taken
    House* newHouse = nullptr;
    ifstream csvFile;
    string filePath;
    
    cout << "Enter CSV file path: ";
   
    do {
        cin >> filePath;
        csvFile.open(filePath);
        if (!csvFile.is_open())
            cout << "Invalid file path. Please try again: ";
        clearInput();
    } while (!csvFile.is_open());

    // counts total number of houses in file
    ifstream helperCSVFile;
    helperCSVFile.open(filePath);
    string helperCntData;
    int totalData = 0;
    while (getline(helperCSVFile, helperCntData))
        ++totalData;
    --totalData;
    
    int numData = 0;
    cout << "Enter the number of houses to read from the CSV file: ";
    while (!(cin >> numData) || numData > totalData || numData < 0) {
        cout << "Invalid input. Please try again: ";
        clearInput();
    }
    
    dataInv.setHouseData(filePath);
    
    // look over header line that takes up one from numData
    for (int i = 0; i < numData + 1; i++) {
        try {
            // read line and set it to inputStr
            string inputStr;
            getline(csvFile, inputStr);
            //cout << inputStr << endl;
            
            // skip the header line of csv file
            if (i == 0) continue;
            
            cout << "yoyo" << endl;
            cout << inputStr << endl;
            CSVParser->setData(0, inputStr);    // 0 signifies 1 data entry set
            string* curData = CSVParser->getData(0);
            newHouse = new House(curData[0], stoll(curData[1]), stoi(curData[2]), stoi(curData[3]), curData[4], stoi(curData[5]));
            
            /*
             adding house to hash table:
             - integer precision loss okay because price only used as key
             - when truncating long long to int, deletes excess 32 bits
            */
            dataHash->addItem(newHouse->getAddress(), newHouse);
            
            // adding house to BST
            dataTree.insert(newHouse);
            
            // adding house to inventory's array: set to false to prevent rewriting of file
            dataInv.addHouse(*newHouse, false);
        } catch (const std::invalid_argument& e) {
            cout << "Error parsing data " << i + 1 << " (" << e.what() << "). Data is not added." << endl;
        }
        
        // delete newHouse;
        // newHouse = nullptr;
    }
    
    dataInv.updateHouseData();
    
    delete CSVParser;
    clearInput();
}

int main() {
    // loading data
    
    createDataFromCSV();

    // flag for menu
    bool flag = true;
    
    // main menu
    while (flag)
    {
        // menu options
        cout << endl;
        cout << "San Jose Housing Listing Service" << endl;
        cout << "--------------------------------" << endl;
        cout << "1. Add house" << endl;
        cout << "2. Delete house" << endl;
        cout << "3. Search house by address" << endl;
        cout << "4. List houses in hash table sequence" << endl;
        cout << "5. List house price in ascending order" << endl;
        cout << "6. List house price in given range" << endl;
        cout << "7. Print house price indented tree" << endl;
        cout << "8. Efficiency" << endl;
        cout << "9. Quit" << endl << endl;
        cout << "Enter your choice: ";

        //clearInput();
        // user response variabl
        int userResponse;
        while (!(cin >> userResponse)) {
            cout << "Invalid input. Please enter a number (1-9): ";
            clearInput();
        }
        
        string key, type;
        int price, beds, baths, area;
        
        switch (userResponse) {
            case 1: { // adding data to hash table
                // address
                cout << "Enter the address: ";
                clearInput();
                getline(cin, key);
                
                // price
                cout << "Enter the price: ";
                while (!(cin >> price)) // while loop to ensure user puts in int values
                {
                    cout << "Invalid input. Please enter a whole number: " << endl;
                    cin.clear();
                    cin.ignore(123, '\n');
                }

                // beds
                cout << "Enter the number of beds: ";
                while (!(cin >> beds)) // while loop to ensure user puts in int values
                {
                    cout << "Invalid input. Please enter a whole number: " << endl;
                    cin.clear();
                    cin.ignore(123, '\n');
                }

                // baths
                cout << "Enter the number of baths: ";
                while (!(cin >> baths)) // while loop to ensure user puts in int values
                {
                    cout << "Invalid input. Please enter a whole number: " << endl;
                    cin.clear();
                    cin.ignore(123, '\n');
                }

                // prop type
                cout << "Enter the property type: ";
                clearInput();
                getline(cin, type);
                
                // area
                cout << "Enter the area (sq. ft.): ";
                while (!(cin >> area)) // while loop to ensure user puts in int values
                {
                    cout << "Invalid input. Please enter a whole number: " << endl;
                    cin.clear();
                    cin.ignore(123, '\n');
                }
                
                clearInput();

                // add item to hash table, bst, and inventory
                House* toInsert = new House(key, price, beds, baths, type, area);
                dataHash->addItem(key, toInsert);
                dataTree.insert(toInsert);
                dataInv.addHouse(*toInsert);
                
                break;
            } case 2: {
                cout << "Enter the address of the house to delete: ";
                clearInput();
                getline(cin, key);
                
                // remove from bst
                auto result = dataHash->getNode(key);
                if (result) {
                    House tmp;
                    tmp.setPrice(result->data->getPrice());
                    dataTree.remove(&tmp);
                    std::cout << "House at " << key << " deleted." << std::endl;
                }
                
                // remove from hash
                dataHash->removeItem(key);
                
                // remove from inventory
                dataInv.deleteHouse(key);
                
                break;
            } case 3: {
                cout << "Enter the address: ";
                clearInput();
                getline(cin, key);

                dataHash->searchItem(key);
                
                break;
            } case 4: {
                bool innerFlag = true;
                while (innerFlag != false) {
                    // printing options
                    cout << endl;
                    cout << "1. Print bucket index, number of items, and key\n2. Print specified bucket\n3. Print entire hash table\n4. Return to main menu" << endl << endl;
                    cout << "Enter your choice: ";

                    int userResponse;
                    while (!(cin >> userResponse)) {
                        cout << "Invalid input. Please enter a number (1-9): ";
                        clearInput();
                    }
                    
                    // nested menu
                    switch(userResponse) {
                        // print the whole hash table
                        case 1:
                            dataHash->printTable();
                            break;
                        case 2:
                            // print the table by searching for bucket
                            cout << "Input the bucket key: " << endl;
                            clearInput();
                            getline(cin, key);
                            dataHash->printItemsInBucket(key);
                            break;
                        case 3:
                            dataHash->printEntireTable();
                            break;
                        case 4:
                            innerFlag = false;
                            break;
                        default:
                            cout << "Input not valid! Number out of range." << endl;
                            break;
                    }
                }
                break;
            } case 5: {
                dataTree.printBySortedKey(cout);
                break;
            } case 6: {
                // initialize min and max
                long min, max;
                cout << "Enter the minimum price in the range: ";
                while (!(cin >> min)) {
                    cout << "Invalid input. Please try again: ";
                    clearInput();
                }
                cout << "Enter the maximum price in the range: ";
                while (!(cin >> max)) {
                    cout << "Invalid input. Please try again: ";
                    clearInput();
                }
                // create min and max housing objects
                House minHouse;
                minHouse.setPrice(min);
                House maxHouse;
                maxHouse.setPrice(max);
                // pass min and max housing objects into printInRange
                dataTree.printInRange(minHouse, maxHouse);
                clearInput();
                break;
            } case 7: {
                dataTree.printIndentedTree(cout);
                break;
            } case 8: {
                cout << endl;
                cout << "Hash Table" << endl;
                cout << "----------" << endl;
                cout << "Load factor: " << dataHash->getNodeCnt() / double(tableSize) << endl
                    << "Longest linked list: " << dataHash->getLongestListSize() << endl
                    << "Average number of nodes in linked lists: " << dataHash->getAverageListSize() << endl
                    << "Number of collisions in hash table " << dataHash->getNumCollisions() << endl;
                cout << "Binary Search Tree" << endl;
                cout << "------------------" << endl
                    << "Average number of operations to insert in BST: " << endl
                    << "Average number of operations to search in BST: " << endl << endl;
                break;
            } case 9: {
                flag = false;
                break;
            } default: {
                cout << "Input not valid! Number out of range." << endl;
                break;
            }
        }
    }
    return 0;
}
