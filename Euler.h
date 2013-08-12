#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <utility> // Contains the pair data type
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <sstream>

#define CLEAR "clear" // On UNIX systems
// #define CLEAR "cls" // On DOS/Windows systems

using namespace std;

bool searchFor(string token, const string* list, const int size); // Search for a "token" in a "list" of size "size"
int precedence(char token); // Check the precedence of an operator
unsigned int numDigits(float i); // How many digits are in this float?
string vtos(vector<string> input); // Vector to string "translation"
string ftos(float x); // Float to string conversion
string checkErr(int errval, string problem); // We have an error number, what the hell does it actually mean?
vector<string> shuntingYard(string input); // Perform the shunting yard algorithm on an input
float eval(float x, float y, int& errval); // Evaluate the parsed expression for given x and y values

extern string rel_var[2]; // The variables in the expression, always in order (x,y)
vector<string> expression; // Vector to hold the expression

bool err; // Kind of forget what this was for...
extern const int NONE; // No error



