

template<typename T>
class UnorderedTable {
	size_t size;
	struct record {
		string key;
		T data;
	};
	vector<record> table;
public:
	UnorderedTable() : size(0) {}
	void insert(const string& key, const T& data) {
		for (size_t i = 0; i < size; ++i) {
			if (table[i].key == key) {
				table[i].data = data;
				return;
			}
		}
		table.push_back({ key, data });
		++size;
	}
	T* find(const string& key) {
		for (size_t i = 0; i < size; ++i) {
			if (table[i].key == key) {
				return &table[i].data;
			}
		}
		return nullptr;
	}
	void remove(const string& key) {
		for (size_t i = 0; i < size; ++i) {
			if (table[i].key == key) {
				table.erase(table.begin() + i);
				--size;
				return;
			}
		}
	}
};