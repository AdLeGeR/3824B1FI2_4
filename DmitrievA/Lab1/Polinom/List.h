#pragma once

template <typename T>
class List;


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

template <typename T, typename Ptr=T*, typename Ref=T& >
class Iterator {
	friend List<T>;
	Node<T>* current = nullptr;
public:
	Iterator() {}
	Iterator(Node<T>* node) {
		current = node;
	}
	Ref operator*() {
		return current->data;
	}
	Iterator operator++(int) {
		Iterator temp = *this;
		current = current->next;
		return temp;
	}
	Iterator& operator++() {
		current = current->next;
		return *this;
	}
	bool operator != (const Iterator& other) const {
		return current != other.current;
	}
	bool operator == (const Iterator& other) const {
		return current == other.current;
	}
	Ptr operator->() {
		return &(current->data);
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
	typedef Iterator<T, const T*, const T&> const_iterator;
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
		if (size == 0) {
			push_back(data);
		}
		else if(it == iterator(first)) {
			newNode->next = first;
			first->prev = newNode;
			first = newNode;
		}
		else if(it == nullptr) {
			last->next = newNode;
			newNode->prev = last;
			last = newNode;
		}
		else {
			
			newNode->next = it.current;
			newNode->prev = it.current->prev;
			it.current->prev->next = newNode;
			it.current->prev = newNode;
		}
		size++;
	}
	void erase(iterator it) {
		Node<T>* node = it.current;
		if(node == nullptr) {
			throw "Can't erase end() iterator";
		}
		else if(node == first) {
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
	iterator begin() const {
		return iterator(first);
	}
	iterator end() const {
		return iterator(nullptr);
	}
	const_iterator cbegin() const {
		return const_iterator(first);
	}
	const_iterator cend() const {
		return const_iterator(nullptr);
	}

	
	void sort() {
		sort_(begin(), size, std::less<T>{});

	}

	template <typename Compare>
	void sort(Compare comp = std::less<T>{}) {
		sort_(begin(), size, comp);
		
	}
	size_t getSize() const {
		return size;
	}
	~List() {
		if (size == 0) return;
		if (size == 1) { delete first; return; };
		for (Node<T>* n = first; n != last;) {
			Node<T>* temp = n->next;
			delete n;
			n = temp;
		}
		delete last;
	}
private:
	template <typename Compare>
	iterator sort_(iterator iter, size_t len, Compare comp) {
		if (len <= 1)
			return iter;
		iterator middle_it = iter;
		for (size_t i = 0; i < len / 2; i++) middle_it++;
		iter = sort_(iter, len / 2, comp);
		middle_it = sort_(middle_it, len - (len / 2), comp);
		size_t m_ind = 0;
		size_t i = 0;
		iterator start = iter;
		for (; (iter != middle_it) && (len / 2 + m_ind < len);) {
			if (comp(*middle_it, *iter)) {
				Node<T>* middle_node = middle_it.current;
				Node<T>* iter_node = iter.current;
				// увеличение итератора и индекса
				middle_it++;
				m_ind++;
				// склейка предыдущего и следующего узла для middle_node
				if (middle_node->next != nullptr) middle_node->next->prev = middle_node->prev;
				else last = middle_node->prev;
				middle_node->prev->next = middle_node->next;
				//вставка middle_node перед iter_node
				middle_node->next = iter_node;
				middle_node->prev = iter_node->prev;
				if(iter_node->prev != nullptr) iter_node->prev->next = middle_node;
				else first = middle_node;
				iter_node->prev = middle_node;
				// если мы вставили в начало, то обновляем start
				if (i == 0) {
					start = iterator(middle_node);
				}
			}
			else {
				iter++;
			}
			i++;
		}
		return start;
	}
};
