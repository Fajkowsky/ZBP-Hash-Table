#include <iostream>
#include "HashTable.h"
#include <string>

void main(){

	struct myclass {
	public:
		int operator() (int value, bool step, int table_size) { 
			int index;
			index = value % table_size;

			if(step){
				index = (3 + (value % 3));
			}
			return (index);
		}
	} myInt;

	struct myStringclass {
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
			}

			return (index);
		}
	};

//	HashTable<int> tablica(myInt);
	
	
	std::cout << "Test";
	getchar();
}