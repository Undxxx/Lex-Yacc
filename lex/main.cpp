#include<iostream>
#include<vector>
#include<fstream>
#include"structs.h"
using namespace std;

void read_lex_file(string filepath, vector<token> &all_tokens);
void re_to_NFA(vector<token> &all_tokens);
void NFA_to_DFA(vector<token> &all_tokens);
bool check_match(string str, NFA *my_NFA);
int main() {
	vector<token> all_tokens;
	read_lex_file("REs.l", all_tokens);
	re_to_NFA(all_tokens);
	//NFA_to_DFA(all_tokens);
	//下面是简化版本的一个示例
	ifstream infile;
	infile.open("./input.txt");
	string line;
	string test = "";
	while (infile >> line) {
		test += line;
	}
	infile.close();
	fstream outfile("c:/users/alicia/desktop/output.txt", ios::app);
	string match_str = "";
	string test_str;
	for (int i = 0; i < test.size(); i++) {
		if (test.substr(i,1) != " "&test.substr(i, 1) != "\n") {
			match_str += test.substr(i, 1);
			test_str = match_str + test.substr(i + 1, 1);
			vector<token>::iterator it;
			vector<token>::iterator it_test;
			for (it = all_tokens.begin(); it != all_tokens.end(); it++) {
				bool next_match_pattern = false;
				bool next_equal_pattern = false;
				for (it_test = all_tokens.begin(); it_test != all_tokens.end(); it_test++) {
					if ((*it_test).re_pattern == test_str) {
						next_equal_pattern = true;
						break;
					}
					else if ((*it_test).my_NFA != nullptr) {
						if (check_match(test_str, (*it_test).my_NFA) == true) {
							next_match_pattern = true;
							break;
						}
					}
				}
				if ((*it).re_pattern == match_str& next_equal_pattern==false) {
					cout << (*it).token_name << " " << (*it).attribute << " " << match_str << endl;
					outfile << (*it).token_name << " ";
					outfile << (*it).attribute << " ";
					outfile << match_str << endl;
					match_str = "";
					break;
				}
				else if ((*it).my_NFA != nullptr) {
					if (check_match(match_str, (*it).my_NFA) == true & next_match_pattern == false & next_equal_pattern == false) {
						cout << (*it).token_name << " " << (*it).attribute << " " << match_str << endl;
						outfile << (*it).token_name << " ";
						outfile << (*it).attribute << " ";
						outfile << match_str << endl;
						match_str = "";
						break;
					}
				}
			}
		}
	}
	outfile.close();
}