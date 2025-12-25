#pragma once

#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <functional>
#include "DynamicStack.h"

using namespace std;

class Formula {
	string Expression;
	string PostfixForm = "";
	DynamicStack<char> st;

	int priority(const char ch) {
		switch (ch) {
		case '(':
			return 0;
		case ')':
			return 1;
		case '+': case '-':
			return 2;
		case '*': case '/':
			return 3;
		}
	}

	void processOperator(char op) {
		PostfixForm += ' ';
		while (!st.isEmpty()) {
			char stackitem = st.pop();
			if (priority(stackitem) >= priority(op)) {
				PostfixForm += stackitem;
				PostfixForm += ' ';
			}
			else {
				st.push(stackitem);
				break;
			}
		}
		st.push(op);
	}

public:

	Formula(string ex) {
		Expression = ex;
	}

	string getPostfix() {
		if (PostfixForm.empty()) throw - 1;
		return PostfixForm;
	}

	bool validateBrackets(){
		enum State {
			S0, //начальное
			S1, //есть незакрытые скобки
		};

		map<State, map<char, State>> transitionTable = {
			{S0, {
				{'(', S1}
			}},
			{S1, {
				{'(', S1}, {')', S0}
			}}
		};

		State cur = S0;
		int count = 0;

		for (char c : Expression) {
			if (c != '(' && c != ')') continue;
			if (transitionTable[cur].find(c) != transitionTable[cur].end()) {
				cur = transitionTable[cur][c];
				if (cur == S1) count++;
				else count--;
			}
			else {
				return false;
			}
		}
		if (cur != S0 || count != 0) {
			return false;
		}
		return true;
	}

	bool validateOperations() {
		enum State {
			s0, //начальное
			s1, //после операнда
			s2, //после оператора
			s3, //после открывающей скобки
			s4 //после закрывающей скобки
		};
		map<State, map<char, State>> transitionTable = {
			{s0, {
				{'(', s3},
				{'0', s1}, {'1', s1}, {'2', s1}, {'3', s1}, {'4', s1}, {'5', s1}, {'6', s1}, {'7', s1}, {'8', s1}, {'9', s1}, {'-', s1}
			}},
			{s1, {
				{'+', s2}, {'-', s2}, {'*', s2}, {'/', s2},
				{'0', s1}, {'1', s1}, {'2', s1}, {'3', s1}, {'4', s1}, {'5', s1}, {'6', s1}, {'7', s1}, {'8', s1}, {'9', s1},
				{')', s4}
			}},
			{s2, {
				{'(', s3},
				{'0', s1}, {'1', s1}, {'2', s1}, {'3', s1}, {'4', s1}, {'5', s1}, {'6', s1}, {'7', s1}, {'8', s1}, {'9', s1}
			}},
			{s3, {
				{'(', s3},
				{'0', s1}, {'1', s1}, {'2', s1}, {'3', s1}, {'4', s1}, {'5', s1}, {'6', s1}, {'7', s1}, {'8', s1}, {'9', s1}, {'-', s1}
			}},
			{s4, {
				{'+', s2}, {'-', s2}, {'*', s2}, {'/', s2},
				{')', s4}
			}}
		};

		State cur = s0;
		for (char c : Expression) {
			if (transitionTable[cur].find(c) != transitionTable[cur].end()) {
				cur = transitionTable[cur][c];
			}
			else {
				return false;
			}
		}
		if (cur != s1 && cur != s4) {
			return false;
		}
		return true;
	}

