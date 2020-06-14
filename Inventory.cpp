#include "Inventory.h"

#include <fstream>
#include <iostream>
#include <iomanip>

Inventory::Inventory() {
  invArrSize = 1;
  inventory = new House[1];
  invSize = 0;
  HouseData = "";
}

Inventory::Inventory(std::string HouseData) {
//  this->HouseData = HouseData;
//  invSize = 0;
//
//  std::ifstream dataFile(HouseData, std::ios::in);
//
//  if (dataFile.is_open()) {
//    char tmpChar1 = ' ';
//    char tmpChar2 = ' ';
//
//    dataFile.get(tmpChar1);
//    dataFile.get(tmpChar2);
//
//    // Looks at file to see how large to make the House array
//    while (!dataFile.eof()) {
//      // Due to layout of file, two newlines in a row signify a new House
//      // Since there is an extra line between each House in the file
//      if (tmpChar1 == '\n' && tmpChar2 == '\n') {
//        invSize++;
//      }
//
//      // unget() goes back one character in the file
//      dataFile.unget();
//      dataFile.get(tmpChar1);
//      dataFile.get(tmpChar2);
//    }
//
//    invArrSize = invSize;
//    inventory = new House[invArrSize];
//
//    dataFile.clear();
//    dataFile.seekg(0, std::ios::beg);
//
//    // This is where the dataFile is actually copied into the House
//    for (int idx = 0; idx < invSize; idx++) {
//      dataFile >> inventory[idx];
//    }
//
//    dataFile.close();
//  }
//  else {
//    std::cout << "Error: file path not found\n";
//  }
}

Inventory::Inventory(int invArrSize, House inventory[],
  int invSize, std::string HouseData) {
  this->invArrSize = invArrSize;
  this->inventory = new House[invArrSize];
  this->invSize = invSize;
  this->HouseData = HouseData;

  for (int idx = 0; idx < invArrSize; idx++) {
    (this->inventory)[idx] = inventory[idx];
  }
}

Inventory::Inventory(const Inventory& i) {
  invArrSize = i.invArrSize;
  inventory = new House[invArrSize];
  invSize = i.invSize;
  HouseData = i.HouseData;

  for (int idx = 0; idx < invArrSize; idx++) {
    inventory[idx] = i.inventory[idx];
  }
}

Inventory::~Inventory() {
  delete [] inventory;
}

int Inventory::getInvSize() const {
  return invSize;
}

House Inventory::searchHouse(std::string address) const {
  for (int i = 0; i < invSize; i++) {
    if (inventory[i].getAddress() == address)
      return inventory[i];
  }

  return House();
}

void Inventory::addHouse(House house, bool update) {
    ++invSize;

    if (invSize > invArrSize) {
      House* tempInv = new House[invArrSize + 50];
      for (int i = 0; i < invArrSize; i++) {
        tempInv[i] = inventory[i];
      }
      invArrSize += 50;
      tempInv[invSize - 1] = house;
      delete[] inventory;
      inventory = tempInv;
    }
    
    if (update)
        updateHouseData();
}

void Inventory::addHouse(std::string address, long price, int beds, int baths, std::string type, int area, bool update) {
  House tmpHouse(address, price, beds, baths, type, area);

  addHouse(tmpHouse, update);
}

bool Inventory::deleteHouse(House House) {
  for (int idx = 0; idx < invSize; ++idx) {
    if (inventory[idx].getAddress() == House.getAddress()) {
        inventory[idx] = inventory[invSize - 1];
        invSize--;
    }
    updateHouseData();

    return true;
  }
  
  return false;
}

bool Inventory::deleteHouse(std::string address) {
  for (int idx = 0; idx < invSize; ++idx) {
    if (inventory[idx].getAddress() == address) {
        inventory[idx] = inventory[invSize - 1];
        invSize--;
    }

    updateHouseData();
    return true;
  }

  return false;
}

// Below are all the private member functions of the Inventory class
void Inventory::updateHouseData() {
  std::ofstream out;
  out.open(HouseData);
  if (out.is_open()) {
    for (int idx = 0; idx < invSize; ++idx) {
      out << inventory[idx].getAddress() << ","
        << inventory[idx].getPrice() << ","
        << inventory[idx].getBeds() << ","
        << inventory[idx].getBaths() << ","
        << inventory[idx].getType() << ","
        << inventory[idx].getArea() << "," << std::endl;
    }
  }
  else {
    std::cout << "ERROR: File path was not found." << std::endl;
  }
}

/*
void operator=(const StudentTestScores &right)
{ delete [] testScores;
65 studentName = right.studentName;
66 numTestScores = right.numTestScores;
67 testScores = new double[numTestScores];
68 for (int i = 0; i < numTestScores; i++)
69 testScores[i] = right.testScores[i]; }
 */

void Inventory::operator=(const Inventory &right) {
    invArrSize = right.invArrSize;
    inventory = new House[invArrSize];
    invSize = right.invSize;
    HouseData = right.HouseData;

    for (int idx = 0; idx < invArrSize; idx++)
      inventory[idx] = right.inventory[idx];
}
