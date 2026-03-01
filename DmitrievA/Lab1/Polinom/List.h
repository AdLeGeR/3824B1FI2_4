#pragma once


template <typename T>
struct Node {
	T data;
	Node* next;
	Node* prev;
	Node(T data) {
		this->data = data;
		this->next = nullptr;
		this->prev = nullptr;
	}
};

template <typename T>
class Iterator {
	Node<T>* current;
public:
	Iterator(Node<T>* node) {
		current = node;
	}
	T operator*() {
		return current->data;
	}
	Iterator& operator++(int) {
		Iterator& temp = *this;
		current = current->next;
		return temp;
	}
	Iterator& operator++() {
		Iterator& temp = *this;
		current = current->next;
		return temp;
	}
	bool operator != (const Iterator& other) {
		return current != other.current;
	}
	T* operator->() {
		return &current->data;
	}
};

template <typename T>
class List {
	friend class Iterator<T>;
	Node<T>* first = nullptr;
	Node<T>* last = nullptr;
	size_t size = 0;
	
public:
	typedef Iterator<T> iterator;
	typedef Iterator<const T> const_iterator;
	List() {}
	void push_back(T data) {
		Node<T>* newNode = new Node<T>(data);
		if(size == 0) {
			first = newNode;
			last = newNode;
		}
		else {
			last->next = newNode;
			newNode->prev = last;
			last = newNode;
		}
		size++;
	}
	void insert(iterator it, T data) {
		Node<T>* newNode = new Node<T>(data);
		if(it == iterator(first)) {
			newNode->next = node;
			node->prev = newNode;
			first = newNode;
		}
		else if(it == nullptr) {
			last->next = newNode;
			newNode->prev = last;
			last = newNode;
		}
		else {
			newNode->next = node;
			newNode->prev = node->prev;
			node->prev->next = newNode;
			node->prev = newNode;
		}
		size++;
	}
	void erase(iterator it) {
		Node<T>* node = it.current;
		if(node == first) {
			first = node->next;
			if(first) first->prev = nullptr;
		}
		else if(node == last) {
			last = node->prev;
			if(last) last->next = nullptr;
		}
		else {
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}
		delete node;
		size--;
	}
	iterator begin() {
		return Iterator<T>(first);
	}
	iterator end() {
		return Iterator<T>(nullptr);
	}
	const_iterator begin() const {
		return const_iterator(first);
	}
	const_iterator end() const {
		return const_iterator(nullptr);
	}
	void sort() {
		sort_(begin(), size);
		
	}
private:
	void sort_(iterator iter, size_t len) {
		if (len == 1)
			return;
		auto middle_it = iter;
		for (size_t i = 0; i < len / 2; i++) middle_it++;
		sort_(iter, len / 2);
		sort_(middle_it, len - len / 2);
		size_t m_ind = 0;
		for (size_t i = 0; (i < len - 1) && (len / 2 + m_ind < len); i++) {
			if (*middle_it < *iter) {
				auto temp = *middle_it;
				*middle_it = *iter;
				*iter = temp;
				middle_it++;
				m_ind++;
			}
			iter++;
		}
	}
};
