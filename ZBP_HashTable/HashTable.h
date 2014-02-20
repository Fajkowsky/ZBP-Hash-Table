#pragma once

template <typename T>
class HashTable
{
public:
	HashTable(void);
	~HashTable(void);

	//std::pair<iterator,bool> insert(const T& value);
	//void erase( iterator pos );
	//iterator find(const T& key);
private:
	struct field {
		unsigned char state;
		T value;
	};
	field hash_table[2];
	//void resize();
};

