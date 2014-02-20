#pragma once

template <typename T, typename Fun>
class HashTable
{
public:
	HashTable(void);
	~HashTable(void);
	void uzyj(Fun);

	//std::pair<iterator,bool> insert(const T& value);
	//void erase( iterator pos );
	//iterator find(const T& key);
	//iterator begin();
	//iterator end();
private:
	int index;
	struct field {
		unsigned char state;
		T value;
	};
	field hash_table[2];
	//void resize();
};

