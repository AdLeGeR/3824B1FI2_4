#include "../lib_interface/interface.h"

InterfacePol::InterfacePol() : Pol1(), Pol2() {}

InterfacePol::~InterfacePol() {}

Polynomial InterfacePol::sum() const { return Pol1 + Pol2; }

Polynomial InterfacePol::sub() const { return Pol1 - Pol2; }

Polynomial InterfacePol::mul() const { return Pol1 * Pol2; }

Polynomial InterfacePol::sum2() const { return Pol2 + Pol1; }

Polynomial InterfacePol::sub2() const { return Pol2 - Pol1; }

void InterfacePol::input_polyn() {
  std::cout << "Entering the polynomial number 1" << std::endl;
  Pol1.record();
  std::cout << "Entering the polynomial number 2" << std::endl;
  Pol2.record();
}

void InterfacePol::actions() {
  bool flage = true;
  int a;
  Polynomial rez;
  while (flage) {
      while (true) {
          std::cout << "What to do with polynomials?\n1 - Pol1 + Pol2\n2 - Pol1 - "
              "Pol2\n3 - Pol1 * Pol2\n4 - Pol2 + Pol1\n5 - Pol2 - Pol1\n0 - "
              "Exit\nEnter the number indicating the action: ";
          std::cin >> a;
          if (std::cin.fail()) {
              std::cout << "Error: Invalid input!" << std::endl;
              std::cin.clear();
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          }
          else
              break;
      }

    switch (a) {
    case 1:
      rez = sum();
      flage = false;
      break;

    case 2:
      rez = sub();
      flage = false;
      break;

    case 3:
      rez = mul();
      flage = false;
      break;

    case 4:
      rez = sum2();
      flage = false;
      break;

    case 5:
      rez = sub2();
      flage = false;
      break;

    case 0:
      std::cout << "\nGoodbye!";
      return;

    default:
      std::cout << "\nincorrect value\n";
    }

    std::cout << rez << std::endl;
    
    while (true) {
        std::cout << "\ndo you want to continue with the same polynomials?\n1 - "
            "yes\n2 - no\n3 - Exit\n";
        std::cin >> a;
        if (std::cin.fail()) {
            std::cout << "Error: Invalid input!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
            break;
    }
    switch (a) {
    case 1:
      flage = true;
      break;

    case 2:
      input_polyn();
      actions();
      flage = true;
      break;

    case 3:
      break;

    default:
      std::cout << "incorrect value\n";
    }
  }
}

InterfaseTable::InterfaseTable() : count(0) {
  int a;
  bool flage = true;
  while (flage) {
      while (true) {
          std::cout
              << "Select the table type\n0 - TableVector\n1 - TableAVL\n2 - TableHash"
              << std::endl;
          std::cin >> a;
          if (std::cin.fail()) {
              std::cout << "Error: Invalid input!" << std::endl;
              std::cin.clear();
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          }
          else
              break;
      }
    switch (a) {
    case 0:
      _table = new TableVector<Polynomial>();
      flage = false;
      break;
    case 1:
      _table = new TableAVL<Polynomial>();
      flage = false;
      break;
    case 2:
      _table = new TableHash<Polynomial>();
      flage = false;
      break;
    default:
      std::cout << "Erorr" << std::endl;
      break;
    }
  }
}

InterfaseTable::~InterfaseTable() { delete _table; }

void InterfaseTable::choice() {

  int option;
  bool running = true;

  while (running) {
      while (true) {
          std::cout << "1 - Insert data" << std::endl;
          std::cout << "2 - Find data" << std::endl;
          std::cout << "3 - Remove data" << std::endl;
          std::cout << "4 - Show operations count" << std::endl;
          std::cout << "5 - Working with polynomials" << std::endl;
          std::cout << "0 - Exit" << std::endl;
          std::cin >> option;
          if (std::cin.fail()) {
              std::cout << "Error: Invalid input!" << std::endl;
              std::cin.clear();
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          }
          else
              break;
      }
    switch (option) {
    case 1:
      inputData();
      break;
    case 2:
      findData();
      break;
    case 3:
      removeData();
      break;
    case 4:
      showOperations();
      break;
    case 5:
      workingWithPolynomials();
      break;
    case 0:
      running = false;
      break;
    default:
      std::cout << "Erorr" << std::endl;
      break;
    }
  }
}

void InterfaseTable::inputData(const Polynomial &result) {
  std::string key;
  bool flage = true;
  int a;
  while (flage) {
      while (true) {
          std::cout << "Do you want to enter your key?\n1 - Yes\n2 - No" << std::endl;
          std::cin >> a;
          if (std::cin.fail()) {
              std::cout << "Error: Invalid input!" << std::endl;
              std::cin.clear();
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          }
          else
              break;
      }
    switch (a) {
    case 1:
      std::cout << "Enter key: ";
      std::cin >> key;
      flage = false;
      break;
    case 2:
      key = std::to_string(count);
      flage = false;
      break;
    default:
      std::cout << "Erorr" << std::endl;
      break;
    }
  }

  std::cout << "Enter value: ";
  Polynomial val;
  if (result == Polynomial()) {
    val.record();
  } else
    val = result;

  _table->insert(key, val);
  std::cout << "Inserted: " << key << " = " << val << std::endl;
  count++;
}

Polynomial *InterfaseTable::findData() {
  std::string key;

  std::cout << "Enter key to find: ";
  std::cin >> key;
  Polynomial *value = _table->find(key);

  if (value != nullptr) {
    std::cout << "Found: " << key << " = " << *value << std::endl;
    return value;
  }

  else
    std::cout << "Key not found" << std::endl;
  return nullptr;
}

void InterfaseTable::removeData() {
  std::string key;

  std::cout << "Enter key to remove: ";
  std::cin >> key;

  _table->remove(key);
  std::cout << "Removed: " << key << std::endl;
}

int InterfaseTable::showOperations() {
  std::cout << _table->getCountOper() << std::endl;
  return _table->getCountOper();
}

Polynomial *InterfaseTable::getPolynomial(const std::string &key) {
  return _table->find(key);
}

void InterfaseTable::workingWithPolynomials() {
  Polynomial *Pol1, *Pol2;
  Pol1 = findData();
  Pol2 = findData();
  if (Pol1 == nullptr || Pol2 == nullptr) {
    std::cout << "Erorr" << std::endl;
    return;
  }
  bool flage = true;
  int a;
  Polynomial rez;
  while (flage) {

      while (true) {
          std::cout << "What to do with polynomials?\n1 - Pol1 + Pol2\n2 - Pol1 - "
              "Pol2\n3 - Pol1 * Pol2\n4 - Pol2 + Pol1\n5 - Pol2 - Pol1\n0 - "
              "Exit\nEnter the number indicating the action: ";
          std::cin >> a;
          if (std::cin.fail()) {
              std::cout << "Error: Invalid input!" << std::endl;
              std::cin.clear();
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          }
          else
              break;
      }

    switch (a) {
    case 1:
      rez = *Pol1 + *Pol2;
      flage = false;
      break;

    case 2:
      rez = *Pol1 - *Pol2;
      flage = false;
      break;

    case 3:
      rez = *Pol1 * *Pol2;
      flage = false;
      break;

    case 4:
      rez = *Pol1 + *Pol2;
      flage = false;
      break;

    case 5:
      rez = *Pol2 - *Pol1;
      flage = false;
      break;

    case 0:
      std::cout << "\nGoodbye!";
      return;

    default:
      std::cout << "\nincorrect value\n";
    }
  }
  inputData(rez);
}