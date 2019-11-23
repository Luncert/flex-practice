#include <stdio.h>
#include "scanner.h"

enum yytokentype {
    BAI=899,
    SEMI=901,
    COMMA=902,
    PLUS=904,
    MINUS=905,
    STAR=906,
    DIV=907,
    LP=908,
    RP=909,
    LB=910,
    RB=911,
    LC=912,
    RC=913,
    NUMBER = 258,
    EOL = 259,
    ID = 112,
    WHILE = 113,
    ELSE = 114,
    RETURN = 115,
    PRINT = 1116,
    SCAN = 117,
    INT =  301,
    STR =302,
    VOID = 303,
    STRING = 304,
    IF=305,
    CMP=306,
    ASSIGN=903,
    EN=904,
    END=999
};

void intstr_list1();
void declarator_list1();
void primary_ID();
void expr_list1();
void program();
void programr();
void external_declaration();
void type();
void decl_or_stmt();
void declarator_list();
void declarator();
void initializer();
void parameter_list();
void parameter();
void statement_list();
void statement();
void intstr_list();
void expression_statement();
void expr();
void cmp_expr();
void add_expr();
void mul_expr();
void primary_expr();
void expr_list();
void id_list();
void statement_list1();
void parameter_list1();
void cmp_expr1();
void add_expr1();
void id_list1();
void mul_expr1();

int tok;

void advance()
{
	tok = yylex();
	if (tok != EOL){
		printf("tok:%d,%s\n", tok, yytext);
	}
	else{
		advance();
	}
}

void program()
{
	printf("program->external_declaration programR\n");
	external_declaration();
	programr();
}

void programr()
{
	printf("programR->external_declaration programR|null\n");
	if (tok == INT || tok == STR || tok == VOID) {
		external_declaration();
		programr();
	}
}

void external_declaration()
{
	printf("external_declaration->type declarator decl_or_stmt\n");
	type();
	declarator();
	decl_or_stmt();
}


void decl_or_stmt() {
	printf("decl_or_stmt->{statement_list}|{}|,declarator_list;|;\n");
	if (tok == LC)
	{
		advance();
		if (tok != RC)
		{
			statement_list();
		}
		advance();
	}
	else if (tok == COMMA) {
		advance();
		declarator_list();
		if (tok == SEMI) {
			advance();
		}

	}
	else if (tok == SEMI) {
		advance();
	}
}

void declarator_list()
{
	printf("declarator_list->declarator declarator_list1\n");
	declarator();
	declarator_list1();
}

void declarator_list1()
{
	printf("declarator_list1->,declarator|null\n");
	if (tok == COMMA)
	{
		advance(); 
		declarator();
		declarator_list1();
	}
}

void initializer()
{
	printf("initializer->NUMBER|STRING\n");
	if (tok == NUMBER)
	{
		advance();
	}
	else if (tok == ID)
	{
		advance();
	}
}

void intstr_list() {
	printf("intstr_list->initializer intstr_list1\n");
	initializer();
	intstr_list1();
}

void intstr_list1() {
	printf("intstr_list1->,intstr_list1|null\n");
	if (tok == SEMI) {
		advance();
		initializer();
		intstr_list1();
	}
}



void parameter_list()
{
	printf("parameter_list->parameter parameter_list1\n");
	parameter();
	parameter_list1();
}

void parameter_list1()
{
	printf("parameter_list1->,parameter parameter_list1|null\n");
	if (tok == SEMI)
	{
		advance();
		parameter();
		parameter_list1();
	}
}

void parameter() {
	printf("parameter->type ID\n");
	type();
	if (tok == ID) {
		advance();
	}
}

void type() {
	printf("type->INT|STR|VOID\t%s\n", yytext);
	if (tok == INT || tok == STR || tok == VOID) {
		advance();
	}
}


void statement() {
	printf("statement->type declarator_list;|{statement_list}|expr_statement|IF(expr)statement| IF(expr ) statement ELSE statement| WHILE ( expr ) statement| RETURN ;| RETURN expr ;| PRINT ;| PRINT expr_list ;| SCAN id_list ;\n");
	if (tok == INT || tok == STR || tok == VOID) {
		type();
		declarator_list();
		if (tok == SEMI) {
		    advance();
		} else {
		    printf("[ERROR]`;` expected, got %s\n", yytext);
		}
	}
	else if (tok == LC) {
		advance();
		statement();
		advance();
	}
	else if (tok == IF) {
		advance();//IF
		advance();//(
		expr();
		advance();//)
		statement();
		if (tok == ELSE) {
			expr();

		}
	}
	else if (tok == RETURN)
	{
		advance();
		if (tok == SEMI) {
			advance();
		}
		else {
			expr();
			advance();//;
		}
	}
	else if (tok == PRINT) {
		advance();
		if (tok == SEMI) {
			advance();
		}
		else
		{
			expr_list();
			advance();//;
		}
	}
	else if (tok == SCAN) {
		advance();
		id_list();
		advance();//;
	}
	else if (tok == WHILE) {
		advance();
		if (tok == LP) {
			advance();
			expr();
			advance();
			statement();
		}
	}
	else if(tok==SEMI||tok==ID){
		expression_statement();
	}
}


