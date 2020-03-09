#pragma once
#include <string>
#include<sstream>
using namespace std;
string tokens[] = { "INT", "FLOAT", "FOR", "WHILE", "IF", "{", "}", "(", ")", "+", "-", "*", "/", "<", ">", ",", ";", "EQ_OP", "LE_OP", "GE_OP", "NE_OP", "IDENTIFIER", "CONSTANT","=", "$" };
string nonterminals[] = { "Start", "Function", "Type", "Arg", "Declaration", "ArgList", "ArgList'", "IdentList", "IdentList'", "Stmt", "CompoundStmt", "ForStmt", "OptExpr", "WhileStmt", "IfStmt", "StmtList",
	"StmtList'", "Expr", "Rvalue", "Rvalue'", "Compare", "Mag", "Mag''", "Mag'", "Term", "Term''", "Term'", "Factor"};
int ppt[28][25] = { {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.0},
					{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{9,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{3,3,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,13,0,0,0,0,0,0,0,0},
					{19,19,14,15,17,18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,0,0,0},
					{0,0,0,0,0,25,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,21,22,21,21,0,0,0,0,0,22,0,0,0,0,21,21,0,0},
					{0,0,0,23,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,24,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{26,26,26,26,26,26,29,0,0,0,0,0,0,0,0,0,0,0,0,0,0,26,0,0,0},
					{27,27,27,27,27,27,28,0,0,0,0,0,0,0,0,0,0,0,0,0,0,27,0,0,0},
					{0,0,0,0,0,0,0,30,0,30,30,0,0,0,0,0,0,0,0,0,0,30,30,0,0},
					{0,0,0,0,0,0,0,31,0,31,31,0,0,0,0,0,0,0,0,0,0,31,31,0,0},
					{0,0,0,0,0,0,0,0,33,0,0,0,0,32,32,0,33,32,32,32,32,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,35,36,0,0,34,37,38,39,0,0,0,0}, 
					{0,0,0,0,0,0,0,40,0,40,40,0,0,0,0,0,0,0,0,0,0,40,40,0,0}, 
					{0,0,0,0,0,0,0,0,42,41,41,0,0,42,42,0,42,42,42,42,42,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,43,44,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,45,0,45,45,0,0,0,0,0,0,0,0,0,0,45,45,0,0},
					{0,0,0,0,0,0,0,0,47,47,47,46,46,47,47,0,47,47,47,47,47,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,48,49,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,50,0,52,51,0,0,0,0,0,0,0,0,0,0,53,54,0,0}};
string productions[] = {
	"Start->Function",
	"Function->Type IDENTIFIER ( ArgList ) CompoundStmt",
	"ArgList->Arg ArgList'",
	"ArgList'->, Arg ArgList'",
	"ArgList'->��",
	"ArgList->��",
	"Arg->Type IDENTIFIER",
	"Declaration->Type IdentList ;",
	"Type->INT",
	"Type->FLOAT",
	"IdentList->IDENTIFIER IdentList'",
	"IdentList'->, IdentList",
	"IdentList'->��",
	"Stmt->ForStmt",
	"Stmt->WhileStmt",
	"Stmt->IDENTIFIER = Expr ;",
	"Stmt->IfStmt",
	"Stmt->CompoundStmt",
	"Stmt->Declaration",
	"ForStmt->FOR ( Expr ; OptExpr ; OptExpr ) Stmt",
	"OptExpr->Expr",
	"OptExpr->��",
	"WhileStmt->WHILE ( Expr ) Stmt",
	"IfStmt->IF ( Expr ) Stmt",
	"CompoundStmt->{ StmtList }",
	"StmtList->StmtList'",
	"StmtList'->Stmt StmtList'",
	"StmtList'->��",
	"StmtList->��",
	"Expr->Rvalue",
	"Rvalue->Mag Rvalue'",
	"Rvalue'->Compare Mag Rvalue'",
	"Rvalue'->��",
	"Compare->EQ_OP",
	"Compare-><",
	"Compare->>",
	"Compare->LE_OP",
	"Compare->GE_OP",
	"Compare->NE_OP",
	"Mag->Term Mag''",
	"Mag''->Mag' Mag''",
	"Mag''->��",
	"Mag'->+ Term",
	"Mag'->- Term",
	"Term->Factor Term''",
	"Term''->Term' Term''",
	"Term''->��",
	"Term'->* Factor",
	"Term'->/ Factor",
	"Factor->( Expr )",
	"Factor->- Factor",
	"Factor->+ Factor",
	"Factor->IDENTIFIER",
	"Factor->CONSTANT"
};
struct prod {
	string left;
	string *right;
	int right_size;
};