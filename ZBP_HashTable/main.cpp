#include <iostream>
#include "HashTable.h"
#include <string>
#include <stdlib.h>
#include <ctime>
#include <set>
#include <unordered_set>
#include <vector>
#include <fstream>

clock_t begin_time;
void start_timer(){ 
	begin_time = clock();
}
double get_time(){ 
	return double(clock() - begin_time) / CLOCKS_PER_SEC;
}

struct myclass {
	int operator() (int value, bool step, int table_size) { 
		int index;
		index = value % table_size;

		if(step){
			index = (3 + (value % 3));
		}
		return (index);
	}
};

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

myclass int_funktor;
myStringclass string_funktor;

HashTable<int, myclass> int_tablica(int_funktor);
HashTable<std::string, myStringclass> string_tablica(string_funktor);

std::set<int> int_set;
std::set<std::string> string_set;

std::unordered_set<int> int_uset;
std::unordered_set<std::string> string_uset;

std::vector<int> int_dane;
std::vector<std::string> string_dane;

int ile = 100000;



void generuj_dane(){
	std::cout << "Generuje inty" << std::endl;
	int k = 3;
	for(int i=0;i<ile;i++){
		int_dane.push_back(k*i);
		k += 11;
	}
	std::cout << "Generuje stringi" << std::endl;
	std::ifstream dict("polski.txt");
	std::string line;
	if(dict.is_open())
	{ 
		while (getline(dict, line))
		{ 
			string_dane.push_back(line);
		} 
	} 
	else 
		std::cout << "Cos jest nie tak z plikiem\n";
}

void wstawianie() {
	start_timer();
	for(int i=0;i<ile;i++)
		int_tablica.insert(int_dane[i]);
	std::cout << "Czas dla wstawiania " << int_tablica.size() << " rekordow int: " << get_time() <<std::endl;

	start_timer();
	for(int i=0;i<ile;i++)
		int_set.insert(int_dane[i]);
	std::cout << "Czas dla wstawiania set " << int_set.size() << " rekordow int: " << get_time() <<std::endl;

	start_timer();
	for(int i=0;i<ile;i++)
		int_uset.insert(int_dane[i]);
	std::cout << "Czas dla wstawiania uset " << int_uset.size() << " rekordow int: " << get_time() <<std::endl;

	start_timer();
	for(int i=0;i<string_dane.size();i++)
		string_tablica.insert(string_dane[i]);
	std::cout << "Czas dla wstawiania " << string_tablica.size() << " rekordow string: " << get_time() <<std::endl;

	start_timer();
	for(int i=0;i<string_dane.size();i++)
		string_set.insert(string_dane[i]);
	std::cout << "Czas dla wstawiania set " << string_set.size() << " rekordow string: " << get_time() <<std::endl;

	start_timer();
	for(int i=0;i<string_dane.size();i++)
		string_uset.insert(string_dane[i]);
	std::cout << "Czas dla wstawiania uset " << string_uset.size() << " rekordow string: " << get_time() <<std::endl;
}

void main(){
	setlocale(LC_ALL, "polish");

	generuj_dane();
	wstawianie();


	getchar();
}