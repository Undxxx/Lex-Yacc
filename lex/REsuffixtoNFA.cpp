#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "structs.h"
using namespace std;

void re_to_NFA(vector<token> &all_tokens);
void get_one_NFA(token &);
void re_to_NFA(vector<token> &all_tokens) {
	vector<token>::iterator it;
	for (it = all_tokens.begin(); it != all_tokens.end(); it++) {
		if ((*it).my_NFA != nullptr) {
			get_one_NFA(*it);
		}
	}
}
void get_one_NFA(token &one_token) {
	vector<NFA *> all_NFA;
	string test_concat = "¡¤";
	string re = one_token.re_pattern;
	for (int i = 0; i < re.size(); i++) {
		string one = re.substr(i, 1);
		string check_epsilon_or_concat = re.substr(i, 2);
		if (check_epsilon_or_concat == "¦Å"|check_epsilon_or_concat=="¡¤") {
			one = check_epsilon_or_concat;
			i++;
		}
		if (one == "|") {
			NFA *nfa2 = all_NFA.back();
			all_NFA.pop_back();
			NFA *nfa1 = all_NFA.back();
			all_NFA.pop_back();
			nfa1->union_another(nfa2);
			all_NFA.push_back(nfa1);
		}
		else if (one == "¡¤") {
			NFA *nfa2 = all_NFA.back();
			all_NFA.pop_back();
			NFA *nfa1 = all_NFA.back();
			all_NFA.pop_back();
			nfa1->concat(nfa2);
			all_NFA.push_back(nfa1);
		}
		else if (one == "*") {
			NFA *nfa1 = all_NFA.back();
			all_NFA.pop_back();
			nfa1->get_closure();
			all_NFA.push_back(nfa1);
		}
		else {
			state *start_state = new state(false);
			state *end_state = new state(true);
			start_state->edges.insert(make_pair(one, end_state));
			NFA *one_NFA = new NFA;
			one_NFA->start_state = start_state;
			one_NFA->end_state = end_state;
			all_NFA.push_back(one_NFA);
		}
	}
	one_token.my_NFA = all_NFA.back();
}