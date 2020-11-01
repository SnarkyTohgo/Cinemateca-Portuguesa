#ifndef CINEMATECAPORTUGUESA_UTILS_H
#define CINEMATECAPORTUGUESA_UTILS_H

#include "defs.h"


/*
 * Extern Globals
 */

extern ifstream salasDB;
extern ifstream eventosDB;
extern ifstream aderentesDB;

extern vector<string> salasData;
extern vector<string> eventosData;
extern vector<string> aderentesData;


/*
 * INPUT / OUTPUT
 */

/*
 * Prints a line of specified size with specified character
 */
void line(int size, char ch = '-');

void cinERR(const string &message);

/*
 * Tries to get a valid int option from cin to use in a switch-case
 */
void getOption(int &dest, const string &message = "Option: ", function<bool(int)> cond = [](int a) { return true; });

void getOptionList(vector<int> &dest, const string &message = "Option (* to end): ", function<bool(int)> cond = [](int a) { return true; });

/*
 * Tries to get a valid int option from cin to use in a switch-case
 */
void getDouble(double &dest, const string &message = "Enter double: ");

void enterWait(const string &message = "ENTER to go back");


/*
 * CALC
 */

int rng(int lower, int upper);


/*
 * TEXT
 */

// To Uppercase
string toUpper(string s);

// Left Trim
void lTrim(string &s);

// Right Trim
void rTrim(string &s);

// Trim
void trim(string &s);

// Split
template<typename t>
void split(const string& s, char delim, t result);

vector<string> split(const string &s, char delim);


/*
 * FILES
 */

// Empty Check
bool fileIsEmpty(ifstream& file);

// Make File
void makeFile(string filename);

// Read File
ifstream readFile(string filename);

// Write to File
void writeToFile(vector<string> &data, string filename);
void writeToFile(string &data, string filename);

// Write Data
void writeData(string data, string filename);

// Parse File Data
vector<string> parseFile(ifstream &file);

// Delete Data
void deleteFileData(string filename);




#endif //CINEMATECAPORTUGUESA_UTILS_H
