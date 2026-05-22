#include "Table_Manager.h"
int main() { 
  // all the logics have been described in Table_Manager.h
  int hashTableSize = 10;
  std::cout << "Before get started, enter the hash table's size\n";
  std::cin >> hashTableSize;
  TableManager<Polinomial> manager(hashTableSize);
  manager.Run();
  return 0;
}