/* This header contains the basic arithmetic operations: */
/* 1. Exponents (raise to power)                         */
/* 2. Multiplication                                     */
/* 3. Division                                           */
/* 4. Addition                                           */
/* 5. Subtraction                                        */

#ifndef _ALGEXP_H_
	#define _ALGEXP_H_

vector<string> errors;
const int ERR_POS=7; // Width of "ERROR: " substring
const string PARENS_ERR="ERROR: Parenthesis mismatch";
const string OP_ERR="ERROR:  is not a recognised operator";
const int NONE=-1
const int GENERIC=0; // generic error (cause unknown/i'm lazy to program a way of checking it)
const int PARENS=1; // Mismatched parentheses
const int OPER=2; // Operator problem (likely not an operator)
const int INSUFF=3; // Insufficient operands
const int DIVZERO=4; // Divide by zero
const int IMAGINARY=5; // Imaginary number (nth root of negative number, where n%2==0)
const int VAL=6; // Too many values somehow (bad parsing? bad input?)

const int NUM_OPS=8;
const string operators[NUM_OPS] = {".", "(",")","^","*","/","+","-"};


#endif