void statement_list(){
	printf("statement_list->statement statement_list1\n");
	statement();
	statement_list1();
}

void statement_list1() {
	printf("statement_list1->statement statement_list1|null\n");
	if (tok== VOID||tok==INT||tok==STR||tok ==RC|| tok == IF || tok == WHILE || tok == RETURN || tok == SCAN || tok == PRINT || tok==CMP||tok==MINUS||tok==NUMBER||tok==STRING) {
		statement();
		statement_list1();
	}
}

void expression_statement() {
	printf("expression_statement->;|expr;\n");
	if (tok == SEMI) {
		advance();
	}
	else if(tok){
		expr();
		advance();
	}
}

void expr() {
	printf("expr->cmp_expr\n");
	cmp_expr();
}

void cmp_expr() {
	printf("cmp_expr->add_expr cmp_expr1\n");
	add_expr();
	cmp_expr1();
}

void cmp_expr1() {
	//printf("cmp_expr1->CMP add_expr cmp_expr1|null\n");
	if (tok == CMP) {
		advance();
		add_expr();
		cmp_expr1();
	}
}

void expr_list() {
	printf("expr_list->expr expr_list1\n");
	expr();
	expr_list1();
}

void expr_list1() {
	//printf("expr_list1->,expr expr_list1|null\n");
	if (tok == COMMA) {
		advance();
		expr();
		expr_list1();
	}
}

void primary_expr() {
	printf("primary_expr->(expr )| NUMBER| STRING| primray_ID\n");
	if (tok == ID) {
		primary_ID();
	}
	else if (tok == NUMBER) {

		advance();
	 }
	else if (tok == STRING) {
		advance();
	}
	else if (tok == LP) {
		advance();
		expr();
		advance();
	}
}

void primary_ID() {
	printf("primray_ID->uraaaaaaa\n");
	advance();
	if (tok == LP) {
		advance();
		if (tok == RP)
			advance();
		else
		{
			expr_list();
		}
	}
	else if (tok == ASSIGN) {
		advance();
		expr_list();
	}
	else if (tok ==ASSIGN) {
		advance();
		expr();
	}
	else if (tok == LB) {
		advance();
		expr();
		advance();
		if (tok == ASSIGN) {
			advance();
			expr();
		}
	}
	else {
		advance();
	}
}

void id_list() {
	//printf("id_list\n");
	if (tok == ID) {
		advance();
		id_list1();
	}
}

void id_list1() {
	if (tok == COMMA) {
		advance();
		id_list1();
	}
}

void add_expr() {
	//printf("add_expr");
	mul_expr();
	add_expr1();
}

void add_expr1() {
	if (tok == PLUS) {
		advance();
		mul_expr();
		add_expr1();
	}
	else if (tok == MINUS) {
		advance();
		mul_expr();
		add_expr1();
	}
}

void mul_expr() {
	//printf("mul");
	if (tok == MINUS) {
		advance();
		primary_expr();
	}
	else {
		primary_expr();
		mul_expr1();
	}
}

void mul_expr1() {
	if (tok == STAR) {
		advance();
		primary_expr();
		mul_expr1();
	}
	else if (tok ==DIV) {
		advance();
		primary_expr();
		mul_expr1();
	}
	else if(tok==BAI)
	{
		advance();
		primary_expr();
		mul_expr1();
	}
}
 
void declarator() {
	printf("declarator\n");
	if (tok == ID) {
		advance();
		if (tok == LP) {
			advance();
			if (tok != RP) {
				parameter_list();
			}
			else {
				advance();
			}
		}
		else if (tok == ASSIGN) {

			//printf("AAAAA\n");
			advance();
			expr();
		}
		else if(tok==LB)
		{
			advance();
			if (tok != RB) {
				expr();
				advance();
				if (tok == ASSIGN) {
					advance();
					if (tok == LC) {
						advance();
						intstr_list();
						advance();
					}
				}
			}
			else {
				advance();
				if (tok == ASSIGN) {
					advance();
					if (tok == LC) {
						advance();
						intstr_list();
						advance();
					}
				}
			}
		}
	}
}