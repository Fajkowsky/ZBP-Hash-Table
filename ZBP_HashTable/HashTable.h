#pragma once

template <typename T, typename Fun>
class HashTable
{
public:
	HashTable(void)
	{
		this->index = 0;
	}
	HashTable(Fun fun)
	{
		this->hash_function = fun;
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

	};

	iterator insert(const T & val)
	{
		size_t id = getNextIndex(val); 

		iterator it(*this);
		it.setIndex(id);

		hash_table[id].value = val;
		hash_table[id].state = 't';

		return it;
	}
	//void erase( iterator pos );
	//iterator find(const T& key);
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
	
	size_t getNextIndex(const T & val)
	{
		return index++;
	}

private:
	int index, table_size;
	struct field {
		field()
		{
			state = 'e';
		}
		unsigned char state;
		T value;
	};
	field hash_table[2];
	Fun hash_function;
	//void resize();
};