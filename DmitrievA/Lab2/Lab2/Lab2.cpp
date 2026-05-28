"Copyright 2026 Alexey Dmitriev"

#include <fstream>
#include <iostream>
#include <string>

#include "OrderedTable.h"
#include "Polinom.h"
#include "UnorderedTable.h"
#include "experements.h"

    using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::string;

Polinom enter_polinom() {
  cout << "Choose input format of polinome:" << endl;
  cout << "1. First number N - count of monomes.Next N pairs of numbers - "
          "monomes.First number at "
          "pair - coefficient.Second - degree(must be between 0 and "
          "999).Example:"
       << endl;
  cout << "3\n2 111\n3 123\n10 0\n";
  cout << "2. Human readable format. Example: x^2y^3z^4 + 2*xy4z - 5x - "
          "10x2y3z4 + 1\n";
  int mode;
  cin >> mode;
  while (mode != 1 && mode != 2) {
    cout << "Invalid input. Please enter 1 or 2." << endl;
    cin >> mode;
  }
  cin.clear();

  Polinom polinom;
  ParseMode parse_mode = (mode == 1) ? Simple : Human;
  polinom.parseMode = parse_mode;
  cout << "Enter polinome:" << endl;
  bool valid_input = false;
  while (!valid_input) {
    try {
      cin >> polinom;
      valid_input = true;
    } catch (const std::exception&) {
      cout << "Invalid input. Please try again." << endl;
    }
  }
  cout << "You entered: " << polinom << endl;
  return polinom;
}

int main() {
  cout << "commands:" << endl;
  cout << "1. Insert polynomial" << endl;
  cout << "2. Find polynomial by string" << endl;
  cout << "3. remove polynomial by string" << endl;
  cout << "4. Exit" << endl;
  unsigned insertUnordered = 0, findUnordered = 0, removeUnordered = 0;
  unsigned insertAVL = 0, findAVL = 0, removeAVL = 0;
  unsigned insertHash = 0, findHash = 0, removeHash = 0;
  UnorderedTable<Polinom> unorderedTable;
  AVLOrderedTable<Polinom> avlOrderedTable;
  HashOrderedTable<Polinom> hashOrderedTable(100);
  int command = -1;
  while (command != 4) {
    cin >> command;
    switch (command) {
      case 1: {
        Polinom polinom = enter_polinom();
        string name;
        cin >> name;
        unorderedTable.insert(name, polinom);
        avlOrderedTable.insert(name, polinom);
        hashOrderedTable.insert(name, polinom);
        insertUnordered += unorderedTable.getCount();
        insertAVL += avlOrderedTable.getCount();
        insertHash += hashOrderedTable.getCount();
      }
      case 2: {
        cout << "Enter string to find:" << endl;
        string str;
        cin >> str;
        Polinom* resUnordered = unorderedTable.find(str);
        Polinom* resAVL = avlOrderedTable.find(str);
        Polinom* resHash = hashOrderedTable.find(str);
        findUnordered += unorderedTable.getCount();
        findAVL += avlOrderedTable.getCount();
        findHash += hashOrderedTable.getCount();
        if (resUnordered)
          cout << "Unordered table: " << *resUnordered << endl;
        else
          cout << "Unordered table: not found" << endl;
        if (resAVL)
          cout << "AVL ordered table: " << *resAVL << endl;
        else
          cout << "AVL ordered table: not found" << endl;
        if (resHash)
          cout << "Hash ordered table: " << *resHash << endl;
        else
          cout << "Hash ordered table: not found" << endl;
        break;
      }
      case 3: {
        cout << "Enter string to remove:" << endl;
        string str;
        cin >> str;
        unorderedTable.remove(str);
        avlOrderedTable.remove(str);
        hashOrderedTable.remove(str);
        removeUnordered += unorderedTable.getCount();
        removeAVL += avlOrderedTable.getCount();
        removeHash += hashOrderedTable.getCount();
        break;
      }
      case 4: {
        cout << "Exiting..." << endl;
        ofstream fileStream;
        fileStream.open("log.txt", std::ios::out);
        fileStream << "Operations count:" << endl;
        fileStream << "\tUnorderedTable: " << endl;
        fileStream << "\t\tInsert: " << insertUnordered << endl;
        fileStream << "\t\tFind: " << findUnordered << endl;
        fileStream << "\t\tRemove: " << removeUnordered << endl;
        fileStream << "\tAVLTable: " << endl;
        fileStream << "\t\tInsert: " << insertAVL << endl;
        fileStream << "\t\tFind: " << findAVL << endl;
        fileStream << "\t\tRemove: " << removeAVL << endl;
        fileStream << "\tHashTable: " << endl;
        fileStream << "\t\tInsert: " << insertHash << endl;
        fileStream << "\t\tFind: " << findHash << endl;
        fileStream << "\t\tRemove: " << removeHash << endl;
        break;
      }
      default:
        cout << "Invalid command. Please try again." << endl;
        break;
    }
  }
}
