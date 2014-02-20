#include <iostream>
#include "HashTable.h"

template <typename T, typename Fun>
HashTable<T, Fun>::HashTable(void)
{
} 

/*
template <typename T, typename Fun>
HashTable<T, Fun>::HashTable(Fun fun)
{
	index = fun(1,false,10);
}*/

template <typename T, typename Fun>
void HashTable<T, Fun>::uzyj(Fun fun){
	fun("asd");
}

template <typename T, typename Fun>
HashTable<T, Fun>::~HashTable(void)
{
}



//template class HashTable<int>;
//template class HashTable<std::string>;
