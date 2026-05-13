#pragma once

#include <iostream>
#include <algorithm>

class Polynom;
class List;

// ------------------------------ NODE -----------------------------------------

class Node {
private:
    friend class Polynom;
    friend class List;
    bool can_multiply(const Node* b);
public:
    int power;
    double coeff;
    Node* next;
    Node* prev;
    Node(int pow, double co) : power(pow), coeff(co), next(nullptr), prev(nullptr) {}
    bool operator>(const Node& other) const;
    bool operator<(const Node& other) const;
    bool operator==(const Node& other) const;
};

bool Node::operator>(const Node& other) const {
    int a_degs[3] = { this->power / 100, (this->power / 10) % 10, this->power % 10 };
    int b_degs[3] = { other.power / 100, (other.power / 10) % 10, other.power % 10 };

    std::sort(a_degs, a_degs + 3, std::greater<int>());
    std::sort(b_degs, b_degs + 3, std::greater<int>());

    for (int i = 0; i < 3; ++i) {
        if (a_degs[i] != b_degs[i]) return a_degs[i] > b_degs[i];
    }
    return this->power > other.power;
}

bool Node:: operator==(const Node& other) const {
    return this->power == other.power;
}

bool Node::operator<(const Node& other) const {
    return (!(*this > other) && !(*this == other));
}

bool Node::can_multiply(const Node* b) {
    int px = this->power / 100 + b->power / 100;;
    if (px > 9) return false;
    int py = this->power / 10 % 10 + b->power / 10 % 10;
    if (py > 9) return false;
    int pz = this->power % 10 + b->power % 10;
    if (pz > 9) return false;
    return true;
}



// ------------------------------ LIST -----------------------------------------


class List {
    friend class Polynom;
public:
    Node* head;
    Node* tail;
    List() : head(nullptr), tail(nullptr) {}
    List(const List& other);
    List& operator=(const List& other);
    void simple_push_back(double co, int pow);
    void push_back(double co, int pow);
    void print();
    void deleteNode(Node* node);
    ~List();
};

List::List(const List& other) : head(nullptr), tail(nullptr) {
    Node* curr = other.head;
    while (curr) {
        this->simple_push_back(curr->coeff, curr->power);
        curr = curr->next;
    }
}

List& List::operator=(const List& other) {
    if (this == &other) return *this;

    Node* curr = head;
    while (curr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
    head = tail = nullptr;

    Node* temp = other.head;
    while (temp) {
        this->simple_push_back(temp->coeff, temp->power);
        temp = temp->next;
    }

    return *this;
}

void List::simple_push_back(double co, int pow) {
    Node* newNode = new Node(pow, co);
    if (!tail) {
        head = tail = newNode;
        return;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void List::push_back(double co, int pow) {
    Node* newNode = new Node(pow, co);
    if (!tail) {
        head = tail = newNode;
        return;
    }

    Node* monom = tail;
    while (monom != nullptr) {
        if (*monom > *newNode) {
            newNode->next = monom->next;
            if (monom->next != nullptr) monom->next->prev = newNode;
            monom->next = newNode;
            newNode->prev = monom;
            if (monom == tail) tail = newNode;
            return;
        }
        else {
            if (pow == monom->power) {
                monom->coeff += co;
                delete newNode;
                return;
            }
        }
        monom = monom->prev;
    }
    newNode->next = head;
    head->prev = newNode;
    head = newNode;

}

void List::print() {
    Node* curr = head;
    while (curr) {
        std::cout << curr->coeff << " " << curr->power << " , ";
        curr = curr->next;
    }
}

void List::deleteNode(Node* node) {
    if (!node) return;
    if (node->prev) node->prev->next = node->next;
    else head = node->next;

    if (node->next) node->next->prev = node->prev;
    else tail = node->prev;

    delete node;
}

List::~List() {
    Node* curr = head;
    while (curr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
}