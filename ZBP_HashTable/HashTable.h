#pragma once
#include <iostream>

template <typename T, typename Fun>
class HashTable
{
public:
	HashTable(void)
	{

	}

	HashTable(Fun fun)
	{
		this->hash_function = fun;
		this->table_size = 8;
		this->size = 0;
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
			if(index >= myTable.getCapacity()) return 0;
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

			if(this->hash_table[index].state != 't')
			{
				iterator it(*this);
				it.setIndex(index);
				this->hash_table[index].value = value;
				this->hash_table[index].state = 't';
				this->size++;

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
			this->size--;
		}
	}

	size_t getCapacity()
	{
		return this->table_size;
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

	void resize()
	{
		//this->hash_table = new field[16];
	}

private:
	int index, size, table_size;
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
	//void resize();
};