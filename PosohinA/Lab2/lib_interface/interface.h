#ifndef INTERFACE_H
#define INTERFACE_H

#include <fstream>
#include "../lib_polynomial/polynomial.h"
#include "../lib_table/table_vector.h"
#include "../lib_table/table_AVL.h"
#include "../lib_table/table_hash.h"

class InterfacePol {
    Polynomial Pol1, Pol2;
public:
    InterfacePol();
    ~InterfacePol();
    Polynomial sum() const;
    Polynomial sub() const;
    Polynomial mul() const;
    Polynomial sum2() const;
    Polynomial sub2() const;
    void input_polyn();
    void actions();
};

class InterfaseTable {
    Table<Polynomial>* _table1, *_table2, *_table3;
    int count1;
    
    int totInstV, totInstA, totInstH;
    int totFindV, totFindA, totFindH;
    int totRmV, totRmA, totRmH;

public:
    InterfaseTable();
    ~InterfaseTable();
    void choice();
    void inputData(const Polynomial &result = Polynomial());
    Polynomial *findData();
    void removeData();
    int showOperations();
    Polynomial* getPolynomial(const std::string& key);
    void workingWithPolynomials();
};
#endif // !INTERFACE_INTERFASE_H