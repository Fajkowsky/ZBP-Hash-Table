#pragma once

template <typename T>
class HashTable
{
public:
	HashTable(void);
	~HashTable(void);
private:
	struct field {
		int state;
		T value;
	};
	field hash_table[2];
};

