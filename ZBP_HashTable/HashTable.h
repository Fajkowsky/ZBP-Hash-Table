#pragma once

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
		size_t key1 = this->hash_function(val, 0, this->table_size);
		size_t key2 = this->hash_function(val, 1, this->table_size);

		for(int i=0;i < table_size; i++)
		{
			index = (key1 + i*key2) % this->table_size;

			if(hash_table[index].state != 't')
			{
				iterator it(*this);
				it.setIndex(index);
				hash_table[index].value = val;
				hash_table[index].state = 't';

				return it;
			}
		}
		return this->end();
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
		unsigned char state;  // e = empty; f = free; t = taken
		T value;
	};
	field hash_table[8];
	Fun hash_function;
	//void resize();
};