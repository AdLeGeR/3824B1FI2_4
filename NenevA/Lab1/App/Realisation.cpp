#include "Header.h"

//iterator
my_list::iterator::iterator(Node* ptr) : current_node(ptr) {}
Monomial& my_list::iterator::operator*() const { return current_node->Elem; }

Monomial* my_list::iterator::operator->() const { return &(current_node->Elem); }
my_list::iterator& my_list::iterator::operator++() {
    if (current_node) current_node = current_node->next;
    return *this;
}
bool my_list::iterator::operator==(const iterator& other) const { return current_node == other.current_node; }
bool my_list::iterator::operator!=(const iterator& other) const { return current_node != other.current_node; }





//const_iterator
my_list::const_iterator::const_iterator(const Node* ptr) : current_node(ptr) {}
const Monomial& my_list::const_iterator::operator*() const { return current_node->Elem; }
const Monomial* my_list::const_iterator::operator->() const { return &(current_node->Elem); }
my_list::const_iterator& my_list::const_iterator::operator++() {
    if (current_node) current_node = current_node->next;
    return *this;
}

bool my_list::const_iterator::operator==(const const_iterator& other) const { return current_node == other.current_node; }

bool my_list::const_iterator::operator!=(const const_iterator& other) const { return current_node != other.current_node; }





//my_list
my_list::my_list() : head(nullptr), tail(nullptr), _size(0) {};
my_list::~my_list() { clear(); }

my_list::my_list(const my_list& other) : head(nullptr), tail(nullptr), _size(0) {
    for (const Monomial& m : other) emplace_back(m);
}

my_list& my_list::operator=(my_list other) {
    swap(head, other.head);
    swap(tail, other.tail);
    swap(_size, other._size);
    return *this;
}
bool my_list::empty() const { return head == nullptr; }
size_t my_list::size() const { return _size; }
void my_list::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* next_node = current->next;
        delete current;
        current = next_node;
    }
    head = nullptr;
    tail = nullptr;
    _size = 0;
}
void my_list::emplace_back(Monomial M) {
    Node* p = new Node(M);
    if (empty()) {
        head = p;
        tail = p;
    }
    else {
        tail->next = p;
        tail = p;
    }
    _size++;
}
void my_list::emplace_back(double c, int d) {
    emplace_back(Monomial(c, d));
}

void my_list::sort() {
    if (empty() || head == tail) return;
    vector<Monomial> temp_vec;
    for (const Monomial& m : *this) temp_vec.emplace_back(m);

    std::sort(temp_vec.begin(), temp_vec.end());
    clear();
    for (const Monomial& m : temp_vec) emplace_back(m);
}

my_list::iterator my_list::begin() { return iterator(head); }
my_list::iterator my_list::end() { return iterator(nullptr); }

my_list::const_iterator my_list::begin() const { return const_iterator(head); }
my_list::const_iterator my_list::end() const { return const_iterator(nullptr); }





//polinomial
void Polinomial::simplify() {
    if (Data.empty()) return;
    Data.sort();
    my_list newData;
    auto it = Data.begin();
    while (it != Data.end()) {
        double currentCoeff = it->Coefficient;
        int currentDegree = it->Degrees;
        ++it;
        while (it != Data.end() && it->Degrees == currentDegree) {
            currentCoeff += it->Coefficient;
            ++it;
        }
        if (fabs(currentCoeff) > 0.000001) {
            newData.emplace_back(currentCoeff, currentDegree);
        }
    }
    Data = newData;
}

Polinomial::Polinomial(const Polinomial& other) {
    for (auto it = other.Data.begin(); it != other.Data.end(); ++it) Data.emplace_back(*it);
}

Polinomial::Polinomial(const string s) {
    istringstream iss(s);
    double coeff;
    int degree;
    vector<Monomial> tempMonomials;
    while (iss >> coeff >> degree) {
        if (degree > 999 || degree < 0) throw runtime_error("Such values of degrees are not supported");
        if (coeff) tempMonomials.emplace_back(coeff, degree);
    }

    if (!tempMonomials.empty()) {
        sort(tempMonomials.begin(), tempMonomials.end());
        if (!tempMonomials.empty()) {
            for (size_t i = 0; i < tempMonomials.size(); ++i) Data.emplace_back(tempMonomials[i]);
        }
    }
    simplify();
}

bool Polinomial::operator==(const Polinomial& other) const {
    if (Data.size() != other.Data.size()) return 0;
    auto it1 = Data.begin();
    auto it2 = other.Data.begin();
    while (it1 != Data.end()) {
        if (!(*it1 == *it2)) {
            return false;
        }
        ++it1;
        ++it2;
    }
    return 1;
}

bool Polinomial::operator!=(const Polinomial& other) const {
    return !(*this == other);
}

Polinomial& Polinomial:: operator=(const Polinomial& other) {
    if (*this == other) return *this;
    Polinomial temp(other);
    swap(Data, temp.Data);
    return *this;
}

Polinomial Polinomial::operator+(const Polinomial& other) const {
    Polinomial result;
    vector<Monomial> temp1, temp2;

    for (auto& it : this->Data) temp1.emplace_back(it);
    for (auto& it : other.Data) temp2.emplace_back(it);

    vector<Monomial> Res(temp1.size() + temp2.size());
    merge(temp1.begin(), temp1.end(), temp2.begin(), temp2.end(), Res.begin());

    for (auto& i : Res) result.Data.emplace_back(i);

    result.simplify();
    return result;
}

Polinomial Polinomial::operator-(const Polinomial& other) const {
    Polinomial M(other), result = *this;
    result = result + M * -1;
    return result;
}

Polinomial Polinomial::operator*(const Polinomial& other) const {
    Polinomial result;
    vector<Monomial> temp1, temp2, res;

    for (auto& elem : this->Data) temp1.emplace_back(elem);
    for (auto& elem : other.Data) temp2.emplace_back(elem);

    for (auto& elem1 : temp1) {
        for (auto& elem2 : temp2) {
            int X = elem1.Degrees / 100 + elem2.Degrees / 100;
            int Z = elem1.Degrees % 10 + elem2.Degrees % 10;
            int Y = (elem1.Degrees + elem2.Degrees - Z - 100 * X) / 10;
            if (X > 9 || Y > 9 || Z > 9) {
                //cout << X << " " << Y << " " << Z << " ";
                throw runtime_error("Degrees over 9 aren't allowed");
            }
            int NewDegree = Z + Y * 10 + 100 * X;
            double NewCoeff = elem1.Coefficient * elem2.Coefficient;
            res.emplace_back(NewCoeff, NewDegree);
        }
    }

    for (auto& elem : res) result.Data.emplace_back(elem);

    result.simplify();
    return result;
}

Polinomial Polinomial::operator*(const double Mult) {
    Polinomial result(*this);
    for (auto& elem : result.Data) elem.Coefficient *= Mult;
    return result;
}