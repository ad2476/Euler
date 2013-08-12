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

bool searchFor(string token, const string* list, const int size);
int precedence(char token);
unsigned int numDigits(float i);
string vtos(vector<string> input);
string ftos(float x);
string checkErr(int errval, string problem);
vector<string> shuntingYard(string input);
float eval(float x, float y, int& errval);

extern string rel_var[2]; // The variables in the expression, always in order (x,y)
vector<string> expression; // Vector to hold the expression

bool err;
extern const int NONE; // No error



