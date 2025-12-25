#include <iostream>

#include "Formula.h"

using namespace std;

int main() {
	setlocale(LC_CTYPE, "rus");
	Formula exp("2+(-3)*4");
	if (exp.validateBrackets() && exp.validateOperations()) {
		exp.convertToPostfix();
		cout << exp.getPostfix() << endl;
		cout << exp.Calculate();
	}
	else {
		cout << "Было введено недопустимое выражение";
	}
}