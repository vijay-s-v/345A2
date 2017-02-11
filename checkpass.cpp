#include <stdio.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "HashTable.h"

//#define ANALYZE

using namespace std;

// Parses all passwords in passwords.txt into a vector
vector<string> readPasswords(){

	vector<string> passwords;
	ifstream ifs;
	ifs.open("passwords.txt");
	
	string pw;
	while(getline(ifs, pw, '\n')){
		passwords.push_back(pw);
	}

	ifs.close();
	return passwords;
}

void writePassword(string s){

	ofstream ofs;
	ofs.open("passwords.txt", ios_base::app);
	ofs << endl << s; 
	ofs.close();

}

// Returns true if s is a valid password, false otherwise
bool checkPass(string s){
	// Conditions: must be between 6 to 12 characters 
	//             must only contain alphanumeric symbols
	int l = s.length();
	if(l < 6 || l > 12){
		return false;
	}

	for(int i = 0; i < l; i++){
		if(!isalnum(s[i])){
			return false;
		}
	}

	return true;
}

// Returns the mirror of a string
string mirrorMe(string s){
	string retval = "";
	for(int i = s.length() - 1; i > -1; i--){
		retval += s[i];
	}
	return retval;
}

int main(int argc, char * argv[]){
	HashTable myTable;

#ifndef ANALYZE
	string pw = argv[1];
	// Check if password is valid
	if(!checkPass(pw) || argc != 2){
		cout << "INVALID" << endl;
		return 0;
	}
#endif

	vector<string> passwords = readPasswords();
	for(int i = 0; i < passwords.size(); i++){
		myTable.insert(passwords[i]);
	}

#ifndef ANALYZE
	// Check if password exists in table
	string pwReverse = mirrorMe(pw);
	if(myTable.search(pw) == -1 || myTable.search(pwReverse) == -1){
		cout << "INVALID" << endl;
		return 0;
	}

	writePassword(pw);
	cout << "VALID" << endl;
	return 0;
#endif

#ifdef ANALYZE
	int x = myTable.getCollisions();
	double a = myTable.loadFactor();
	cout << "Table size: " << TABLE_SIZE << endl;
	cout << "Collisions: " << x << endl;
	cout << "Load factor: " << a << endl;
#endif
}
