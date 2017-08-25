// Math Parser.cpp : Defines the entry point for the console application.
//

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <ctype.h>
#include <stack>

#include <windows.h>

using namespace std;

enum class PraserState { RUN, STOP };
PraserState _praserState;
bool solvable;

bool WINAPI consoleHandler(DWORD signal) {

	if (signal == CTRL_C_EVENT) {
		_praserState = PraserState::STOP;
	}

	return true;
}

vector<string> tokenize(string equation) {

	istringstream buf(equation);
	istream_iterator<string> beg(buf), end;

	vector<string> tokens(beg, end);

	return tokens;

}

string getInput() {
	string equation;

	cout << "Enter a equation: ";
	getline(cin, equation);
	cout << endl;

	return equation;
}

vector<string> shuntingYard(vector<string> tokens) {
	vector<string> result;
	stack <string> stack;
	bool intflag = false;
	bool opflag = false;
	string tmp = "";

	for (auto& s : tokens) {

		//Process if token is a number
		if(isdigit(s[0])) {
			for (char& c : s) {
				if (isdigit(c) != FALSE) {
					intflag = true;
				}
			}

			if (intflag) {
				result.push_back(s);
				intflag = false;
			}
		}

		//Token is a operator
		else if (s == "+" || s == "-" || s == "/" || s == "*") {

			while (!stack.empty() && (stack.top() == "+" || stack.top() == "-" || stack.top() == "/" || stack.top() == "*") && opflag) {
				if (((s == "+" || s == "-") && (stack.top() == "/" || stack.top() == "*")) || ((s == stack.top() && (s == "/" || s == "*")))) {
					result.push_back(stack.top());
					stack.pop();
				}
				opflag = false;
			}

			opflag = true;
			stack.push(s);
		}

		else if (s == "(") {
			stack.push(s);
		}

		else if (s == ")") {

			tmp = stack.top();

			while (!stack.empty() && (stack.top() != "(")) {
				result.push_back(tmp);
				stack.pop();
				
				tmp = stack.top();
			}

			stack.pop();
		}

		//Token is not an expected symbol
		else {
			solvable = false;
		}

	}

	while (!stack.empty()) {
		result.push_back(stack.top());
		stack.pop();
	}

	return result;
}

double evalulation(vector<string> input) {
	stack <double> stack;
	double result = 0.0;
	double val1 = 0.0;
	double val2 = 0.0;

	for (auto& s : input) {
		if (isdigit(s[0])) {
			stack.push(atof(s.c_str()));
		}

		else {

			if (!stack.empty()) {
				val1 = stack.top();
				stack.pop();
				val2 = stack.top();
				stack.pop();

				if (s == "+") {
					result = val1 + val2;
				}
				if (s == "-") {
					result = val2 - val1;
				}
				if (s == "/") {
					result = val2 / val1;
				}
				if (s == "*") {
					result = val2 * val1;
				}
			}
			stack.push(result);
		}

	}

	return stack.top();
}

void postPrint(vector<string> input) {
	cout << "Postfix is: ";
	for (auto& s : input) {
		cout << s << " ";
	}
	cout << endl;
}

int main()
{
	_praserState = PraserState::RUN;
	while (_praserState == PraserState::RUN) {
		SetConsoleCtrlHandler((PHANDLER_ROUTINE)consoleHandler, TRUE);
		
		solvable = true;
		string input = getInput();

		vector<string> intermediate = shuntingYard(tokenize(input));

		//cout << evalulation(tokenize(input));
		postPrint(intermediate);

		if (!solvable) {
			cout << "Equation has unknown tokens" << endl << endl;
			solvable = true;
		} else {
			cout << evalulation(intermediate) << endl << endl;
		}
	}
	
    return 0;
}