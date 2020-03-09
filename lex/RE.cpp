#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "structs.h"
using namespace std;
string standarlize_re(string expression);
string add_concat(string expression);
string to_suffix(string expression);
void read_lex_file(string filepath, vector<token> &all_tokens) {
	ifstream infile;
	infile.open(filepath);
	string part1, part2;
	while (infile >> part1) {
		infile >> part2;
		if (part1.find("/") != string::npos) {
			int pos = part1.find("/");
			token one_token;
			one_token.token_name = part1.substr(0, pos);
			one_token.attribute = part1.substr(pos + 1, part1.size() - pos - 1);
			if ((part2.find("[") != string::npos&part2.find("]") != string::npos)
				| (part2.find("?")!=string::npos&part2.size()>1)) {
				string pattern = standarlize_re(part2);
				pattern = to_suffix(pattern);
				one_token.re_pattern = pattern;
				one_token.my_NFA = new NFA;
			}
			else {
				one_token.my_NFA = nullptr;
				one_token.re_pattern = part2;
			}
			all_tokens.push_back(one_token);
		}
		else {
			token one_token;
			one_token.token_name = part1;
			one_token.attribute = "null";
			one_token.re_pattern = part2;
			one_token.my_NFA = nullptr;
			all_tokens.push_back(one_token);
		}
	}
	infile.close();
}

string standarlize_re(string expression) {
	//处理方括号
	while (expression.find("[") != string::npos&expression.find("]") != string::npos) {
		int start = expression.find_first_of("[");
		int end = expression.find_first_of("]");
		string substring = expression.substr(start, end - start + 1);
		
		if (substring == "[a-zA-Z_]") {
			expression.replace(start, end - start + 1,
				"(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z|_)");
		}
		else if (substring == "[0-9]") {
			expression.replace(start, end - start + 1, "(0|1|2|3|4|5|6|7|8|9)");
		}
		else if (substring == "[a-fA-F0-9]") {
			expression.replace(start, end - start + 1, "(a|b|c|d|e|f|A|B|C|D|E|F|0|1|2|3|4|5|6|7|8|9)");
		}
		else if (substring == "[a-zA-Z0-9_]"){
			expression.replace(start, end - start + 1,
				"(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z|0|1|2|3|4|5|6|7|8|9|_)");

		}
		else {
			string replace = "";
			for (int i = start + 1; i < end; i++) {
				replace += expression[i];
				if (i != end - 1) {
					replace += "|";
				}
			}
			replace = "(" + replace + ")";
			expression.replace(start, end - start + 1, replace);
		}
	}
	//处理问号
	int pos = expression.find_first_of("?");
	while (pos != string::npos) {
		if (expression[pos - 1] != ')') {
			string replace = "(ε|" + expression[pos - 1];
			replace += ")";
			expression.replace(pos - 1, 1, replace);
		}
		else {
			int end = pos - 1;
			int start = 0;
			int right_bracket = 0;
			for (int j = end-1; j >= 0; j--) {
				if (expression[j] == '(') {
					if (right_bracket == 0) {
						start = j;
						break;
					}
					else{
						right_bracket--;
					}
				}
				else if (expression[j] ==')') {
					right_bracket++;
				}
			}
			string replace = "(ε|" + expression.substr(start, end - start + 1);
			replace += ")";
			expression.replace(start, pos - start + 1, replace);
		}
		pos = expression.find_first_of("?");
	}
	//处理加号
	int plus_pos = expression.find_first_of("+");
	while (plus_pos!=string::npos) {
		if (expression[plus_pos - 1] == '(') {
			string placeholder = "`";
			expression.replace(plus_pos, 1, placeholder);
			plus_pos = expression.find_first_of("+");
			continue;
		}
		int end = plus_pos - 1;
		int start = 0;
		int right_bracket = 0;
		for (int j = end - 1; j >= 0; j--) {
			if (expression[j] == '(') {
				if (right_bracket == 0) {
					start = j;
					break;
				}
				else {
					right_bracket--;
				}
			}
			else if (expression[j] == ')') {
				right_bracket++;
			}
		}
		string replace = expression.substr(start, end - start + 1) + expression.substr(start, end - start + 1) + "*";
		expression.replace(start, plus_pos - start + 1, replace);
		plus_pos = expression.find_first_of("+");
	}
	string plus = "+";
	int placeholder_pos = expression.find("`");
	if (placeholder_pos != string::npos) {
		expression.replace(placeholder_pos, 1, plus);
	}
	expression = add_concat(expression);
	return expression;
}

string add_concat(string expression) {
	//添加连接符
	string concat = "·";
	string union_char = "|";
	string closure = "*";
	string left = "(";
	string right = ")";
	string res = "";
	string epsilon = "ε";
	for (int i = 0; i < expression.size(); i++) {
		string one = expression.substr(i, 1);
		string check_epsilon = expression.substr(i, 2);
		if (check_epsilon == epsilon) {
			one = epsilon;
			i++;
		}
		res = res+ one;
		if (one == left | one == union_char) {
			continue;
		}
		if (i != expression.size() - 1) {
			string next_char = expression.substr(i + 1, 1);
			if (next_char == closure | next_char == right | next_char == union_char) {
				continue;
			}
			res = res + concat;
		}
		
	}
	return res;
}

string to_suffix(string expression) {
	string res = "";
	string concat = "·";
	string union_char = "|";
	string closure = "*";
	string left = "(";
	string right = ")";
	string epsilon = "ε";
	vector<string> all;
	for (int i = 0; i < expression.size(); i++) {
		string one = expression.substr(i, 1);
		string check_epsilon_or_concat = expression.substr(i, 2);
		if (check_epsilon_or_concat == epsilon | check_epsilon_or_concat==concat) {
			one = check_epsilon_or_concat;
			i++;
		}
		if (one == left) {
			all.push_back(one);
		}
		else if (one == right) {
			string test = all.back();
			while (test != "(") {
				res += test;
				all.pop_back();
				test = all.back();
			}
			if (test == "(") {
				all.pop_back();
			}
		}
		else if (one == concat | one == closure | one == union_char) {
			//优先级：closure>concat>union_char
			if (one == closure) {
				if (!all.empty()) {
					string test = all.back();
					while (test == closure) {
						res += test;
						all.pop_back();
						if (!all.empty()) {
							test = all.back();
						}
						else {
							break;
						}
					}
				}
			}
			else if (one == concat) {
				if (!all.empty()) {
					string test = all.back();
					while (test == concat | test == closure) {
						res += test;
						all.pop_back();
						if (!all.empty()) {
							test = all.back();
						}
						else {
							break;
						}
					}
				}
			}
			else {
				if (!all.empty()) {
					string test = all.back();
					while (test == concat | test == closure | test == union_char) {
						res += test;
						all.pop_back();
						if (!all.empty()) {
							test = all.back();
						}
						else {
							break;
						}
					}
				}
			}
			all.push_back(one);
		}
		else {
			res += one;
		}
	}
	while (!all.empty()) {
		if (all.back() != left) {
			res += all.back();
		}
		all.pop_back();
	}
	return res;
}