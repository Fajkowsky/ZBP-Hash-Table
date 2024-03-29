﻿#include <iostream>
#include "HashTable.h"
#include <string>
#include <stdlib.h>
#include <ctime>
#include <set>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <algorithm>

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
			int q = 4007;
			int p = 94583;
			index = ((q * value) % p);

			if ((index % 2) == 0){
				index++;
			}
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
			if ((index % 2) == 0){
				index++;
			}
		}

		return (index);
	}
};

myclass int_funktor;
myStringclass string_funktor;

HashTable<int, myclass> int_tablica(int_funktor);
HashTable<std::string> string_tablica;

std::set<int> int_set;
std::set<std::string> string_set;

std::unordered_set<int> int_uset;
std::unordered_set<std::string> string_uset;

std::vector<int> int_dane;
std::vector<std::string> string_dane;

int ile = 100000;



void generuj_dane(){
	std::cout << "Generuje inty" << std::endl;
	int k = 6;
	start_timer();
	for(int i=0;i<ile;i++){
		int_dane.push_back(k*i);
	}
	std::random_shuffle ( int_dane.begin(), int_dane.end() );
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

void szukanie(){
	std::random_shuffle ( int_dane.begin(), int_dane.end() );
	double elementy = 0.0;
	std::vector<int>::iterator it;
	std::vector<std::string>::iterator string_it;

	start_timer();
	for(it=int_dane.begin(); it!=int_dane.end(); ++it)
	{
		elementy++;
		int_tablica.find(*it);
	}
	std::cout << "Szukanie int dla hash_table: " << get_time()/elementy << " " << elementy << std::endl;

	elementy = 0.0;
	start_timer();
	for(it=int_dane.begin(); it!=int_dane.end(); ++it)
	{
		elementy++;
		int_set.find(*it);
	}
	std::cout << "Szukanie int dla set: " << get_time()/elementy << " " << elementy << std::endl;

	elementy = 0.0;
	start_timer();
	for(it=int_dane.begin(); it!=int_dane.end(); ++it)
	{
		elementy++;
		int_uset.find(*it);
	}
	std::cout << "Szukanie int dla uset: " << get_time()/elementy << " " << elementy << std::endl;

	elementy = 0.0;
	start_timer();
	for(string_it=string_dane.begin(); string_it!=string_dane.end(); ++string_it)
	{
		elementy++;
		string_tablica.find(*string_it);
	}
	std::cout << "Szukanie string dla hash_table: " << get_time()/elementy << " " << elementy << std::endl;

	elementy = 0.0;
	start_timer();
	for(string_it=string_dane.begin(); string_it!=string_dane.end(); ++string_it)
	{
		elementy++;
		string_set.find(*string_it);
	}
	std::cout << "Szukanie string dla set: " << get_time()/elementy << " " << elementy << std::endl;

	elementy = 0.0;
	start_timer();
	for(string_it=string_dane.begin(); string_it!=string_dane.end(); ++string_it)
	{
		elementy++;
		string_uset.find(*string_it);
	}
	std::cout << "Szukanie string dla uset: " << get_time()/elementy << " " << elementy << std::endl;
}

void wypelnienie(){
	double searches[] = {0.05, 0.1, 0.2, 0.4, 0.7};
	int int_size = int_dane.size();
	int j=0, number_of_elements =0, warunek;
	std::vector<int>::iterator it;
	std::vector<int> search;
	for(int i=0; i<5; i++){
		std::cout << "----- Zapenienie: " << searches[i] << " -----" << std::endl; 
		int_set.clear();
		int_uset.clear();
		int_tablica.clear();
		search.clear();
		warunek = (int)int_size*searches[i];
		for(it=int_dane.begin(); it != int_dane.end(); it++){
			int_set.insert(*it);
			int_uset.insert(*it);
			int_tablica.insert(*it);
			search.push_back(*it);
			
			if(j >= warunek){
				break;
			}
			j++;
		}
		
		std::random_shuffle(search.begin(), search.end());

		number_of_elements = 0;
		start_timer();
		for(it=search.begin(); it != search.end(); it++){
			number_of_elements++;
			int_tablica.find(*it);
		}
		std::cout << "Wyszukiwanie dla int hash_table i zapelnienia: "<< warunek << " zajelo: " << get_time() << std::endl;

		number_of_elements = 0;
		start_timer();
		for(it=search.begin(); it != search.end(); it++){
			number_of_elements++;
			int_set.find(*it);
		}
		std::cout << "Wyszukiwanie dla int set i zapelnienia: "<< warunek << " zajelo: " << get_time() << std::endl;

		number_of_elements = 0;
		start_timer();
		for(it=search.begin(); it != search.end(); it++){
			number_of_elements++;
			int_uset.find(*it);
		}
		std::cout << "Wyszukiwanie dla int uset i zapelnienia: "<< warunek << " zajelo: " << get_time() << std::endl;
	}
}

void wypelnienie_string(){
	double searches[] = {0.05, 0.1, 0.2, 0.4, 0.7};
	int int_size = string_dane.size();
	int j=0, number_of_elements =0, warunek;
	std::vector<std::string>::iterator it;
	std::vector<std::string> search;
	for(int i=0; i<5; i++){
		std::cout << "----- Zapenienie: " << searches[i] << " -----" << std::endl; 
		string_set.clear();
		string_uset.clear();
		string_tablica.clear();
		search.clear();
		warunek = (int)int_size*searches[i];
		for(it=string_dane.begin(); it != string_dane.end(); it++){
			string_set.insert(*it);
			string_uset.insert(*it);
			string_tablica.insert(*it);
			search.push_back(*it);
			
			if(j >= warunek){
				break;
			}
			j++;
		}
		
		std::random_shuffle(search.begin(), search.end());

		number_of_elements = 0;
		start_timer();
		for(it=search.begin(); it != search.end(); it++){
			number_of_elements++;
			string_tablica.find(*it);
		}
		std::cout << "Wyszukiwanie dla string hash_table i zapelnienia: "<< warunek << " zajelo: " << get_time() << std::endl;

		number_of_elements = 0;
		start_timer();
		for(it=search.begin(); it != search.end(); it++){
			number_of_elements++;
			string_set.find(*it);
		}
		std::cout << "Wyszukiwanie dla string set i zapelnienia: "<< warunek << " zajelo: " << get_time() << std::endl;

		number_of_elements = 0;
		start_timer();
		for(it=search.begin(); it != search.end(); it++){
			number_of_elements++;
			string_uset.find(*it);
		}
		std::cout << "Wyszukiwanie dla string uset i zapelnienia: "<< warunek << " zajelo: " << get_time() << std::endl;
	}
}


void main(){
	setlocale(LC_ALL, "polish");

	generuj_dane();
	std::cout << std::endl;
	wstawianie();
	std::cout << std::endl;
	szukanie();
	std::cout << std::endl;
	wypelnienie();
	std::cout << std::endl;
	wypelnienie_string();
	std::cout << std::endl;
	getchar();
}