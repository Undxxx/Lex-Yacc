#pragma once
#include <string>
#include <unordered_map>
using std::string;
using std::unordered_map;
class state {
public:
	bool isEnd = false;
	unordered_map<string, state *> edges;
	state(bool end) {
		isEnd = end;
	}
};
class NFA {
public:
	state *start_state;
	state *end_state;
	void concat(NFA *another) {
		this->end_state->isEnd = false;
		this->end_state->edges.insert(std::make_pair("¦Å", another->start_state));
		this->end_state = another->end_state;
	};
	void union_another(NFA *another) {
		state *new_start_state = new state(false);
		state *new_end_state = new state(true);
		new_start_state->edges.insert(std::make_pair("¦Å1", this->start_state));
		new_start_state->edges.insert(std::make_pair("¦Å2", another->start_state)); 
		this->end_state->isEnd = false;
		another->end_state->isEnd = false;
		this->end_state->edges.insert(std::make_pair("¦Å1", new_end_state));
		another->end_state->edges.insert(std::make_pair("¦Å2", new_end_state));
		this->start_state = new_start_state;
		this->end_state = new_end_state;
	};
	void get_closure() {
		state *new_start_state = new state(false);
		state *new_end_state = new state(true);
		new_start_state->edges.insert(std::make_pair("¦Å1", this->start_state));
		new_start_state->edges.insert(std::make_pair("¦Å2", new_end_state));
		this->end_state->isEnd = false;
		this->end_state->edges.insert(std::make_pair("¦Å1", this->start_state));
		this->end_state->edges.insert(std::make_pair("¦Å2", new_end_state));
		this->start_state = new_start_state;
		this->end_state = new_end_state;
	};
};
class DFA_state {
	/*
public:
	bool isEnd = false;
	vector<state *> NFA_states;
	unordered_map<string, DFA_state *> edges;
	DFA_state(bool end) {
		isEnd = end;
	}*/
};
class DFA {
	DFA_state *start_state;
	DFA_state *end_state;
};
struct Min_DFA {

};
struct token {
	string token_name;
	string attribute;
	string re_pattern;
	NFA *my_NFA;
	DFA *my_DFA;
};

 