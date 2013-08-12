#include "Euler.h"
#include "AlgExp.h"

string rel_var[2]={"x", "y"};

bool searchFor(string token, const string* list, const int size) {
	for(int i=0; i<size; i++) {
		if(token==*(list+i))
			return true;
	}
	return false;
}

int precedence(char token) {
	switch(token) {
		case '.':
			return 5;
		case '(': case ')':
			return 4;
		case '^':
			return 3;
		case '*': case '/':
			return 2;
		case '+': case '-':
			return 1;
		case ' ':
			return 0;
	}
	
	return -1; // There's a problem
}

unsigned int numDigits(float i)
{
    return i > 0 ? (int) log10 ((double) i) + 1 : 1;
}

string vtos(vector<string> input) {
	string output;
	
	for(int i=0; i<input.size(); i++) {
		output.append(input[i]);
		output.append(" ");
	}
		
	return output;
}

string ftos(float x) {
	ostringstream ss;
	ss << x;
	string s(ss.str());
	return s;
}

string checkErr(int errval, string problem=" ") {
	switch(errval) {
		case NONE:
			return "No error. Except reporting no error as an error is in error. So there actually is an error. Somewhere.";
		case GENERIC:
			return "ERROR: Something went all wibbly-wobbly (generic error)";
		case PARENS:
			return "ERROR: Parenthesis mismatch";
		case OPER:
			return "ERROR: "+problem+" is not a recognised operator";
		case INSUFF:
			return "ERROR: Insufficient operands";
		case DIVZERO:
			return "ERROR: Universe broke. Did you try and divide by zero?";
		case IMAGINARY:
			return "ERROR: Unreal, man. Literally. The expression has an imaginary number.";
		case VAL:
			return "ERROR: Too many values somehow. Bad parsing? Bad input? Only Eru knows.";
		default:
			return "Ok. It's time to sleep now. Somehow you returned an error value that does not exist.";
	}
}

/*	Per Wikipedia:
	The shunting yard algorithm is stack-based. Infix expressions are the form of
	mathematical notation most people are used to, for instance 3+4 or 3+4*(2−1).
	For the conversion there are two text variables (strings), the input and the output.
	There is also a stack that holds operators not yet added to the output queue
*/
vector<string> shuntingYard(string input) {	
	vector<string> output; // The output will be a sequence of constants and operators
	stack<string> op_stack; // Working stack of operators
	string top, error;
	
	cout << "Parsing tokens..." << endl;
	for(int i=0; i<input.size(); i++) {
		int pos=i; // Position of last digit in string
		while (input[pos]>='0' && input[pos]<='9')
			pos++; // Find the endpoint of the number substring
		
		size_t delta=pos-i; // Width of substring interval
		if(delta!=0) {
			string token=input.substr(i, delta);
			output.push_back(token);
			// cout << "Reading number " << token << "..." << endl;
			i=pos-1; // Set i ahead to not repeatedly read the same digits
			continue;
		} 
		
		string token=string(1,input[i]);
		if(searchFor(token, operators, NUM_OPS)) { // If token is an operator, push to op_stack
			// cout << "Reading operator " << token << "..." << endl;
			if(!op_stack.empty())				
				top=op_stack.top();
			else top=" ";
			
			// It's a right parens - start popping off stack until bracket match found
			if(token==")") {
				while(!op_stack.empty()) {
					top=op_stack.top();
					op_stack.pop();
					if(top=="(")
						break;
					
					output.push_back(top);
					// cout << "Pushing " << top << " onto output" << endl;
				}
			}
			else if(token=="(")
				op_stack.push(token);
			// If higher precedence, pop top to output and place token on op_stack
			else if(precedence(top[0])>precedence(token[0])) {
				op_stack.pop();
				if(top!="(") { // Don't push a left parens to the output
					output.push_back(top);
					// cout << "Pushing " << top << " onto output" << endl;
				}
				op_stack.push(token);
			}
			// It's just a normal op, push it
			else op_stack.push(token);
			continue;
		}
		else if(token==" ")
			continue;
		else if(isalpha(token[0])) { // Handle a variable
			if(token==rel_var[0]) { // It's our 'x' variable, push to output
				output.push_back(token);
				continue;
			}
			else if(token==rel_var[1]) { // It's our 'y' variable, push to output
				output.push_back(token);
				continue;
			}			
		}
		
		// Not a number, not in list of ops, not a variable, return error
		error=OP_ERR;
		error.insert(ERR_POS, token);
		output.clear();
		output.push_back(error);
		err=true;
		return output;
		
	}
	
	cout << "Popping remaining operators from stack..." << endl;
	// No more tokens, check op_stack
	while(!op_stack.empty()) {
		top=op_stack.top();
		op_stack.pop();
		
		if((top=="(")||(top==")")) {
			output.clear();
			output.push_back(PARENS_ERR);
			err=true;
			return output;
		}
			
		output.push_back(top);
	}
	err=false;
	return output;
}

/* Evaluates a given expression (in RPN)    */
/* Keep in mind that it returns 0 ON ERROR  */
/* Always check that errval==NONE if eval() */
/* returns 0.                               */
float eval(float x, float y, int& errval) {
	stack<float> values; // Stack of values to be evaluated
	float operands[2]; // Array to contain the two operands (assuming n=2 arguments for any operator)
	
	string s_vars[2]={ftos(x), ftos(y)};
	
	for(int thisvar=0; thisvar<2; thisvar++) // Substitute for each variable
	{
		vector<string> vec_var=shuntingYard(s_vars[thisvar]);
	
		cout << "Substituting variable... " << vtos(vec_var) << endl;
		// Go through vector, inserting 'x' into all instances of variable
		for(int i=0; i<expression.size(); i++) {
			if(expression[i]==rel_var[thisvar]) {
				expression.erase(expression.begin()+i);
				expression.insert(expression.begin()+i, vec_var.begin(), vec_var.end());
				i+=vec_var.size();
			}
		}
	}
	
	cout << "After substitution: " << vtos(expression) << endl;

	cout << "Parsing tokens..." << endl;
	for(int i=0; i<expression.size(); i++) {
		string token=expression[i];
		
		// If it's a number, push it to the stack
		if(isdigit(token[0]))
			values.push(atof(token.c_str()));
		// If it's an operator, evaluate
		else if(searchFor(token, operators, NUM_OPS)) {
			float result;
			
			if(values.size()<2) { // Not enough values
				errval=INSUFF;
				return 0.0;
			}
			
			operands[1]=values.top();
			values.pop();
			operands[0]=values.top();
			values.pop();
			
			// Evaluate the operator
			switch(token[0]) {
				case '.':
					result=operands[0]+operands[1]/pow(10, numDigits(operands[1]));
					cout << operands[1] << endl;
					break;
				case '^':
					if(operands[0]<0) {
						errval=IMAGINARY;
						return 0.0;
					}
					result=pow(operands[0], operands[1]);
					break;
				case '*':
					result=operands[0]*operands[1];
					break;
				case '/':
					if(operands[1]==0) {
						errval=DIVZERO;
						return 0.0;
					}
					result=operands[0]/operands[1];
					break;
				case '+':
					result=operands[0]+operands[1];
					break;
				case '-':
					result=operands[0]-operands[1];
					break;
				default:
					errval=OPER;
					return 0.0;
			}
			
			values.push(result);
		}
		else {
			errval=OPER;
			return 0.0;
		}
	}
	
	if(values.size()==1) { // That one value is the result
		errval=NONE;
		return values.top();
	}
	else { // Problem, too many values on stack
		errval=VAL;
		return 0.0;
	}
}
