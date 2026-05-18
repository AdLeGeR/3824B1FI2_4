#include"../lib_list/list.h"

Node::Node(const std::pair<double, int>& val, Node* next) : _val(val), _next(next) {}


List::Iterator::Iterator() : _current(nullptr) {}

List::Iterator::Iterator(Node* poc) : _current(poc) {}

List::Iterator::Iterator(const Iterator& A) : _current(A._current) {}


typename List::Iterator& List::Iterator::operator =(const Iterator& A) {
	if (this != &A)
		_current = A._current;
	return (*this);
}


std::pair<double, int>& List::Iterator::operator*() {
	return _current->_val;
}


bool List::Iterator::operator != (const Iterator& A) {
	return _current != A._current;
}


bool List::Iterator::operator == (const Iterator& A) {
	return _current == A._current;
}


typename List::Iterator List::Iterator::operator ++(int) {
	Iterator tmp(*this);
	_current = _current->_next;
	return tmp;
}


typename List::Iterator List::Iterator::operator ++() {
	_current = _current->_next;
	return (*this);
}

Node* List::Iterator::get_current() { return _current; }


int sum_numb(int a) {
	int sum = 0;
	while (a != 0) {
		sum += a % 10;
		a /= 10;
	}
	return sum;
}


List::List() : _head(nullptr), _tail(nullptr) {}


List::List(const List& A) {
	_head = nullptr;
	_tail = nullptr;
	Node* tmp = A._head;
	while (tmp != nullptr) {
		push_back(tmp->_val);
		tmp = tmp->_next;
	}
}


List::~List() { clear(); }


void List::clear() noexcept {
	while (!is_empty()) {
		Node* tmp = _head;
		_head = _head->_next;
		delete tmp;
	}
}


bool List::is_empty() {
	return _head == nullptr;
}


void List::pop_front() {
	if (is_empty())
		throw std::logic_error("list is empty");
	Node* tmp = _head;
	_head = _head->_next;

	if (is_empty()) {
		_tail = nullptr;
	}
	delete tmp;
}


void List::push_front(const std::pair<double, int>& val) noexcept {
	Node* A = new Node(val, _head);
	if (is_empty())
		_tail = A;
	_head = A;
}


void List::pop_back() {
	if (is_empty())
		throw std::logic_error("list is empty");
	Node* tmp = _head;

	if (_head == _tail) {
		_head = nullptr;
		_tail = nullptr;
	}
	else {
		while (tmp->_next != _tail)
			tmp = tmp->_next;

		_tail = tmp;
		tmp = tmp->_next;
		_tail->_next = nullptr;
	}
	delete tmp;
}


void List::push_back(const std::pair<double, int>& val) noexcept {
	Node* A = new Node(val, nullptr);
	if (is_empty())
		_head = A;

	else
		_tail->_next = A;
	_tail = A;
}


void List::insert(Node* A, const std::pair<double, int>& val) {
	if (is_empty())
		throw std::logic_error("list is empty");
	if (A == nullptr)
		throw std::logic_error("A = nullptr");
	if (A == _tail)
		push_back(val);
	else {
		Node* B = new Node(val, A->_next);
		A->_next = B;
	}
}

List& List::operator = (const List& A) {
	if (this == &A)
		return (*this);
	clear();
	for (auto it = A.begin(); it != A.end(); it++) 
		push_back(*it);
	return (*this);
}