#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "structs.h"
using namespace std;
bool check_match(string str, NFA *my_NFA);
void get_closure(vector<state *> &, state *);
void NFA_to_DFA(vector<token> &all_tokens);
void get_one_DFA(token &);
//�򻯰汾���������DFA��ֻ��DFA��˼·����NFA
bool check_match(string str, NFA *my_NFA) {
	//DFA�ĳ�̬ΪNFA��̬�Ħ�-closure
	state *start_state = my_NFA->start_state; 
	vector<state *> current_states;
	current_states.push_back(start_state);
	get_closure(current_states, start_state);
	for (int i = 0; i < str.size(); i++) {
		vector<state *> next_states;
		unordered_map<string, state *>::iterator it_next_state; //ͨ���ߵ���״̬��ָ��
		vector<state *>::iterator it_current_state; //���е�ǰ״̬��vector�ĵ�����
		for (it_current_state = current_states.begin(); it_current_state != current_states.end(); it_current_state++) {
			it_next_state = (*it_current_state)->edges.find(str.substr(i, 1));
			if (it_next_state != (*it_current_state)->edges.end()) {
				next_states.push_back((*it_next_state).second);
				get_closure(next_states, (*it_next_state).second);
			}
		}
		if (next_states.empty() == true) {
			return false;
		}
		current_states = next_states;
	}
	//���current_states�Ƿ������̬
	vector<state *>::iterator it_current_state;
	if (current_states.empty() == true) {
		return false;
	}
	for (it_current_state = current_states.begin(); it_current_state != current_states.end(); it_current_state++) {
		if ((*it_current_state)->isEnd == true) {
			return true;
		}
	}
	return false;
}
void get_closure(vector<state *> &states, state *one_state) {
	unordered_map<string, state *>::iterator edges;
	for (edges = one_state->edges.begin(); edges != one_state->edges.end(); edges++) {
		if ((*edges).first.find("��") != string::npos) {
			states.push_back((*edges).second);
			get_closure(states, (*edges).second);
		}
	}
}
//����DFA
void NFA_to_DFA(vector<token> &all_tokens) {
	vector<token>::iterator it;
	for (it = all_tokens.begin(); it != all_tokens.end(); it++) {
		if ((*it).my_NFA != nullptr) {
			get_one_DFA(*it);
		}
		else {
			(*it).my_DFA = nullptr;
		}
	}
}
void get_one_DFA(token &one_token) {
	/*
	NFA *token_NFA = one_token.my_NFA;
	one_token.my_DFA = new DFA;
	state *start_state = token_NFA->start_state;
	vector<state *> current_states;
	current_states.push_back(start_state);
	get_closure(current_states, start_state);
	one_token.my_DFA->start_state = new DFA_state(false);
	one_token.my_DFA->start_state->NFA_states = current_states;
	*/

}
