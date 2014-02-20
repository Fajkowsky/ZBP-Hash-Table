#pragma once

template <typename T, typename Fun>
class HashTable
{
public:
	HashTable(void);
	HashTable(Fun);
	~HashTable(void);

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

template <typename T, typename Fun>
HashTable<T, Fun>::HashTable(){

}

template <typename T, typename Fun>
HashTable<T, Fun>::HashTable(Fun fun){
	fun("asd");
}

template <typename T, typename Fun>
HashTable<T, Fun>::~HashTable(){

}