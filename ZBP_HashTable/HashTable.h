#pragma once
#include <iostream>

struct hashClass {
public:
	int operator() (int value, bool step, int table_size) { 
		int index;
		index = value % table_size;

		if(step){
			index = (3 + (value % 3));
		}
		return (index);
	}

	int operator() (std::string value, bool step, int table_size) { 
		int b,index = 0;
		int a = 29;

		if(!step){
			for (unsigned int i = 0; i < value.length(); i++){
				index = (a * index + value[i]) % table_size;
			}
		}
		a = 31415;
		b = 27183;
		if(step){
			for (unsigned int i = 0; i < value.length(); i++){
				index = (a * index + value[i]) % table_size;
				a = (a * b) % (table_size - 1);
			}
			if ((index % 2) == 0){
				index++;
			}
		}

		return (index);
	}
} tmp;

template <typename T, typename Fun = hashClass>
class HashTable
{
public:
	HashTable(void)
	{
		this->hash_function = tmp;
		this->table_size = 8;
		this->taken = 0;
		this->hash_table = new field[this->table_size];
	}

	HashTable(Fun fun)
	{
		this->hash_function = fun;
		this->table_size = 8;
		this->taken = 0;
		this->hash_table = new field[this->table_size];
	}

	~HashTable(void)
	{

	}

	class iterator
	{
		friend class HashTable<T, Fun>;
		size_t index;
		HashTable<T, Fun> & myTable;

		void setIndex(size_t index)
		{
			this->index = index;
		}

	public:

		iterator(HashTable<T, Fun> & table) : myTable(table)
		{
			index = 0;
		}

		int operator==(const iterator & it)
		{
			if(index == it.index) return 1;
			else return 0;
		}

		iterator & operator++()
		{
			index += 1;
			return *this;
		}

		iterator operator++(int)
		{
			iterator it = *this;
			++*this;
			return it;
		}

		T & operator*()
		{
			return myTable.get(index);
		}

		operator int()
		{
			if(index >= myTable.size()) return 0;
			else return 1;
		}

		int getIndex()
		{
			return this->index;
		}
	};

	iterator insert(const T & value)
	{
		size_t key1 = this->hash_function(value, 0, this->table_size);
		size_t key2 = this->hash_function(value, 1, this->table_size);

		for(int i=0;i < table_size; i++)
		{
			this->index = (key1 + i*key2) % this->table_size;
			if(this->hash_table[index].value == value)
				break;

			if(this->hash_table[index].state != 't')
			{
				iterator it(*this);
				it.setIndex(index);

				this->hash_table[index].value = value;
				this->hash_table[index].state = 't';
				this->taken++;
				resize();

				return it;
			}
		}
		return this->end();
	}

	void erase( iterator pos )
	{
		if(pos != this->end())
		{
			this->hash_table[pos.getIndex()].state = 'd';
			this->taken--;
		}
	}

	int size()
	{
		return this->taken;
	}
	
	int count(const T & value)
	{
		if(this->find(value) == this->end())
			return 0;
		return 1;
	}

	size_t max_size()
	{
		return this->table_size;
	}

	void clear()
	{
		for(int i=0; i<this->table_size; i++)
			this->hash_table[i].state = 'e';
		this->taken = 0;
	}

	iterator find(const T& value)
	{
		size_t key1 = this->hash_function(value, 0, this->table_size);
		size_t key2 = this->hash_function(value, 1, this->table_size);

		for(int i=0;i < table_size; i++)
		{
			index = (key1 + i*key2) % this->table_size;

			if(hash_table[index].value == value)
			{
				iterator it(*this);
				it.setIndex(index);

				return it;
			}
			else if(hash_table[index].state == 'e')
				return this->end();
		}
		return this->end();
	}

	T& operator[] (const int index)
	{
		return this->hash_table[index].value;
	}

	iterator begin()
	{
		iterator it(*this);
		it.setIndex(0);
		return it;
	}

	iterator end()
	{
		iterator it(*this);
		it.setIndex(table_size);
		return it;
	}

private:

	int index, table_size, taken;

	struct field {
		field()
		{
			state = 'e';
		}
		unsigned char state;  // e = empty; d = deleted; t = taken
		T value;
	};

	T & get(int index)
	{
		return hash_table[index].value;
	}

	field* hash_table;
	Fun hash_function;

	void resize()
	{
		float full = (float)this->taken / (float)this->table_size;

		if (full > 0.7) {

			int old_size = this->table_size;
			field* tmp_hash_table = new field[old_size];
			std::memcpy(tmp_hash_table, this->hash_table, old_size * sizeof(field));
			
			this->taken = 0;
			delete[] this->hash_table;
			this->table_size = old_size * 2;
			this->hash_table = new field[this->table_size];

			for (int i = 0; i < old_size; i++){
				if (tmp_hash_table[i].state == 't'){
					this->insert(tmp_hash_table[i].value);
				}
			}

		}
	}
};