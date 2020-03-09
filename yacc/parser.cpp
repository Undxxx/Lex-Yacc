#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "ppt.h"
using namespace std;

void productions_standarlize(string,prod &);
int main() {
	//将产生式转化为prod结构体
	prod prods[54];
	for (int i = 0; i < 54; i++) {
		productions_standarlize(productions[i], prods[i]);
	}

	//读入输入文件，分割后保存在vector中
	vector<string> input_tokens;
	ifstream infile;
	infile.open("./input.txt");
	string line;
	while (infile >> line) {
		input_tokens.push_back(line);
	}
	infile.close();
	fstream outfile("./output.txt", ios::app);
	input_tokens.push_back("$");
	//建立栈，开始分析
	vector<string> stack;
	stack.push_back("$");
	stack.push_back("Start");
	int input_reader = 0;
	while (true) {
		if (stack.back() == input_tokens[input_reader]) {
			if (stack.back() == "$") {
				outfile << "Parse Success" << endl;
				outfile.close();
				break;
			}
			else {
				stack.pop_back();
				input_reader++;
			}
		}
		else {
			int x = 0, y = 0;
			for (int i = 0; i < 28; i++) {
				if (nonterminals[i] == stack.back()) {
					x = i;
					break;
				}
			}
			for (int i = 0; i < 25; i++) {
				if (tokens[i] == input_tokens[input_reader]) {
					y = i;
					break;
				}
			}
			int prod_num = ppt[x][y] - 1;
			stack.pop_back();
			outfile << prods[prod_num].left << " -> ";
			for (int i = prods[prod_num].right_size - 1; i >= 0; i--) {
				if (prods[prod_num].right[i] != "ε") {
					stack.push_back(prods[prod_num].right[i]);
				}
			}
			for (int i = 0; i < prods[prod_num].right_size; i++) {
				outfile << prods[prod_num].right[i] << " ";
			}
			outfile << endl;
		}
	}
	system("pause");
}



void productions_standarlize(string production, prod &one_prod) {
	
	
		string left;
		string* right;
		string right_substr;
		vector<string> tmp_right;
		int arrow_pos = 0;

		arrow_pos = production.find("->");
		left = production.substr(0, arrow_pos);
		right_substr = production.substr(arrow_pos + 2, production.size() - arrow_pos - 2);
		string tmp;
		istringstream f(right_substr);
		while (getline(f, tmp, ' ')) {
			tmp_right.push_back(tmp);
		}
		one_prod.left = left;
		one_prod.right = new string[tmp_right.size()];
		one_prod.right_size = tmp_right.size();
		for (int j = 0; j < tmp_right.size(); j++) {
			one_prod.right[j] = tmp_right[j];
		}
		
	

}
