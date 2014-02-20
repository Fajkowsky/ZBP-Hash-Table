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
		fun("asd");
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

		table[id].value = val;

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
		it.setIndex(MAXID);
		return it;
	}


private:
	int index;
	struct field {
		field()
		{
			state = 'e';
		}
		unsigned char state;
		T value;
	};
	field hash_table[2];
	//void resize();
};