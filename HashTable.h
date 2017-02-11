#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

// To make the analysis easier
#define TABLE_SIZE 1177 // Default size should be 1177

class HashTable{

	private:
		vector<list<string>> table;
		int numElements;
		int collisions; 

	public:
		HashTable();
		~HashTable();
		bool insert(string s);
		bool del(string s); // Don't really need to implement or call this
		int search(string s);
		int myHash(string s);
		int getCollisions(); // To make the report and analysis easier
		double loadFactor(); // To make the report and analysis easier
		void printTableLoad(); // Debug function to show how the table is populated

};

#endif /* HASHTABLE_H */