	void convertToPostfix() {
		enum State {
			s0, //начальное
			s1, //цифра
			s2, //оператор
			s3, //открывающая скобка
			s4 //закрывающая скобка
		};

		map<State, map<char, State>> transitionTable = {
			{s0, {
				{'(', s3},
				{'0', s1}, {'1', s1}, {'2', s1}, {'3', s1}, {'4', s1}, {'5', s1}, {'6', s1}, {'7', s1}, {'8', s1}, {'9', s1}, {'-', s1}
			}},
			{s1, {
				{'+', s2}, {'-', s2}, {'*', s2}, {'/', s2},
				{'0', s1}, {'1', s1}, {'2', s1}, {'3', s1}, {'4', s1}, {'5', s1}, {'6', s1}, {'7', s1}, {'8', s1}, {'9', s1},
				{')', s4}
			}},
			{s2, {
				{'(', s3},
				{'0', s1}, {'1', s1}, {'2', s1}, {'3', s1}, {'4', s1}, {'5', s1}, {'6', s1}, {'7', s1}, {'8', s1}, {'9', s1}
			}},
			{s3, {
				{'(', s3},
				{'0', s1}, {'1', s1}, {'2', s1}, {'3', s1}, {'4', s1}, {'5', s1}, {'6', s1}, {'7', s1}, {'8', s1}, {'9', s1}, {'-', s1}
			}},
			{s4, {
				{'+', s2}, {'-', s2}, {'*', s2}, {'/', s2},
				{')', s4}
			}}
		};

		map<State, map<char, function<void()>>> eventTable;

		auto addAction = [&](State from, char c, auto action) {
			eventTable[from][c] = action;
		};

		addAction(State::s3, '(', [&]() { st.push('('); });
		addAction(State::s4, ')', [&]() {
			char stackitem = st.pop();
			while (stackitem != '(') {
				PostfixForm += ' ';
				PostfixForm += stackitem;
				stackitem = st.pop();
			}
		});
		addAction(State::s1, '0', [&]() {PostfixForm += '0';});
		addAction(State::s1, '1', [&]() {PostfixForm += '1';});
		addAction(State::s1, '2', [&]() {PostfixForm += '2';});
		addAction(State::s1, '3', [&]() {PostfixForm += '3';});
		addAction(State::s1, '4', [&]() {PostfixForm += '4';});
		addAction(State::s1, '5', [&]() {PostfixForm += '5';});
		addAction(State::s1, '6', [&]() {PostfixForm += '6';});
		addAction(State::s1, '7', [&]() {PostfixForm += '7';});
		addAction(State::s1, '8', [&]() {PostfixForm += '8';});
		addAction(State::s1, '9', [&]() {PostfixForm += '9';});
		addAction(State::s1, '-', [&]() {PostfixForm += '-';});

		addAction(State::s2, '+', [&]() { processOperator('+'); });
		addAction(State::s2, '-', [&]() { processOperator('-'); });
		addAction(State::s2, '*', [&]() { processOperator('*'); });
		addAction(State::s2, '/', [&]() { processOperator('/'); });

		State cur = s0;

		for (char item : Expression) {
			if (transitionTable[cur].find(item) != transitionTable[cur].end()) {
				State next = transitionTable[cur][item];
				if (eventTable[next].find(item) != eventTable[next].end()) {
					eventTable[next].find(item)->second();
				}
				cur = next;
			}
		}
		while (!st.isEmpty()) {
			PostfixForm += ' ';
			PostfixForm += st.pop();
		}
	}

	int Calculate() {

		enum State {
			s0, // начальное
			s1, // после цифры
			s2, // после оператора
			s3 // после пробела
		};

		map<State, map<char, State>> transitionTable = {
			{s0, {
				{'0', s1}, {'1', s1}, {'2', s1}, {'3', s1}, {'4', s1}, {'5', s1}, {'6', s1}, {'7', s1}, {'8', s1}, {'9', s1}, {'-', s1},
				{' ', s3}
			}},
			{s1, {
				{'0', s1}, {'1', s1}, {'2', s1}, {'3', s1}, {'4', s1}, {'5', s1}, {'6', s1}, {'7', s1}, {'8', s1}, {'9', s1},
				{' ', s3}
			}},
			{s2, {
				{' ', s3}
			}},
			{s3, {
				{'0', s1}, {'1', s1}, {'2', s1}, {'3', s1}, {'4', s1}, {'5', s1}, {'6', s1}, {'7', s1}, {'8', s1}, {'9', s1},
				{'+', s2}, {'-', s2}, {'/', s2}, {'*', s2}
			}}
		};
		
		map<State, map<char, function<void()>>> eventTable;

		auto addAction = [&](State from, char c, auto action) {
			eventTable[from][c] = action;
		};

		string operand = "";

		addAction(State::s1, '-', [&]() {operand += '-'; });
		addAction(State::s1, '0', [&]() {operand += '0'; });
		addAction(State::s1, '1', [&]() {operand += '1'; });
		addAction(State::s1, '2', [&]() {operand += '2'; });
		addAction(State::s1, '3', [&]() {operand += '3'; });
		addAction(State::s1, '4', [&]() {operand += '4'; });
		addAction(State::s1, '5', [&]() {operand += '5'; });
		addAction(State::s1, '6', [&]() {operand += '6'; });
		addAction(State::s1, '7', [&]() {operand += '7'; });
		addAction(State::s1, '8', [&]() {operand += '8'; });
		addAction(State::s1, '9', [&]() {operand += '9'; });

		DynamicStack<double> stack;
		int a, b;
		State cur = s0;
		State next;
		char Next = ' ';
		char item = ' ';

		addAction(State::s2, '+', [&]() {
			b = stack.pop();
			a = stack.pop();
			stack.push(a + b);
		});
		addAction(State::s2, '-', [&]() {
			if (Next == ' ') {
				b = stack.pop();
				a = stack.pop();
				stack.push(a - b);
			}
			else {
				next = s1;
				operand += '-';
			}
		});
		addAction(State::s2, '*', [&]() {
			b = stack.pop();
			a = stack.pop();
			stack.push(a * b);
		});
		addAction(State::s2, '/', [&]() {
			b = stack.pop();
			a = stack.pop();
			stack.push(a / b);
		});

		addAction(State::s3, ' ', [&]() {
			if (!operand.empty()) {
				stack.push(stoi(operand));
				operand = "";
			}
		});

		
		PostfixForm += ' ';

		for (int i = 0; i < PostfixForm.length() - 1; i++) {
			item = PostfixForm[i];
			Next = PostfixForm[i+1];
			if (transitionTable[cur].find(item) != transitionTable[cur].end()) {
				next = transitionTable[cur][item];
				if (eventTable[next].find(item) != eventTable[next].end()) {
					eventTable[next].find(item)->second();
				}
				cur = next;
			}
		}

		return stack.pop();
	}
};