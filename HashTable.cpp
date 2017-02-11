#include "HashTable.h"

HashTable::HashTable(){
	numElements = 0;
	collisions = 0;
	table.resize(TABLE_SIZE);
}

HashTable::~HashTable(){
	for(int i = 0; i < TABLE_SIZE; i++){
		table[i].clear();
	}
	table.clear();
}

// Hashes strings into a specific bucket in our table
int HashTable::myHash(string s){
	// Password will have alphanumeric characters only
	// Convert chars into ASCII int equivalent and sum them up
	// Then use division hashing
	// Highest value is 48, and lowest is 122
	// So the range of values will be [288 , 1464] 

	int sum = 0;
	for(int i = 0; i < s.length(); i++){
		sum += static_cast<int>(s[i]);
	}
	int retval = sum % TABLE_SIZE;
	return retval;
}

// Attempt to insert an element into the table
// Return true if the insertion is successful
// Return false otherwise (element already exists in table)
bool HashTable::insert(string s){
	// Check to see if s is already in the table
	int h = search(s);
	if(h == -1){
		return false;
	}

	// Check for collision and update 
	// counter accordingly
	if(!(table[h].empty())){
		collisions++;
	}

	table[h].push_back(s);
	numElements++;	
	return true;
}

// Not necessary for this assignment
// Never called, filler function
bool HashTable::del(string s){
	numElements--;
	return true;
}

// Returns -1 if s exists in the table
// Returns the hash of s otherwise
int HashTable::search(string s){
	int h = myHash(s);
	int l = table[h].size();

	for(int i = 0; i < l; i++){
		for(list<string>::iterator it = table[h].begin(); it != table[h].end(); ++it){
			if(s.compare(*it) == 0){
				return -1;
			}
		}
	}

	return h;
}

// Calculate the current load factor
// of the hash table
double HashTable::loadFactor(){
	double retval = (static_cast<double>(numElements))/(static_cast<double>(TABLE_SIZE));
	return retval;
}

// Return the number of collisions
// that have occured so far
int HashTable::getCollisions(){
	return collisions;
}

// Iterate throught the table and
// output to the console how many elements
// are in each bucket of the table
void HashTable::printTableLoad(){
	int maxLoad = 0;
	double avgLoad = 0;
	int emptyBuckets = 0;
	int totalElements = 0;

	for(int i = 0; i < TABLE_SIZE; i++){
		if(table[i].empty()){
			emptyBuckets++;
			continue;
		}
		int x = table[i].size();
		avgLoad += x;
		totalElements += x;
		if(x > maxLoad){ maxLoad = x; }
		cout << "Bucket " << i << " has " << x << " elements" << endl;
	}

	avgLoad = avgLoad/(TABLE_SIZE - emptyBuckets);
	cout << "The number of unused buckets is: " << emptyBuckets << endl;
	cout << "The maximum number of elements in a bucket is: " << maxLoad << endl;
	cout << "The average number of elements in a bucket is: " << avgLoad << endl;
	cout << "The total number of elements is: " << totalElements << endl << endl;
}