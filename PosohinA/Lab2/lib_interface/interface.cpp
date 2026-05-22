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

InterfaseTable::InterfaseTable() : count1(0), totInstV(0), totInstA(0), totInstH(0), totFindV(0), totFindA(0), totFindH(0), totRmV(0), totRmA(0), totRmH(0) {
    _table1 = new TableVector<Polynomial>();
    _table2 = new TableAVL<Polynomial>();
    _table3 = new TableHash<Polynomial>();
}

InterfaseTable::~InterfaseTable() 
{
    std::ofstream logFile("C:/Git Hab/Lab/3824B1FI2_4/PosohinA/Lab2/log.txt", std::ios::app);

    logFile << "Вставка: Vector - " << totInstV << ", AVL - " << totInstA << ", Hash - " << totInstH << "\n";
    logFile << "Поиск: Vector - " << totFindV << ", AVL - " << totFindA << ", Hash - " << totFindH << "\n";
    logFile << "Удаление: Vector - " << totRmV<< ", AVL - " << totRmA<< ", Hash - " << totRmH << "\n\n";

    logFile << "Всего:\n";
    logFile << "TableVector - " << totInstV + totFindV + totRmV << "\n";
    logFile << "TableAVL - " << totInstA + totFindA + totRmA << "\n";
    logFile << "TableHash - " << totInstH + totFindH + totRmH << "\n";

    logFile.close();

    delete _table1;
    delete _table2; 
    delete _table3;
}

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

void InterfaseTable::inputData(const Polynomial& result) {
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
            key = std::to_string(count1);
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
    }
    else
        val = result;

    int tmp = _table1->getCountOper();
    _table1->insert(key, val);
    int opsVector = _table1->getCountOper() - tmp;

    tmp = _table2->getCountOper();
    _table2->insert(key, val);
    int opsAVL = _table2->getCountOper() - tmp;

    tmp = _table3->getCountOper();
    _table3->insert(key, val);
    int opsHash = _table3->getCountOper() - tmp;

    totInstV += opsVector;
    totInstA += opsAVL;
    totInstH += opsHash;

    std::ofstream logFile("log.txt", std::ios::app);
    logFile << "Вставка " << key << ":\n"<< "Vector - " << opsVector << "AVL - " << opsAVL<< "Hash - " << opsHash<< std::endl;
    logFile.close();

    std::cout << "Inserted: " << key << " = " << val << std::endl;
    count1++;
}

Polynomial* InterfaseTable::findData() {
    std::string key;

    std::cout << "Enter key to find: ";
    std::cin >> key;
    int tmp = _table1->getCountOper();
    Polynomial* value = _table1->find(key);
    int opsVector = _table1->getCountOper() - tmp;

    tmp = _table2->getCountOper();
    _table2->find(key);
    int opsAVL = _table2->getCountOper() - tmp;

    tmp = _table3->getCountOper();
    _table3->find(key);
    int opsHash = _table3->getCountOper() - tmp;

    totFindV += opsVector;
    totFindA += opsAVL;
    totFindH += opsHash;

    std::ofstream logFile("log.txt", std::ios::app);
    logFile << "Поиск  " << key << ":\n"<< "Vector - " << opsVector<< "AVL - " << opsAVL<< "Hash - " << opsHash<< std::endl;
    logFile.close();

    if (value != nullptr) {
        std::cout << "Found: " << key << " = " << *value << std::endl;
        return value;
    }
    std::cout << "Key not found" << std::endl;
    return nullptr;
}

void InterfaseTable::removeData() {
    std::string key;

    std::cout << "Enter key to remove: ";
    std::cin >> key;

    int tmp = _table1->getCountOper();
    _table1->remove(key);
    int opsVector = _table1->getCountOper() - tmp;

    tmp = _table2->getCountOper();
    _table2->remove(key);
    int opsAVL = _table2->getCountOper() - tmp;

    tmp = _table3->getCountOper();
    _table3->remove(key);
    int opsHash = _table3->getCountOper() - tmp;

    totRmV += opsVector;
    totRmA += opsAVL;
    totRmH += opsHash;

    std::ofstream logFile("log.txt", std::ios::app);
    logFile << "Удаление " << key << ":\n"<< "Vector - " << opsVector<< "AVL - " << opsAVL<< "Hash - " << opsHash<< std::endl;
    logFile.close();

    std::cout << "Removed: " << key << std::endl;
}

int InterfaseTable::showOperations() {
    std::cout << "TableVector - " << _table1->getCountOper() << std::endl;
    std::cout << "TableAVL - " << _table2->getCountOper() << std::endl;
    std::cout << "TableHash - " << _table3->getCountOper() << std::endl;
    return _table1->getCountOper();
}

Polynomial* InterfaseTable::getPolynomial(const std::string& key) {
    return _table1->find(key);
}

void InterfaseTable::workingWithPolynomials() {
    Polynomial* Pol1, * Pol2;
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