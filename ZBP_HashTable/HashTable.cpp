#include <iostream>
#include "HashTable.h"

template <typename T>
HashTable<T>::HashTable(void)
{
}

template <typename T>
HashTable<T>::~HashTable(void)
{
}



template class HashTable<int>;
template class HashTable<std::string>;