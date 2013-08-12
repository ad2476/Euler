#include "Euler.h"

float initial[2]; // Holds the initial coordinate pair [x,y]
int n; // Number of steps
float h; // Delta-x

const int X=0; const int Y=1; // For the ordered pair initial[]

float diffEq(float x, float y) {

	return eval(expression, x, y, errval); // <------ Change this

}

void Help() {
	cout << "Usage: euler x,y n h" << endl;
	cout << "\tThe point x,y represents the initial ordered pair L0(x)" << endl;
	cout << "\tn and h represent the number of steps and the delta-x, respectively" << endl;
}

/* Returns -1 on failure */
int processArgs(int argc, string* args)
{
	if ((argc!=4)&&(args[1]!="--help")) {
		cout << "Oops! You entered a wrong number of arguments!" << endl;
		Help();
		return 1; // Why 1? I dunno. I like 1.
	}
	else if (args[1]=="--help") {
		cout << "Display this help: euler --help" << endl;
		Help();
		return 1;
	}
	
	/* Parse ordered pair */
	string coords=args[1];
	size_t commapos=coords.find(",");
	string xi_temp=coords.substr(0,commapos);
	string yi_temp=coords.substr(commapos+1,coords.length()-1);
	
	initial[X]=atof(xi_temp.c_str());
	initial[Y]=atof(yi_temp.c_str());
	
	/* Parse n and h */
	n=atoi(args[2].c_str());
	h=atof(args[3].c_str());
	
	cout << "(" << initial[X] << "," << initial[Y] << ")" << endl;
	
	cout << n << ", " << h << "\n\n\n" << endl;
	return 0;
}

void Euler() {
	float y[n+1];
	y[0]=initial[Y];
	
	float x[n+1];
	for (int i=0; i<=n; i++) {
		x[i]=initial[X]+i*h;
	}
	
	float m=diffEq(x[0], y[0]);
	for (int i=1; i<=n; i++) {
		y[i]=y[i-1]+m*(x[i]-x[i-1]);
		m=diffEq(x[i],y[i]);
	}

	
	cout << " X | Y " << endl;
	cout << "-------" << endl;
	for (int i=0; i<=n; i++) {
		cout << x[i] << " | " << y[i] << endl;
	}
}

int main(int argc, char* argv[])
{
	int errval=NONE;
	string input;	
	
	string args[argc];
	for (int i=0; i<argc; i++) {
		args[i]=argv[i];
	}
	
	if(processArgs(argc, args)!=0)
		return 1;
		
	cout << "dy/dx= ";
	getline(cin, input);
	
	expression=shuntingYard(input);
	
	if(err)
	 	cout << vtos(expression) << endl;
	 else {
	 	cout << "PARSE SUCCESS! Evaluating postfix expression:" << endl;
	 	cout << vtos(expression) << "\n" << endl;
	 	
	 	
	 	cout << "\n---------------------------------------------" << endl;
	 	Euler();
	 	
	 	if(errval!=NONE) {
	 		cout << checkErr(errval) << endl;
	 	}
	 }
	 
	return 0;
}
